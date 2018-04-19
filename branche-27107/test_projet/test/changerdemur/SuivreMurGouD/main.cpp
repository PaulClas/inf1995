/*
*Changer la valeur de suivreMur = g ou d pour decider quel capteur et mur a longer
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

const int DISTANCE_MAX = 380; //le robot se tient a 15cm du mur
const int DISTANCE_MIN = 480; //le robot se tient a 13cm du mur
const int MUR_DETECTE =200; //le robot detecte un mur
/***********************************************************************
 *
 **********************************************************************/
void init(){
	DDRB = SORTIE; //out
    DDRD = SORTIE;
    DDRA = ENTREE; // in
 }
 
/*uint16_t lecture_vd(can convertisseurAnalogique){
	 uint16_t vD= convertisseurAnalogique.lecture(0x00);
	 return vD;
}

uint16_t lecture_vg(can convertisseurAnalogique){
	uint16_t vG= convertisseurAnalogique.lecture(0x02);
	return vG;
}
*/
 

int main()
{
	init();
	
	can convertisseurAnalogique;
	Moteur moteur;
	UART uart;
	DEL del(B);
	
	
	char suivreMur;
	//const int MAX =100;
    uint16_t vD, vG;
    vG= convertisseurAnalogique.lecture(0x02); //valeur analogique Gauche
    vD= convertisseurAnalogique.lecture(0x00); //valeur analogique droite
    /******Pour choisir quel mur suivre au debut*******************
    if(vD>=vG) // si mur droit est plus proche que mur gauche
		suivreMur = 'd';
	else
		suivreMur = 'g';
	**************************************************************/
	suivreMur = 'g';
    for(;;){
		vG= convertisseurAnalogique.lecture(0x02); //valeur analogique Gauche
		vD= convertisseurAnalogique.lecture(0x00); //valeur analogique droite
		
        while(suivreMur =='d'){ //suivre mur droit
			
			vG= convertisseurAnalogique.lecture(0x02); //valeur analogique Gauche
			vD= convertisseurAnalogique.lecture(0x00); //valeur analogique droite
			
			// si le robot se tient trop loin du mur
			if(vD <= DISTANCE_MAX){
				moteur.slightTurnRight();// tourner vers le mur leger
				moteur.avancer(150);
				_delay_ms(380);}
				
			//	si le robot se tient trop proche dur mur 
			if(vD >= DISTANCE_MIN){
				moteur.slightTurnLeft(); // eloigner du mur legerement
				moteur.avancer(150);
				_delay_ms(380);}
			
			// si le robot se tient a la bonne distance du mur 
			if(vD < DISTANCE_MAX && vD > DISTANCE_MIN) 
				moteur.avancer(250);
				
		}//fin du while d
		
		while(suivreMur =='g'){ // suivre mur gauche
			
			vG= convertisseurAnalogique.lecture(0x02); //valeur analogique Gauche
			vD= convertisseurAnalogique.lecture(0x00); //valeur analogique droite
			
			if(vG <= DISTANCE_MAX){
				moteur.slightTurnLeft();// tourner vers le mur legerement
				moteur.avancer(150);
				_delay_ms(380);}
				
			//	si le robot se tient trop proche du mur 
			if(vG >= DISTANCE_MIN){
				moteur.slightTurnRight(); // eloigner du mur legerement
				moteur.avancer(150);
				_delay_ms(380);}
			
			// si le robot se tient a la bonne distance du mur 
			if(vG < DISTANCE_MAX && vG > DISTANCE_MIN) 
				moteur.avancer(250);
				
		}//fin du while g
		 
	}
}


