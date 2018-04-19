#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include "memoire_24.h"
#include "UART.h"
#include "diagnostique.h"
#include "parcours.h"

Memoire24CXXX mem;
uint8_t mode = 0;
int main(){
	
    mem.lecture(0, &mode);
    if(mode==0){
		mode =1;
	}else if(mode ==1){
		mode =0;
	}
	else{
		mode=0;
	}
	
    mem.ecriture(0, mode);
    
    
	switch(mode){
		case 0:
			runDiagnostique();
		break;
		
		case 1:
			runParcours();
		break;
	}
	
   
    return 0; 
}

	
