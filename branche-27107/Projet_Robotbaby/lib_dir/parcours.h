#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "can.h"
#include "DEL.h"
#include "UART.h"
#include "MoteurDiag.h"
#include "Son.h"



const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0x00;


// 10cm
const uint16_t CapteurG_10cm_sup =470;
const uint16_t CapteurG_10cm_inf =430;
//
//15cm
const uint16_t CapteurG_15cm_sup =350;
const uint16_t CapteurG_15cm_inf =320;
//
//20cm
const uint16_t CapteurG_20cm_sup =280;
const uint16_t CapteurG_20cm_inf =260;
//
//60cm
const uint16_t CapteurG_60cm_sup = 115;
const uint16_t CapteurG_60cm_inf = 107;

/**********************************************/

// 10cm
const uint16_t CapteurD_10cm_sup =520;
const uint16_t CapteurD_10cm_inf =490;
//
//15cm
const uint16_t CapteurD_15cm_sup =390;
const uint16_t CapteurD_15cm_inf =360;
//
//20cm
const uint16_t CapteurD_20cm_sup =310;
const uint16_t CapteurD_20cm_inf =280;
//
//60cm
const uint16_t CapteurD_60cm_sup = 110;
const uint16_t CapteurD_60cm_inf = 90;


volatile char suivreMur = 'd';

void suivreMurDroit(uint16_t capteurDroite);
void suivreMurGauche(uint16_t capteurGauche);
bool verificationPermissionChangerDeMur(uint16_t capteur, uint16_t seuilCapteur, bool changerDeMur);


void runParcours()
{ 
	
	DDRB |= 0xFF;
	DEL del(B);
	can capteur;
	MoteurDiag moteur;
	Son son;
    son.chansonPoteau();
	char suivreMur;
    bool changerDeMur = true;
    bool poteauDetecte = false;
    
    uint16_t valeurARetenir = 0;
    
    uint16_t vD, vG;
    
    vG = capteur.lecture(0x02); //valeur analogique Gauche
    vD = capteur.lecture(0x00); //valeur analogique droite
  
    if(vD >= vG){ //Choix du mur le plus pres a suivre au debut du programme
        _delay_ms(30); //rebond
        if(vD >=vG){
            suivreMur = 'd';
        }
    }
    else
        suivreMur = 'g';
  
    for(;;){
		vG = capteur.lecture(0x02); //valeur analogique Gauche
        vD = capteur.lecture(0x00); //valeur analogique droite
        
        if(suivreMur =='d'){ //suivre mur droit
            
            changerDeMur = verificationPermissionChangerDeMur(vG, 80, changerDeMur);
            
            suivreMurDroit(vD);
            
            //si le robot detecte obstacle a gauche
            //verifie si il est entre 10 et 60cm et qu il a le droit de changer de mur
            if(vG > CapteurG_60cm_sup && vG < CapteurG_10cm_sup ){ // si vG detecte un mur du coter gauche
                valeurARetenir = vG; // Obstacle lu, on met la valeur analogique gauche dans valeur a Retenir pour comparer par la suite
                moteur.C_arreter();
                moteur.C_avancer(150);
                _delay_ms(300);
                vG = capteur.lecture(0x02);
                if(valeurARetenir > vG){
                    vG = capteur.lecture(0x02);
                    if(valeurARetenir> vG){
                        son.initialisation();
                        son.chansonPoteau();
                        poteauDetecte= true;
                    }
                  
                }
                //If pour dire de changer de mur
                if(poteauDetecte == false  && changerDeMur == true){
                    suivreMur='g';
                    moteur.C_slightTurnLeft();
                    _delay_ms(100);
                    while(vG < CapteurG_15cm_inf){
                        moteur.C_avancer(150);
                        //_delay_ms(700);
                        vG = capteur.lecture(0x02);
                    }
                    moteur.C_slightTurnRight();
                    _delay_ms(100);
                    moteur.C_arreter();
                    changerDeMur = false;
                }
            }
        }//fin du if d
        
        
        if(suivreMur =='g'){ // suivre mur gauche
            changerDeMur = verificationPermissionChangerDeMur(vD, 80, changerDeMur);
            suivreMurGauche(vG);
            
            if(vD > CapteurD_60cm_sup && vD < CapteurD_10cm_sup){ // si vG detecte un mur du coter gauche
                valeurARetenir= vD; // Obstacle lu, on met la valeur analogique gauche dans valeur a Retenir pour comparer par la suite
                moteur.C_arreter();
                moteur.C_avancer(150);
                _delay_ms(300);
                vD = capteur.lecture(0x00);
                if(valeurARetenir> vD){
                    vD = capteur.lecture(0x00);
                    _delay_ms(100);
                    if(valeurARetenir > vD){
                        son.initialisation();
                        son.chansonPoteau();
                        poteauDetecte= true;
                    }

                }
                //If pour dire de changer de mur
                if(poteauDetecte == false  && changerDeMur == true){
                    suivreMur = 'd';
                    moteur.C_slightTurnRight();
                    _delay_ms(100);
                    while(vD < CapteurD_15cm_inf){
                        moteur.C_avancer(150);
                        //_delay_ms(700);
                        vD =capteur.lecture(0x00);
                    }
                    moteur.C_slightTurnLeft();
                    _delay_ms(100);
                    moteur.C_arreter();
                    changerDeMur = false;
                }
                
            }
        }//fin du if g
        poteauDetecte = false;
    }//fin du for
}// fin du void parcours()
        
