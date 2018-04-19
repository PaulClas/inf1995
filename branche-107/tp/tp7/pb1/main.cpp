/*
 * Nom: Probleme1
 * Auteur(e)s: Emmanuelle Roberge (1849263), Paul Clas (1846912) & Thomas McAdams (1904141)
 * Date: 1 mars 2018
 * Description: 
 * 		Ce programme permet de contrôler la DEL libre a l'aide du bouton
 * 		poussoir que nous avons installé sur le bread board. Lorsque le
 * 		programme est initialisé, la DEL est éteinte. La minuterie demarre
 * 		lorsque l'usager appuie sur le bouton poussoir du bread board, c'est
 * 		un compteur (dixiemes_secondes) qui incrémente 10 fois par seconde.
 * 		Une fois que le bouton est relâché ou lorsque le compteur atteint 
 * 		une valeur de 120 la DEL devient verte pendant 0.5 seconde et ensuite
 * 		s'éteint pour 2 secondes. Par la suite, elle devra clignoter en 
 * 		rouge (compteur/2) fois au rythme de 2 fois par seconde. Une fois
 *		la fin du clignotement elle deviendra verte pendant une seconde 
 * 		pour finalement s'éteindre et revenir à son état initial.
 */

/*
 * Fils: 
 * 		-Le fils bleu et noir, qui est de type mâle-femelle, est branché
 * 		 dans le bread bord du côté mâle et sur la broche 3 et 4 du PORTD
 * 		 du côté  femelle. Il faut bien s'assurer que le fil bleu soit 
 * 		 connecté avec la broche 3.
 * 
 *      -Le fil rouge et noir, qui est de type mâle-femelle, est branché
 *	  	 dans le bread board du côté mâle et dans le Vcc et ground du PORTA
 *  	 (broche 7 et 8) du côté femelle. Il faut bien s'assurer que le 
 * 		 fil rouge soit connecté avec la broche 7.
 * 
 *      -Le fil violet et blanc, qui est de type femelle-femelle, est 
 * 		 branché d'un côté sur les pins de la DEL libre et à son autre 
 * 		 extrémité, il est branché dans le pin 0 et 1 du PORTB.
 */
 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t minuterieExpiree;
volatile uint8_t dixiemes_secondes = 0;
volatile uint8_t boutonPoussoir = 1;

const uint8_t ENTREE = 0x00;
const uint8_t SORTIE = 0xff;

const uint16_t CT_DIXIEME_SECONDE = 781;
const uint16_t DIXIEMES_SECONDES_EXPIRATION = 120;

void DEL_RED();
void DEL_GREEN();
void DEL_OFF();

/***********************************************************************
 * Fonction: ISR(TIMER1_COMPA_vect )
 * Description: Cette fonction permet de partir le compteur lorqu'il y a
 *              une interruption.
 * Dernière modification: 22 février 2018, 14h00
 **********************************************************************/
ISR (TIMER1_COMPA_vect ) {
	
    dixiemes_secondes++;
    if( dixiemes_secondes >= DIXIEMES_SECONDES_EXPIRATION){
		minuterieExpiree = 1;
	}
	TIFR1 |= (1 << TOV1);
}

/***********************************************************************
 * Fonction: ISR(INT0_vect )
 * Description: Cette fonction permet capter l'interruption lorsqu'il y
 * 				un logical change avec le bouton poussoir. 
 * Dernière modification: 22 février 2018, 14h00
 **********************************************************************/
ISR (INT0_vect) {
	
	if(PIND & (1 << 2)){
		_delay_ms(30);
		if(PIND & (1 << 2))
			boutonPoussoir = 1;	
	}
	else
		boutonPoussoir = 0;
	
	EIFR |= (1 << INTF0);
}

/***********************************************************************
 * Fonction: partirMinuterie ( uint16_t duree )
 * Description: Cette fonction initialise la minuterie et le compteur à 
 * 				0 et démarre le timer. 
 * Dernière modification: 22 février 2018, 14h00
 **********************************************************************/

void partirMinuterie ( uint16_t duree )
{
    minuterieExpiree = 0;
    dixiemes_secondes = 0;
    TCNT1 = 0;

    OCR1A = duree;
    TCCR1A = (1 << COM1A0) | (1 << COM1A1); 

    // mode CTC du timer
    TCCR1B |= (1 << WGM12);

    // Mettre le prescaler a 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    TCCR1C = 0;

    // Enable l'interruption TIMER1_COMPA
    TIMSK1 = (1 << OCIE1A);
}

/***********************************************************************
 * Fonction: initialisation()
 * Description: Cette fonction definit les entrees et sorties en plus
 * 				d'enable les interruptions. 
 * Dernière modification: 22 février 2018, 14h00
 **********************************************************************/


void initialisation()
{
    cli();
    
    DDRA = ENTREE;
    DDRB = SORTIE;
    DDRD = ENTREE;
    
    // Permettre les interruptions venant de INT0
    EIMSK |= (1 << INT0);
    
    // Any edge triggers an interrupt
    EICRA |= (1 << ISC00);
    //EICRA &= ~(1 << ISC01);
    
    sei();
}

/***********************************************************************
 * 
 **********************************************************************/

int main()
{
	initialisation();
		
	for(;;){
		
		// Attendre ici que le bouton poussoir soit pressed
		while(boutonPoussoir==1){}
		
		
		partirMinuterie(CT_DIXIEME_SECONDE);
		
		while ( minuterieExpiree == 0 && boutonPoussoir == 0 ){}
		
		cli();
		
		DEL_GREEN();
		_delay_ms(500);
		DEL_OFF();
		_delay_ms(2000);
		
		for(uint8_t i = 0; i < dixiemes_secondes/2; i++){
			DEL_RED();
			_delay_ms(250);
			DEL_OFF();
			_delay_ms(250);
		}
		DEL_GREEN();
		_delay_ms(1000);
		DEL_OFF();
		
		sei();
	}
    return 0;
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


