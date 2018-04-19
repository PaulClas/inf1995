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

volatile State boutonPoussoir = OFF;

ISR (INT0_vect) {
	
	UART uart_;
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
   switch(boutonPoussoir){
			
			case ON:
				uart_.transmit_UART(0xf5);
				uart_.transmit_UART(0x00);
				break;
			case OFF:
				uart_.transmit_UART(0xf5);
				uart_.transmit_UART(0x01);
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
			case 0xf8:
				mo.moteurGauche(operande);
				break;
			case 0xf9:
				mo.moteurDroite(operande);
				break;
			case 0xfb:
				uart.transmit_identification();
				break;
			case 0xfa:
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
    //DDRB = 0xff;
    DDRD |= 0xF0;
    
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

int main(){
	DDRB = 0xff;
	Init();
	initialisationInterrupt();
	UART uart;
	
	while(1){
		uart.transmit_capteur(CAPTEUR_GAUCHE);
		uart.transmit_capteur(CAPTEUR_DROITE);
	}

}

