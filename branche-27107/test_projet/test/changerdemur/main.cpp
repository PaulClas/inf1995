/*
*uart.transmit_UART_number(valeurAnalogiqueDroite);
*
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "can.h"
#include "DEL.h"
#include "UART.h"
#include "Moteur.h"
#include "buttonTouch.h"
#include "Minuterie.h"
#include "Son.h"


const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0x00;

const int DISTANCE_MAX = 400; //le robot se tient a 15cm du mur
const int DISTANCE_MIN = 545; //le robot se tient a 13cm du mur
const int ESPACE_DETECTE =185; //le robot voit un vide, espace entre mur, poteau, etc 
/***********************************************************************
 *
 **********************************************************************/
void init(){
	DDRB = SORTIE; //out
    DDRD = SORTIE;
    DDRA = ENTREE; // in
    can convertisseurAnalogique;
	Moteur moteur;
	UART uart;
	DEL del(B);
 }
 
uint16_t lecture_vd(){
	 vD= convertisseurAnalogique.lecture(0x00);
	 return vD;
}

uint16_t lecture_vg(){
	vG= convertisseurAnalogique.lecture(0x02);
	return vG;
}
 

int main()
{
	init();
	
	int confirmationEspaceVide =0;
	char suivreMur;
	const int MAX =100;
    uint16_t vD, vG;
    vG= convertisseurAnalogique.lecture(0x02); //valeur analogique Gauche
    vD= convertisseurAnalogique.lecture(0x00); //valeur analogique droite
    /******Pour choisir quel mur suivre au debut*******************/
    if(vD>=vG) // si mur droit est plus proche que mur gauche
		suivreMur = 'd';
	else
		suivreMur = 'g';
	/**************************************************************/
    for(;;){
		lecture_vd();
		lecture_vg();
        while(suivreMur =='d'){ //suivre mur droit
			lecture_vd();
			lecture_vg();
			// si le robot se tient trop loin du mur
			if(vD <= DISTANCE_MAX) 
				moteur.slightTurnRight();// tourner vers le mur leger
				moteur.avancer(150);
				
			//	si le robot se tient trop proche dur mur 
			if(vD >= DISTANCE_MIN) 
				moteur.slightTurnLeft(); // eloigner du mur legerement
				moteur.avancer(150);
			
			// si le robot se tient a la bonne distance du mur 
			if(vD < DISTANCE_MAX && vD > DISTANCE_MIN) 
				moteur.avancer(250);
			
			// si le robot detecte un vide (espace entre mur, vide entre poteau, etc)
			if(vG <= ESPACE_DETECTE){
				confirmationEspaceVide++; // compte pour confirmer
				if(confirmationEspaceVide == 10){ // si 10 lecture et vG detecte encore espace vide
					suivreMur == 'g'; // va suivre mur gauche
					confirmationEspaceVide =0;
					moteur.slightTurnLeft(); // rourne legerement ver la gauche
					moteur.avancer(150); // avance legerement vers la gauche
					_delay_ms(500);
				}
			}
		}
		while(suivreMur =='g'){ // suivre mur gauche
			lecture_vd();
			lecture_vg();
			if(vG <= DISTANCE_MAX) 
			moteur.slightTurnLeft();// tourner vers le mur legerement
			moteur.avancer(150);
				
			//	si le robot se tient trop proche du mur 
			if(vG >= DISTANCE_MIN) 
				moteur.slightTurnRight(); // eloigner du mur legerement
				moteur.avancer(150);
			
			// si le robot se tient a la bonne distance du mur 
			if(vG < DISTANCE_MAX && vG > DISTANCE_MIN) 
				moteur.avancer(250);
			
			// si le robot detecte un vide (espace entre mur, vide entre poteau, etc)
			if(vD <= ESPACE_DETECTE){
				confirmationEspaceVide++; // compte pour confirmer
				if(confirmationEspaceVide == 3){ // si trois lecture et vG detecte encore espace vide
					suivreMur == 'd'; // va suivre mur gauche
					confirmationEspaceVide =0;
					moteur.slightTurnRight(); // rourne legerement ver la gauche
					moteur.avancer(150); // avance legerement vers la gauche
					_delay_ms(500);
				}
			}
		};    
	}  
}


