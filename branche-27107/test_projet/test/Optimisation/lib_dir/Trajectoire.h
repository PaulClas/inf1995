#include <avr/io.h>
#include <util/delay.h>
#include "can.h"
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

/******************************************************************************
************************   Fonction suivreMurDroit	***************************
******************************************************************************/

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

/******************************************************************************
************************   Fonction suivreMurGauche	***************************
******************************************************************************/

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
/******************************************************************************
***************	Fonction verificationPermissionChangerDeMur	*******************
******************************************************************************/
bool verificationPermissionChangerDeMur(uint16_t capteur, uint16_t seuilCapteur, bool changerDeMur){

	if (capteur <= seuilCapteur && changerDeMur == false){
		_delay_ms(30); //revérification
		if (capteur <= seuilCapteur && changerDeMur == false)
			changerDeMur = true;
	}
	return changerDeMur;
}
