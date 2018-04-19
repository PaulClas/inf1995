#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "can.h"
#include "DEL.h"
#include "UART.h"
#include "MoteurDiag.h"
#include "Son.h"
#include "buttonTouch.h"



const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0x00;
/*
 const int DISTANCE_MAX = 380; //le robot se tient a 15cm du mur
 const int DISTANCE_MIN = 480; //le robot se tient a 13cm du mur
 const int DISTANCE_10 =500; //le robot se tient a 10cm du mur
 const int DISTANCE_60 = 185; //le robot se tient a 60cm du mur
 */
/*
 //CAPTEUR GAUCHE local inf1995
 //VIDE
 const uint16_t CapteurG_vide_sup = 80;//30-80
 const uint16_t CapteurG_vide_inf = 30;
 //
 // 10cm
 const uint16_t CapteurG_10cm_sup =480; // 455-480
 const uint16_t CapteurG_10cm_inf =455;
 //
 //15cm
 const uint16_t CapteurG_15cm_sup =360;// 335-360
 const uint16_t CapteurG_15cm_inf =335;
 //
 //20cm
 const uint16_t CapteurG_20cm_sup =290;//260-290
 const uint16_t CapteurG_20cm_inf =260;
 //
 //60cm
 const uint16_t CapteurG_60cm_sup = 220;//170/220
 const uint16_t CapteurG_60cm_inf = 170;
 */

//CAPTEUR GAUCHE 4eme etage
//VIDE

//
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

/*
 //CAPTEUR GAUCHE LUMINEUX
 //VIDE
 const uint16_t CapteurG_vide_sup = 150;
 const uint16_t CapteurG_vide_inf = 84;
 //
 // 10cm
 const uint16_t CapteurG_10cm_sup =550;
 const uint16_t CapteurG_10cm_inf =520;
 //
 //15cm
 const uint16_t CapteurG_15cm_sup =390;// 335-360
 const uint16_t CapteurG_15cm_inf =360;
 //
 //20cm
 const uint16_t CapteurG_20cm_sup =310;//260-290
 const uint16_t CapteurG_20cm_inf =285;
 //
 //60cm
 const uint16_t CapteurG_60cm_sup = 180;//170/220
 const uint16_t CapteurG_60cm_inf = 160;
 */

/*
 //CAPTEUR DROIT localinf1995
 //VIDE
 const uint16_t CapteurD_vide_sup = 120;//60-120
 const uint16_t CapteurD_vide_inf = 60;
 //
 // 10cm
 const uint16_t CapteurD_10cm_sup =475; //435-475
 const uint16_t CapteurD_10cm_inf =435;
 //
 //15cm
 const uint16_t CapteurD_15cm_sup =360; //330-360
 const uint16_t CapteurD_15cm_inf =330;
 //
 //20cm
 const uint16_t CapteurD_20cm_sup =270; //270-220
 const uint16_t CapteurD_20cm_inf =220;
 //
 //60cm
 const uint16_t CapteurD_60cm_sup = 200; //170-200
 const uint16_t CapteurD_60cm_inf = 170;
 */

//CAPTEUR DROIT local 4eme

//
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

/*
 //CAPTEUR DROIT LUMINEUX
 //VIDE
 const uint16_t CapteurD_vide_sup = 210;//60-120
 const uint16_t CapteurD_vide_inf = 130;
 //
 // 10cm
 const uint16_t CapteurD_10cm_sup =550; //435-475
 const uint16_t CapteurD_10cm_inf =500;
 //
 //15cm
 const uint16_t CapteurD_15cm_sup =380; //330-360
 const uint16_t CapteurD_15cm_inf =365;
 //
 //20cm
 const uint16_t CapteurD_20cm_sup =300; //270-220
 const uint16_t CapteurD_20cm_inf =285;
 //
 //60cm
 const uint16_t CapteurD_60cm_sup = 180; //170-200
 const uint16_t CapteurD_60cm_inf = 165;
 */

volatile char suivreMur = 'd';
void suivreMurDroit(uint16_t capteurDroite);
void suivreMurGauche(uint16_t capteurGauche);
bool verificationPermissionChangerDeMur(uint16_t capteur, uint16_t seuilCapteur, bool changerDeMur);
uint16_t lectureMediane(uint8_t cote);
bool touchbutton();

