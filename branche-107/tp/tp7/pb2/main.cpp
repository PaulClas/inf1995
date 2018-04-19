/*
 * Nom: Proleme2
 * Auteur(e)s: Emmanuelle Roberge (1849263), Paul Clas (1846912) & Thomas McAdams (1904141)
 * Date: 1 mars 2018
 * Description: 
 * 		Ce programme permet de contrôler la DEL libre sur la carte mère 
 * 		à l'aide de la photorésistance qui se trouve sur le bread board.
 * 		Lorsque la lumière est à un bon niveau (lumière ambiante), la 
 * 		DEL sera ambre. Lorsque la lumière est basse (lorsque la lumiere
 *  	allant sur la photo resistance est bloquee par une main),la DEL
 *  	sera verte. Finalement, lorsque la photorésistance capte beaucoup
 * 		de lumière (lorsqu'elle est eclairee par une lampe de poche), la 
 * 		DEL sera rouge.
 */

/*
 * Fils: 
 * 		-Le fil bleu et brun, qui est de type mâle-femelle, est branché
 *  	 dans le bread bord du du côté male et sur la broche 1 et 2 du PORTA.
 *		 Ce fils doit être branché sur le PORTA puisque c'est le seul port
 * 		 capable de convertir les signaux analogiques en numériques.
 * 
 *      -Le fil rouge et noir, qui est de type mâle-femelle, est branché
 *  	 dans le bread board du côté mâle et dans le Vcc et ground du PORTA 
 * 		 (broche 7 et 8) du côté femelle. Il faut bien s'assurer que le 
 * 		 fil rouge soit connecté avec la broche 7.
 * 
 * 		-Le fil violet et blanc, qui est de type femelle-femelle, est branché
 * 		 d'un côté sur les pins de la DEL libre et à son autre extrémité,
 * 		 il est braché dans les pins 0 et 1 du PORTB.
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "can.h"

const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0x00;

void DEL_RED();
void DEL_GREEN();
void DEL_OFF();
void  DEL_AMBRE();

int SEUIL_VERT = 170;
int SEUIL_ROUGE = 240;


/***********************************************************************
 *
 **********************************************************************/

int main()
{
    DDRB = SORTIE; //out
    DDRD = SORTIE;
    DDRA = ENTREE; // in

	can convertisseurAnalogique;
    uint8_t valeurAnalogique;

    for(;;){
		
		valeurAnalogique = convertisseurAnalogique.lecture(0) >> 2;
		if ( valeurAnalogique < SEUIL_VERT){
			DEL_GREEN();
		} else if ( valeurAnalogique < SEUIL_ROUGE){
			DEL_AMBRE();
		} else {
			DEL_RED();
		}
    }
    
}
/***********************************************************************
 *
 **********************************************************************/
void DEL_RED()
{
    PORTB = 0x02;
}
/***********************************************************************
 *
 **********************************************************************/
void DEL_GREEN()
{
    PORTB = 0x01;
}
/***********************************************************************
 *
 **********************************************************************/
void DEL_OFF()
{
    PORTB = 0x00;
}
/***********************************************************************
 *
 **********************************************************************/
void  DEL_AMBRE()
{
        DEL_RED();
        _delay_ms(3);
        DEL_GREEN();
        _delay_ms(7);
}

