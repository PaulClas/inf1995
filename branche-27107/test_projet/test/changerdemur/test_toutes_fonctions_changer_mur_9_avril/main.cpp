/*
*
*n arrive pas a changer de mur
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
const int MUR_DETECTE =350; //le robot detecte un mur
/***********************************************************************
 *
 **********************************************************************/
void init(){
	DDRB = SORTIE; //out
    DDRD = SORTIE;
    DDRA = ENTREE; // in
 }
 
 
int main()
{
	init();
	
	can convertisseurAnalogique;
	Moteur moteur;
	UART uart;
	DEL del(B);
	
	
	char suivreMur;
	bool changerDeMur= true;
	
    uint16_t vD, vG;
    uint16_t total =0;
    uint16_t moyenne =0;
    
    vG= convertisseurAnalogique.lecture(0x02); //valeur analogique Gauche
    vD= convertisseurAnalogique.lecture(0x00); //valeur analogique droite
    
    
    /******Pour choisir quel mur suivre au debut*******************
    if(vD>=vG) // si mur droit est plus proche que mur gauche
		suivreMur = 'd';
	else
		suivreMur = 'g';
	**************************************************************/
	
	
	
	/*************TEST******************/
	suivreMur = 'd'; //pour forcer mur a choisir
	/*************************************/
	
	
    for(;;){
		
		vG= convertisseurAnalogique.lecture(0x02); //valeur analogique Gauche
		vD= convertisseurAnalogique.lecture(0x00); //valeur analogique droite
		
        while(suivreMur =='d'){ //suivre mur droit
			del.DEL_GREEN();
			
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
			
			
			//si le robot detecte un mur a gauche, ne prends pas encore en compte un poteau
			if(vG >= MUR_DETECTE && changerDeMur == true){// si vG detecte un mur du coter gauche
				//vG = convertisseurAnalogique.lecture(0x02);
				/*for(int i =0; i<20; i++){
					vG= convertisseurAnalogique.lecture(0x02);
					total+=vG;
					moyenne= total/20;}
				if(moyenne >= MUR_DETECTE){*/
					suivreMur = 'g';
					
					/*************TEST**********************/
					for(int i =0; i<10; i++){
						del.DEL_GREEN();
						_delay_ms(50);
						del.DEL_RED();
						_delay_ms(50);
					}
					/***************************************/
					
					moteur.slightTurnLeft();
					moteur.avancer(250);
					_delay_ms(300);
					changerDeMur= false;
				}
			}
			//si le robot detecte un espace vide a gauche, peut changerDeMur devient true
			/*if(vG <= MUR_DETECTE && changerDeMur ==false){
				
				/*************TEST**********************
				for(int i =0; i<10; i++){
					del.DEL_AMBRE();
					_delay_ms(500);
				}
				**************************************
				changerDeMur = true;
			}*/
				
			/*********************************************************
			// si le robot detecte un vide a gauche (espace entre mur, vide entre poteau, etc)
			if(vG <= ESPACE_DETECTE){
				confirmationEspaceVide++; // compte pour confirmer
				if(confirmationEspaceVide == 10){ // si 10 lecture et vG detecte encore espace vide
					suivreMur = 'g'; // va suivre mur gauche
					confirmationEspaceVide =0;
					moteur.slightTurnLeft(); // rourne legerement ver la gauche
					moteur.avancer(150); // avance legerement vers la gauche
					_delay_ms(500);
				}
			}
			* *********************************************************/
		//fin du while d
		
		/*****TEST*************/
		//changerDeMur = true;
		/*********************/
		
		while(suivreMur =='g'){ // suivre mur gauche
			del.DEL_RED();
			
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
		
			//si le robot detecte un mur a droite, ne prends pas encore en compte un poteau
			if(vD >= MUR_DETECTE && changerDeMur == true){// si vG detecte un mur du coter gauche
				moteur.slightTurnRight();
				moteur.avancer(250);
				_delay_ms(2000);
				changerDeMur = false;
				}
			}
			//changerDeMur = true;
			
			
			//si le robot detecte un espace vide a droite, peut changerDeMur devient true
			/*if(vD <= MUR_DETECTE && changerDeMur ==false){
				
				for(int i =0; i<10; i++){
					del.DEL_AMBRE();
					_delay_ms(500);
				}
		
				changerDeMur = true;
			}*/
			/*// si le robot detecte un vide a droite (espace entre mur, vide entre poteau, etc)
			if(vD <= ESPACE_DETECTE){
				confirmationEspaceVide++; // compte pour confirmer
				if(confirmationEspaceVide == 3){ // si trois lecture et vG detecte encore espace vide
					suivreMur = 'd'; // va suivre mur gauche
					confirmationEspaceVide =0;
					moteur.slightTurnRight(); // rourne legerement ver la gauche
					moteur.avancer(150); // avance legerement vers la gauche
					_delay_ms(500);
				}
			}
			* *********************************************************/
		//fin du while g
		 
	}
}


