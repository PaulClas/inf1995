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
#include "moves.h"
#include "detectionObstacle.h"

const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0x00;

const uint16_t distance_au_mur_de_15cm_ = 400; //15cm
const uint16_t SEUILMIN=185; // 60cm 
const uint16_t SEUILMAX=545; // 10cm

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
	
	bool aDroite = true; // suit le mur de droite
	
	//uint16_t cote;
	//uint16_t coteOp;
	
	//
	bool canChange =1;
	bool isPoteau = true;
	moves move;
	detectionObstacle obstacle;
	//Son son;
	//uint32_t somme = 0;
	//uint16_t moyenne = 0;
	int i;
	const int MAX =100;
    uint16_t valeurAnalogiqueDroite, valeurAnalogiqueGauche;
    
    /*********TEST*********/ 
       /* del.DEL_RED();
        _delay_ms(50);
        del.DEL_GREEN();
        _delay_ms(50);
        del.DEL_RED();
        _delay_ms(50);
        del.DEL_GREEN();
        _delay_ms(50);
        
        moteur.avancer(150);
        _delay_ms(2000);
        moteur.arreter();*/
        /*******TEST*******/ 
         char coterASuivre = 'g';
         int compteur =0;
         bool doitchangerdemur = false;
	 bool vide = true;
	 bool obstaclebool = false;
    for(;;){
	valeurAnalogiqueDroite = convertisseurAnalogique.lecture(0x00);
	moteur.avancer(150);
	if(obstacle.obstacleDetecte(valeurAnalogiqueDroite)&& obstaclebool == false){
	   del.DEL_GREEN();
	   vide = false;
	   obstaclebool = true;
	}
	if(!obstacle.obstacleDetecte(valeurAnalogiqueDroite) && obstaclebool ==true){
	  del.DEL_RED();
	  vide = false;
	  obstaclebool = false;	
	}
	if(vide==false && obstaclebool==false){
	del.DEL_AMBRE();	
	}
    }
    return 0;
}
