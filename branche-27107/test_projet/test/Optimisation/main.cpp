
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "can.h"
#include "DEL.h"
#include "UART.h"
#include "Moteur.h"
#include "Son.h"


const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0x00;
/*
const int DISTANCE_MAX = 380; //le robot se tient a 15cm du mur
const int DISTANCE_MIN = 480; //le robot se tient a 13cm du mur
const int DISTANCE_10 =500; //le robot se tient a 10cm du mur
const int DISTANCE_60 = 185; //le robot se tient a 60cm du mur
*/

/*//CAPTEUR GAUCHE PAS LIMUNEUX
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



/*//CAPTEUR DROIT PAS LUMINEUX
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



void suivreMurDroit(uint16_t capteurDroite);
void suivreMurGauche(uint16_t capteurGauche);
bool verificationPermissionChangerDeMur(uint16_t capteur, uint16_t seuilCapteur, bool changerDeMur);
void changerDeMurVersGauche(uint16_t capteurDroite, can convertisseurAnalogique);
void changerDeMurVersDroite(uint16_t capteurGauche, can convertisseurAnalogique);

enum State {ON, OFF};


volatile State boutonPoussoir = OFF;
volatile char suivreMur = 'd';

ISR(__vector_default) {}

ISR (INT0_vect) {

	Moteur moteur;
   //boutonPoussoir = 0x00;
    // anti-rebond
    _delay_ms(30);
   
	switch(boutonPoussoir){
		case OFF:
			boutonPoussoir = ON;
			break;
		case ON:
			boutonPoussoir = OFF;
			break;
		
    }
   if(boutonPoussoir == ON && suivreMur == 'd'){
		moteur.tourner180(false);
	}
	if(boutonPoussoir == ON && suivreMur == 'g'){
		moteur.tourner180(true);
	}
    EIFR |= (1 << INTF0);
}

	

void initialisationInterrupt(){
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli ();
    
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    //DDRB = 0xff;
    DDRD |= 0xF0;
    
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0) ;
    
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC01) ;
    
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}



int main(){
	
	
	can convertisseurAnalogique;
	DEL del(B);
	DDRB |= 0x0B;
	Son son;
	Moteur moteur; 
	initialisationInterrupt();
	
	
	bool changerDeMur = true;
	bool poteauDetecte = false;
	//suivreMur = 'g';
	
	uint16_t capteurDroite , capteurGauche;
	
	while(1){
		
		capteurDroite = convertisseurAnalogique.lecture(0x00); //valeur analogique Gauche
		capteurGauche = convertisseurAnalogique.lecture(0x02); //valeur analogique droite
		
		//Choix du mur de départ
		
		if(capteurDroite >= capteurGauche)
			suivreMur = 'd';
		else
			suivreMur = 'g';
			
			
		if (suivreMur == 'd'){
			
			del.DEL_OFF();
			moteur.avancer(70);
			
			changerDeMur = verificationPermissionChangerDeMur(capteurGauche, CapteurG_vide_sup, changerDeMur);
				
			suivreMurDroit(capteurDroite);
			
			
			if(capteurGauche > CapteurG_60cm_sup && capteurGauche < CapteurG_10cm_sup && changerDeMur == true){
				
				if( poteauDetecte == false){
					
					while(capteurGauche < CapteurG_15cm_inf){
						
						del.DEL_RED();
						changerDeMurVersGauche(capteurGauche, convertisseurAnalogique);
					}
					
					del.DEL_OFF();
						
					
					changerDeMur = false;
					
				}
				
			}
			
			
			
		}
		
		
		if (suivreMur == 'g'){
			
			del.DEL_GREEN();
			moteur.avancer(70);
			
			changerDeMur = verificationPermissionChangerDeMur(capteurDroite, CapteurD_vide_sup, changerDeMur);
			
			suivreMurGauche(capteurGauche);
			
			
			
			if(capteurDroite > CapteurD_60cm_sup && capteurDroite < CapteurD_10cm_sup && changerDeMur == true){
				
				if( poteauDetecte == false){
					
					while(capteurDroite < CapteurD_15cm_inf){
						
						del.DEL_RED();
						changerDeMurVersDroite(capteurDroite, convertisseurAnalogique);
					}
					
					
					changerDeMur = false;
					
				}
				
			}
			
			
			
		}
		
		else{
		del.DEL_AMBRE();
		moteur.arreter();
		}
	
	}

}


void suivreMurDroit(uint16_t capteurDroite){
	
	Moteur moteur;

	// si le robot se tient trop loin du mur
	
	if(capteurDroite < CapteurD_15cm_inf){
		
		moteur.slightTurnRight();// tourner vers le mur leger
		moteur.avancer(150);
		_delay_ms(100);

	}
	
	
	//	si le robot se tient trop proche dur mur 
	if(capteurDroite > CapteurD_15cm_sup){
		
		moteur.slightTurnLeft(); // eloigner du mur legerement
		moteur.avancer(150);
		_delay_ms(100);
		
	}
	
	
	// si le robot se tient a la bonne distance du mur 
	if(capteurDroite <= CapteurD_15cm_sup && capteurDroite >= CapteurD_15cm_inf) {
		
		moteur.avancer(150);
		_delay_ms(200);
		
	}
	
}


void suivreMurGauche(uint16_t capteurGauche){
	
	Moteur moteur;
	
	// si le robot se tient trop loin du mur
			
	if(capteurGauche < CapteurG_15cm_inf){
		
		moteur.slightTurnLeft();// tourner vers le mur legerement
		moteur.avancer(150);
		_delay_ms(100);
		
	}
		
	//	si le robot se tient trop proche du mur 
	if(capteurGauche > CapteurG_15cm_sup){
		
		moteur.slightTurnRight(); // eloigner du mur legerement
		moteur.avancer(150);
		_delay_ms(100);
		
	}
	
	// si le robot se tient a la bonne distance du mur 
	if(capteurGauche <= CapteurG_15cm_sup && capteurGauche >= CapteurG_15cm_inf) {
		moteur.avancer(150);
		_delay_ms(200);
		
	}	
	
}


bool verificationPermissionChangerDeMur(uint16_t capteur, uint16_t seuilCapteur, bool changerDeMur){
	
	if (capteur <= seuilCapteur && changerDeMur == false){
				
		_delay_ms(30); //revérification
		if (capteur <= seuilCapteur && changerDeMur == false)
			changerDeMur = true;
			
	}
	
	return changerDeMur;
	
}


void changerDeMurVersGauche(uint16_t capteurGauche, can convertisseurAnalogique){
	Moteur moteur;
	
	while(capteurGauche < CapteurG_15cm_inf){
		moteur.mediumTurnRight();
		moteur.avancer(200);
		_delay_ms(700);
		moteur.mediumTurnLeft();
		capteurGauche =convertisseurAnalogique.lecture(0x02);
	}
	
	
}

void changerDeMurVersDroite(uint16_t capteurDroite, can convertisseurAnalogique){
	
	Moteur moteur;
	
	while(capteurDroite < CapteurD_15cm_inf){
		moteur.mediumTurnLeft();
		moteur.avancer(200);
		_delay_ms(700);
		moteur.mediumTurnRight();
		capteurDroite =convertisseurAnalogique.lecture(0x00);
	}
	
	
}