void runParcours()
{ 


	
	DDRB |= 0xFF;
	DEL del(B);
	
	can con;
	MoteurDiag moteur;
	Son son;
    son.chansonPoteau();
	char suivreMur;
    bool changerDeMur= true;
    bool poteauDetecte = false;
    bool boutonpresser= false;
    
    uint16_t valeurARetenir =0;
    
    uint16_t vD, vG;
    
    vG= con.lecture(0x02); //valeur analogique Gauche
    vD= con.lecture(0x00); //valeur analogique droite
  
    if(vD >= vG){// si mur droit est plus proche que mur gauche
        _delay_ms(30);
        if(vD >=vG){
            suivreMur = 'd';
        }
    }
    else
        suivreMur = 'g';
  
    
    
    for(;;){
		del.DEL_RED();
		vG= con.lecture(0x02); //valeur analogique Gauche
        vD= con.lecture(0x00); //valeur analogique droite
        if(suivreMur =='d'){ //suivre mur droit
			boutonpresser = touchbutton();
			if(boutonpresser ==true){
				boutonpresser =false;
				moteur.C_turnLeft();
				moteur.C_turnLeft();
				}
            del.DEL_GREEN();
            
            changerDeMur = verificationPermissionChangerDeMur(vG,  CapteurG_60cm_inf, changerDeMur);
            
            suivreMurDroit(vD);
            
            //si le robot detecte obstacle a gauche
            //verifie si il est entre 10 et 60cm et qu il a le droit de changer de mur
            if(vG > CapteurG_60cm_sup && vG < CapteurG_10cm_sup ){// si vG detecte un mur du coter gauche
                valeurARetenir= vG; // Obstacle lu, on met la valeur analogique gauche dans valeur a Retenir pour comparer par la suite
                moteur.C_arreter();
                moteur.C_avancer(150);
                _delay_ms(300);
                vG =con.lecture(0x02);
                if(valeurARetenir > vG){
                    vG =con.lecture(0x02);
                    if(valeurARetenir> vG){
                        son.initialisation();
                        son.chansonPoteau();
                        poteauDetecte= true;
                        moteur.C_reculer(200);
                        _delay_ms(400);
                        moteur.C_arreter();
                    }
                    else poteauDetecte =false;
                }
                else poteauDetecte =false;
                //If pour dire de changer de mur
                if(poteauDetecte == false  && changerDeMur == true){
                    suivreMur='g';
                    moteur.C_slightTurnLeft();
                    _delay_ms(100);
                    while(vG < CapteurG_15cm_inf){
                        moteur.C_avancer(150);
                        _delay_ms(700);
                        vG =con.lecture(0x02);
                    }
                    moteur.C_arreter();
                    changerDeMur = false;
                    del.DEL_OFF();
                }
            }
        }//fin du if d
        if(suivreMur =='g'){ // suivre mur gauche
			boutonpresser = touchbutton();
			if(boutonpresser==true){
				boutonpresser =false;
				moteur.C_turnRight();
				moteur.C_turnRight();
			}
            del.DEL_RED();
            
            changerDeMur = verificationPermissionChangerDeMur(vD,  CapteurD_60cm_sup, changerDeMur);
            suivreMurGauche(vG);
            
            if(vD > CapteurD_60cm_sup && vD < CapteurD_10cm_sup){// si vG detecte un mur du coter gauche
                valeurARetenir= vD; // Obstacle lu, on met la valeur analogique gauche dans valeur a Retenir pour comparer par la suite
                moteur.C_arreter();
                moteur.C_avancer(150);
                _delay_ms(300);
                vD = con.lecture(0x00);
                if(valeurARetenir> vD){
                    vD =con.lecture(0x00);
                    _delay_ms(100);
                    if(valeurARetenir > vD){
                        son.initialisation();
                        son.chansonPoteau();
                        poteauDetecte= true;
                        moteur.C_reculer(200);
                        _delay_ms(400);
                        moteur.C_arreter();
                    }
                    else poteauDetecte =false;
                }
                else poteauDetecte = false;
                //If pour dire de changer de mur
                if(poteauDetecte == false  && changerDeMur == true){
                    suivreMur = 'd';
                    moteur.C_slightTurnRight();
                    _delay_ms(200);
                    while(vD < CapteurD_15cm_inf){
                        moteur.C_avancer(150);
                        _delay_ms(700);
                        vD =con.lecture(0x00);
                    }
                    moteur.C_arreter();
                    changerDeMur = false;
                    del.DEL_OFF();
                }
                
            }
        }//fin du if g
    }//fin du for
}// fin du void parcours()
        
/****
 *
 * */

void suivreMurDroit(uint16_t capteurDroite){
    MoteurDiag moteur;
    
    // si le robot se tient trop loin du mur
    if(capteurDroite < CapteurD_15cm_inf){
        moteur.C_slightTurnRight();// tourner vers le mur leger
        moteur.C_avancer(200);
        _delay_ms(150);
        
    }
    //    si le robot se tient trop proche dur mur
    if(capteurDroite > CapteurD_15cm_sup){
        moteur.C_slightTurnLeft(); // eloigner du mur legerement
        moteur.C_avancer(200);
        _delay_ms(150);
        
    }
    // si le robot se tient a la bonne distance du mur
    if(capteurDroite <= CapteurD_15cm_sup && capteurDroite >= CapteurD_15cm_inf) {
        moteur.C_avancer(200);
        _delay_ms(150);
        
    }
    
}
void suivreMurGauche(uint16_t capteurGauche){
    
    MoteurDiag moteur;
    
    // si le robot se tient trop loin du mur
    
    if(capteurGauche < CapteurG_15cm_inf){
        
        moteur.C_slightTurnLeft();// tourner vers le mur legerement
        moteur.C_avancer(200);
        _delay_ms(150);
        
    }
    
    //    si le robot se tient trop proche du mur
    if(capteurGauche > CapteurG_15cm_sup){
        
        moteur.C_slightTurnRight(); // eloigner du mur legerement
        moteur.C_avancer(200);
        _delay_ms(150);
        
    }
    
    // si le robot se tient a la bonne distance du mur
    if(capteurGauche <= CapteurG_15cm_sup && capteurGauche >= CapteurG_15cm_inf) {
        moteur.C_avancer(200);
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

 uint16_t lectureMediane(uint8_t cote){
 
 can ca;
 
 uint16_t tableauValeurCaptee[200];
 
 for(uint8_t i = 0; i < 200; i++){
 
 tableauValeurCaptee[i] = ca.lecture(cote);
 
 }
 
 uint8_t valeur;
 
 for(uint8_t i = 0; i < 200; i++){
 
	for(uint8_t j = i; j < 200; j++){
 
		if(tableauValeurCaptee[j] < tableauValeurCaptee[i] ){
	 
			 valeur = tableauValeurCaptee[i];
			 tableauValeurCaptee[i] = tableauValeurCaptee[j];
			 tableauValeurCaptee[j] = valeur;
		}
	}
 }
 
 return tableauValeurCaptee[100];
 
 }


bool touchbutton()
{
    bool boutonpresser = false;
    _delay_ms(10);
    boutonpresser = ((PIND & 0x04)!=0);
    return boutonpresser;
}




