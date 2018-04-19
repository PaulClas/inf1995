/*
*
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
//#include "buttonTouch.h"
//#include "Minuterie.h"
#include "Son.h"



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
/***********************************************************************
 *
 **********************************************************************/
void init(){
	DDRB = SORTIE; //out
    DDRD = SORTIE;
    DDRC = SORTIE;
    DDRA = ENTREE; // in
 }
/*
void changerDeMurVersLeMurGauche(can convertisseurAnalogique, Moteur moteur){
	int distance =0;
	//bool changementReussit = false;
	vG= convertisseurAnalogique.lecture(0x02)
	distance = vG;
	while(distance < DISTANCE_MIN){
		moteur.slightTurnLeft
		moteur.avancer(150);
		_delay_ms(100);
		vG= convertisseurAnalogique.lecture(0x02)
		distance =vG;
	}
}
*/
int main()
{
	init();
	
	can convertisseurAnalogique;
	Moteur moteur;
	UART uart;
	DEL del(B);//del sur B0
	Son son;// piezo sur B3
	son.arret();
	
	char suivreMur;
	bool changerDeMur= true;
	uint16_t valeurARetenir =0;
	bool poteauDetecte = false;
	
    uint16_t vD, vG;
    //uint16_t total =0;
    //uint16_t moyenne =0;
    
    vG= convertisseurAnalogique.lecture(0x02); //valeur analogique Gauche
    vD= convertisseurAnalogique.lecture(0x00); //valeur analogique droite
    
    
    /******Pour choisir quel mur suivre au debut*******************
    if(vD >= vG) // si mur droit est plus proche que mur gauche
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
			del.DEL_AMBRE();
			poteauDetecte= false;
			
			vG= convertisseurAnalogique.lecture(0x02); //valeur analogique Gauche
			vD= convertisseurAnalogique.lecture(0x00); //valeur analogique droite
			
			//uart.transmit_UART_number(vG);
			// si le robot se tient trop loin du mur
			if(vD < CapteurD_15cm_inf){
				moteur.slightTurnRight();// tourner vers le mur leger
				moteur.avancer(150);
				_delay_ms(100);
				}
			
			//	si le robot se tient trop proche dur mur 
			if(vD > CapteurD_15cm_sup){
				moteur.slightTurnLeft(); // eloigner du mur legerement
				moteur.avancer(150);
				_delay_ms(100);
				}
			
			// si le robot se tient a la bonne distance du mur 
			if(vD <= CapteurD_15cm_sup && vD >= CapteurD_15cm_inf){
				moteur.avancer(150);
				_delay_ms(200);
				}
			
			
			//si le robot detecte obstacle a gauche
			//verifie si il est entre 10 et 60cm et qu il a le droit de changer de mur
			if(vG > CapteurG_60cm_sup && vG < CapteurG_10cm_sup && changerDeMur == true){// si vG detecte un mur du coter gauche
				/******TEST*******/
				del.DEL_GREEN();
				_delay_ms(200);
				del.DEL_OFF();
				_delay_ms(200);
				del.DEL_GREEN();
				_delay_ms(200);
				del.DEL_OFF();
				_delay_ms(200);
				del.DEL_GREEN();
				_delay_ms(200);
				/****************/
				moteur.avancer(150);
				valeurARetenir= vG; // Obstacle lu, on met la valeur analogique gauche dans valeur a Retenir pour comparer par la suite
				_delay_ms(400); // SEMBLE ETRE LE PROBLEME DE DELAI
				vG= convertisseurAnalogique.lecture(0x02);
				//uart.transmit_UART_number(vG);
				// If pour dire que c est un poteau
				// si detecte une valeur inferieur a sa deuxieme lecture 
				//c est a dire distance plus grande alors detecte poteau
				if(valeurARetenir> vG){
					vG = convertisseurAnalogique.lecture(0x02);
						if(valeurARetenir> vG){
						son.initialisation();
						son.chansonPoteau();
						poteauDetecte= true;
						moteur.reculer(200);
						_delay_ms(800);
						/******TEST*******/
						del.DEL_RED();
						_delay_ms(200);
						del.DEL_OFF();
						_delay_ms(200);
						del.DEL_RED();
						_delay_ms(200);
						del.DEL_OFF();
						_delay_ms(200);
						del.DEL_RED();
						_delay_ms(200);
						/****************/
						}\
					}
				//If pour dire de changer de mur
				if(vG > CapteurG_60cm_sup && vG < CapteurG_10cm_sup && poteauDetecte == false){	
					suivreMur = 'g';
					changerDeMur =false;
					/*************TEST**********************/
					for(int i =0; i<10; i++){
						del.DEL_GREEN();
						_delay_ms(50);
						del.DEL_RED();
						_delay_ms(50);
					}
					/***************************************/
					while(vG < CapteurG_15cm_inf){
						moteur.slightTurnLeft();
						moteur.avancer(200);
						_delay_ms(700);
						//moteur.arreter();
						moteur.slightTurnRight();
						vG =convertisseurAnalogique.lecture(0x02);
					}
				
				}
			}
			
			//pour identifier poteau si poteau est proche d un mur
			if(vG > CapteurG_60cm_sup && vG < CapteurG_10cm_sup && changerDeMur == false){
				moteur.avancer(150);
				valeurARetenir= vG; // Obstacle lu, on met la valeur analogique gauche dans valeur a Retenir pour comparer par la suite
				_delay_ms(400); // SEMBLE ETRE LE PROBLEME DE DELAI
				vG= convertisseurAnalogique.lecture(0x02);
				if(valeurARetenir> vG){
					vG = convertisseurAnalogique.lecture(0x02);
						if(valeurARetenir> vG){
						son.initialisation();
						son.chansonPoteau();
						poteauDetecte= true;
						moteur.reculer(200);
						_delay_ms(800);
						/******TEST*******/
						del.DEL_RED();
						_delay_ms(200);
						del.DEL_OFF();
						_delay_ms(200);
						del.DEL_RED();
						_delay_ms(200);
						del.DEL_OFF();
						_delay_ms(200);
						del.DEL_RED();
						_delay_ms(200);
						/****************/
						}
					}
			}
			
			
			//voit du vide alors met changerDeMur est mis a true
			if(vG< CapteurG_60cm_sup && changerDeMur == false){
				vG= convertisseurAnalogique.lecture(0x02); //valeur analogique Gauche
				if(vG< CapteurG_60cm_sup)
					changerDeMur = true;
			}
				
		
		}//fin du while d
		
		/*****TEST*************/
		//changerDeMur = true;
		/*********************/
		
		while(suivreMur =='g'){ // suivre mur gauche
			del.DEL_RED();
			
			vG= convertisseurAnalogique.lecture(0x02); //valeur analogique Gauche
			vD= convertisseurAnalogique.lecture(0x00); //valeur analogique droite
			
			if(vG < CapteurG_15cm_inf){
				moteur.slightTurnLeft();// tourner vers le mur legerement
				moteur.avancer(150);
				_delay_ms(100);}
				
			//	si le robot se tient trop proche du mur 
			if(vG > CapteurG_15cm_sup){
				moteur.slightTurnRight(); // eloigner du mur legerement
				moteur.avancer(150);
				_delay_ms(100);}
			
			// si le robot se tient a la bonne distance du mur 
			if(vG <= CapteurG_15cm_sup && vG >= CapteurG_15cm_inf) {
				moteur.avancer(150);
				_delay_ms(200);
				}
			//si le robot detecte obstacle a droite
			//verifie si il est entre 10 et 60cm et qu il a le droit de changer de mur
			if(vD > CapteurD_60cm_sup && vD < CapteurD_10cm_sup && changerDeMur == true){// si vG detecte un mur du coter gauche
				/******TEST*******/
				del.DEL_GREEN();
				_delay_ms(200);
				del.DEL_OFF();
				_delay_ms(200);
				del.DEL_GREEN();
				_delay_ms(200);
				del.DEL_OFF();
				_delay_ms(200);
				del.DEL_GREEN();
				_delay_ms(200);
				/****************/
				moteur.avancer(150);
				valeurARetenir= vD; // Obstacle lu, on met la valeur analogique gauche dans valeur a Retenir pour comparer par la suite
				_delay_ms(400); // SEMBLE ETRE LE PROBLEME DE DELAI
				vD= convertisseurAnalogique.lecture(0x00);
				//uart.transmit_UART_number(vG);
				// If pour dire que c est un poteau
				// si detecte une valeur inferieur a sa deuxieme lecture 
				//c est a dire distance plus grande alors detecte poteau
				if(valeurARetenir> vD){
					vD = convertisseurAnalogique.lecture(0x00);
						if(valeurARetenir> vD){
						son.initialisation();
						son.chansonPoteau();
						poteauDetecte= true;
						moteur.reculer(200);
						_delay_ms(800);
						/******TEST*******/
						del.DEL_RED();
						_delay_ms(200);
						del.DEL_OFF();
						_delay_ms(200);
						del.DEL_RED();
						_delay_ms(200);
						del.DEL_OFF();
						_delay_ms(200);
						del.DEL_RED();
						_delay_ms(200);
						/****************/
						}\
					}
				//If pour dire de changer de mur
				if(vD > CapteurD_60cm_sup && vG < CapteurD_10cm_sup && poteauDetecte == false){	
					suivreMur = 'd';
					changerDeMur =false;
					/*************TEST**********************/
					for(int i =0; i<10; i++){
						del.DEL_GREEN();
						_delay_ms(50);
						del.DEL_RED();
						_delay_ms(50);
					}
					/***************************************/
					while(vD < CapteurD_15cm_inf){
						moteur.slightTurnRight();
						moteur.avancer(200);
						_delay_ms(700);
						//moteur.arreter();
						moteur.slightTurnLeft();
						vD =convertisseurAnalogique.lecture(0x00);
					}
				
				}
			}
			
			//pour identifier poteau si poteau est proche d un mur
			if(vD > CapteurD_60cm_sup && vD < CapteurD_10cm_sup && changerDeMur == false){
				moteur.avancer(150);
				valeurARetenir= vD; // Obstacle lu, on met la valeur analogique gauche dans valeur a Retenir pour comparer par la suite
				_delay_ms(400); // SEMBLE ETRE LE PROBLEME DE DELAI
				vD= convertisseurAnalogique.lecture(0x00);
				if(valeurARetenir> vD){
					vD = convertisseurAnalogique.lecture(0x00);
						if(valeurARetenir> vD){
						son.initialisation();
						son.chansonPoteau();
						poteauDetecte= true;
						moteur.reculer(200);
						_delay_ms(800);
						/******TEST*******/
						del.DEL_RED();
						_delay_ms(200);
						del.DEL_OFF();
						_delay_ms(200);
						del.DEL_RED();
						_delay_ms(200);
						del.DEL_OFF();
						_delay_ms(200);
						del.DEL_RED();
						_delay_ms(200);
						/****************/
						}
					}
			}
			
			
			//voit du vide alors met changerDeMur est mis a true
			if(vD< CapteurD_60cm_sup && changerDeMur == false){
				vD= convertisseurAnalogique.lecture(0x00); //valeur analogique Gauche
				if(vD< CapteurD_60cm_sup)
					changerDeMur = true;
			}
				
			
			
			
		}//fin du while g
		 
	}
}


