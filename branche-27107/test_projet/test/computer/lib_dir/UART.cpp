#include "UART.h"
#include "can.h"
#include "ID.h"
#include <stdio.h>

const bool CAPTEUR_GAUCHE = true;
const bool CAPTEUR_DROITE = false;

UART::UART(){
    initialisation_UART();
}
void UART::initialisation_UART ()
{
	//cli();
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0) | (1<<RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    
   // sei();
}

void UART::transmit_UART(uint8_t byte)
{
    while( !(UCSR0A &(1<<UDRE0))){}
    
    UDR0=byte;
}
uint8_t UART:: USART_Receive(void){
		while (!(UCSR0A & (1 << RXC0)));
		return UDR0;
}
void UART::transmit_UART_number(uint16_t n)
{
    char buff[100];
    sprintf(buff, "number is %u\n", n);
    for(int i =0; i<20; i++){
        transmit_UART(buff[i]);
    }
}


void UART::transmit_identification()
{
	
	ID id;
	
	for(uint8_t i = 0; i<sizeof(id.getInformations().nomRobot);i++){
		transmit_UART(id.getInformations().nomRobot[i]);
	}
	for(uint8_t i = 0; i<sizeof(id.getInformations().numeroEquipe);i++){
		transmit_UART(id.getInformations().numeroEquipe[i]);
	}
	for(uint8_t i = 0; i<sizeof(id.getInformations().numeroSection);i++){
		transmit_UART(id.getInformations().numeroSection[i]);
	}
	for(uint8_t i = 0; i<sizeof(id.getInformations().session);i++){
		transmit_UART(id.getInformations().session[i]);
	}
	for(uint8_t i = 0; i<sizeof(id.getInformations().couleurBase);i++){
		transmit_UART(id.getInformations().couleurBase[i]);
	}
   
}

void UART::transmit_capteur(bool coteCapteur){
	
	can ca;
	uint16_t valeurAnalogique;
	
	if(coteCapteur == CAPTEUR_GAUCHE){
		valeurAnalogique = ca.lecture(0x02);
		transmit_UART(0xf6);
	}
	else{
		valeurAnalogique = ca.lecture(0x00); //capteur droite
		transmit_UART(0xf7);
	}
	
	uint8_t valeurCentimetre;
	
		if(valeurAnalogique < 82)
			valeurCentimetre = 80;
		else if(valeurAnalogique < 84)
			valeurCentimetre = 75;
		else if(valeurAnalogique < 115)
			valeurCentimetre = 70;
		else if(valeurAnalogique < 129)
			valeurCentimetre = 65;
		else if(valeurAnalogique < 143)
			valeurCentimetre = 60;
		else if(valeurAnalogique < 164)
			valeurCentimetre = 55;
		else if(valeurAnalogique < 187)
			valeurCentimetre = 50;
		else if(valeurAnalogique < 206)
			valeurCentimetre = 45;
		else if(valeurAnalogique < 225)
			valeurCentimetre = 40;
		else if(valeurAnalogique < 237)
			valeurCentimetre = 35;
		else if(valeurAnalogique < 258)
			valeurCentimetre = 30;
		else if(valeurAnalogique < 274)
			valeurCentimetre = 25;
		else if(valeurAnalogique < 305)
			valeurCentimetre = 20;
		else if(valeurAnalogique < 391)
			valeurCentimetre = 15;
		else if(valeurAnalogique < 554)
			valeurCentimetre = 10;
		else
			valeurCentimetre = 5;
				
		//transmit_UART(0xf7);
		transmit_UART(valeurCentimetre);
	
	
}

