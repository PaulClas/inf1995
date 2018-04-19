#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include "memoire_24.h"
#include "UART.h"
#include "Son.h"
#include "Moteur.h"
#include "DEL.h"


int main(){
	UART uart;
	
	Moteur moteur;
	
	DEL del(A);
	
	//moteur.avancer(255);
	//_delay_ms(2000);
	
	char nomRobot[9] = {'R', 'o', 'b', 'o', 't', 'b', 'a', 'b', 'y'};
	uart.transmit_UART(0xf0); //Nom
	for( uint8_t i = 0; i < sizeof(nomRobot); i++){
      uart.transmit_UART(nomRobot[i]);
	}
   
	uart.transmit_UART(0xf1); //equipe
	char numeroEquipe[5] = {'2', '7', '1', '0', '7'};
	for( uint8_t i = 0; i < sizeof(numeroEquipe); i++){
      uart.transmit_UART(numeroEquipe[i]);
	}
	
	uart.transmit_UART(0xf2); //groupe
	char numeroSection = 0x02;
    uart.transmit_UART(numeroSection);
	
	uart.transmit_UART(0xf3); //session
	char session[4] = {'1', '8', '-', '1'};
	for( uint8_t i = 0; i < sizeof(session); i++){
      uart.transmit_UART(session[i]);
	}
	
	uart.transmit_UART(0xf4); //base
	uint8_t couleurBase = 0x01; //Couleur noire, normal que les lignes soient blanches
    uart.transmit_UART(couleurBase);

	
	uart.transmit_UART(0xf5); //interrupt;
	uint8_t etatInterrupt = 0x00;
    uart.transmit_UART(etatInterrupt);
		
		
	uart.transmit_UART(0xf6); //interrupt;
	uint8_t distanceCapteur_G = 80;
    uart.transmit_UART(distanceCapteur_G);
    
    uart.transmit_UART(0xf7); //interrupt;
	uint8_t distanceCapteur_D = 25;
    uart.transmit_UART(distanceCapteur_D);
	
	
	DDRA = 0xff;
	
	for(;;){
	
    uint8_t octet1 = uart.USART_Receive();
    uint8_t octet2 = uart.USART_Receive();
    
    switch(octet1){
		case(0xf8):
		
			if(octet2 > 0x00)
				moteur.avancer(octet2);
			else if(octet2 < 0x00)
				moteur.reculer(octet2);
			else
				moteur.arreter();
				break;
		case(0xf9):	
			if(octet2 > 0)
				moteur.avancer(octet2);
			else if(octet2 < 0)
				moteur.reculer(octet2);
			else
				moteur.arreter();
			break;
		case(0xfa):
			del.DEL_RED();
			break;
		case(0xfb): 
			moteur.avancer(octet2);
			break;
		}
    }
	
	 //interrupt;
	
	/*Son son;
	
	son.initialisation();
	
	son.chansonDeFin();
	
	Memoire24CXXX mem;
	
   
    uint8_t octet =0x00;
    
    uint8_t adresse=0;
    
    while(true){
		
		octet = uart.USART_Receive();
        mem.ecriture(adresse, octet);
        adresse++;
		
		}*/
	
    return 0; 
}
	

