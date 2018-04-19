

#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include "memoire_24.h"
#include "UART.h"


int main(){
	UART uart;
	
	Memoire24CXXX mem;
	
   // uint8_t nb_octets_MSB = uart.USART_Receive();
   // uint8_t nb_octets_LSB = uart.USART_Receive();
    
  //  uint16_t nb_octets = (nb_octets_MSB << 8) | nb_octets_LSB ;
    uint8_t octet =0x00;
    
    //mem.ecriture(0,nb_octets_MSB);
    //mem.ecriture(1,nb_octets_LSB);
    
    uint8_t adresse=0;
    
    while(true){
		
		octet = uart.USART_Receive();
        mem.ecriture(adresse, octet);
        adresse++;
		
		}
	
    /*for (uint8_t i = 2; i < nb_octets; i++) {
		octet = uart.USART_Receive();
        mem.ecriture(i, octet);
    }*/
    return 0; 
}
	

