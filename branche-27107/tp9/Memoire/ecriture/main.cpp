

#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include "memoire_24.h"
#include "UART.h"


int main(){
	UART uart;
	
	Memoire24CXXX mem;
	
   
    uint8_t octet =0x00;
    
    uint8_t adresse=0;
    
    while(true){
		
		octet = uart.USART_Receive();
        mem.ecriture(adresse, octet);
        adresse++;
		
		}
	
    return 0; 
}
	

