#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include "UART.h"
#include "DEL.h"
#include "GestionnaireDEL.h"
#include "GestionnaireMoteur.h"
#include "can.h"
#include "ID.h"


enum State {ON, OFF};

enum Instruction {ControleMoteurGauche = 0xf8, ControleMoteurDroite = 0xf9 ,
	ControleDEL = 0xfa, DemandeIdentification = 0xfb, EtatInterrupt = 0xf5};

static const bool CAPTEUR_DROITE = true;
static const bool CAPTEUR_GAUCHE = false;

volatile State boutonPoussoir = OFF;

ISR (INT0_vect) {
	
	UART uart_;
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
   switch(boutonPoussoir){
			
			case ON:
				uart_.transmit_UART(EtatInterrupt);
				uart_.transmit_UART(0x00); //Bouton ferme sur image
				break;
			case OFF:
				uart_.transmit_UART(EtatInterrupt);
				uart_.transmit_UART(0x01); //Bouton ouvert sur image
				break;
	}		
    EIFR |= (1 << INTF0);
}



	
ISR (USART0_RX_vect) {
	
	UART uart;
	GestionnaireDEL light;
	GestionnaireMoteur mo;
	
	
	cli();
		uint8_t instruction = uart.USART_Receive();
		uint8_t operande = uart.USART_Receive();
		
		switch(instruction){
			case ControleMoteurGauche:
				mo.moteurGauche(operande);
				break;
			case ControleMoteurDroite:
				mo.moteurDroite(operande);
				break;
			case DemandeIdentification:
				uart.transmit_identification();
				break;
			case ControleDEL:
				light.changerCouleur(operande);
				break;
			}
	sei();
	
	

}
	

void initialisationInterrupt(){
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli ();
    
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRD |= 0xF0;
    //DDRB = 0xFF;
    
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0) ;
    
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC00) ;
    
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}


void Init(){

	//Cette fonction ne comporte rien, mais initialise le ISR du UART
	cli();
	
	sei();
	
}

static void runDiagnostique(){
	DDRB = 0xff;
    Init();
	//while(true);
    //while(true);
    //cli();
    initialisationInterrupt();
    //sei();
	UART uart;
	while(true){
		uart.transmit_capteur(CAPTEUR_GAUCHE);
		uart.transmit_capteur(CAPTEUR_DROITE);
	}

}