/****
 *
 * */

void suivreMurDroit(uint16_t capteurDroite){
    MoteurDiag moteur;
    DEL del(B);
        
    // si le robot se tient trop loin du mur
    if(capteurDroite < CapteurD_15cm_inf){
		del.DEL_RED();
        moteur.C_slightTurnRight();// tourner vers le mur leger
        _delay_ms(50);
        moteur.C_avancer(150);
        _delay_ms(140);
        
    }
    //    si le robot se tient trop proche dur mur
    if(capteurDroite > CapteurD_15cm_sup){
		del.DEL_RED();
        moteur.C_slightTurnLeft(); // eloigner du mur legerement
        _delay_ms(70);
        moteur.C_avancer(150);
        _delay_ms(120);
        
    }
    // si le robot se tient a la bonne distance du mur
    if(capteurDroite <= CapteurD_15cm_sup && capteurDroite >= CapteurD_15cm_inf) {
		del.DEL_GREEN();
        moteur.C_avancer(150);
        _delay_ms(150);
        
    }
    
}
void suivreMurGauche(uint16_t capteurGauche){
    
    MoteurDiag moteur;
    DEL del(B);
    
    // si le robot se tient trop loin du mur
    
    if(capteurGauche < CapteurG_15cm_inf){
        del.DEL_RED();
        moteur.C_slightTurnLeft();// tourner vers le mur legerement
        _delay_ms(70);
        moteur.C_avancer(150);
        _delay_ms(120);
        
    }
    
    //    si le robot se tient trop proche du mur
    if(capteurGauche > CapteurG_15cm_sup){
        del.DEL_RED();
        moteur.C_slightTurnRight(); // eloigner du mur legerement
        _delay_ms(70);
        moteur.C_avancer(150);
        _delay_ms(120);
        
    }
    
    // si le robot se tient a la bonne distance du mur
    if(capteurGauche <= CapteurG_15cm_sup && capteurGauche >= CapteurG_15cm_inf) {
		del.DEL_GREEN();
        moteur.C_avancer(150);
        _delay_ms(150);
        
    }
    
}
bool verificationPermissionChangerDeMur(uint16_t capteur, uint16_t seuilCapteur, bool changerDeMur){
    
    if (capteur <= seuilCapteur && changerDeMur == false){
        
        _delay_ms(30); //revérification
        if (capteur <= seuilCapteur)
            changerDeMur = true;
        
    }
    
    return changerDeMur;
    
}

