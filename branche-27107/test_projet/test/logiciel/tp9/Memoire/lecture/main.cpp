//#include <avr/io.h>
//#include <string.h>
//#include "buttonTouch.h"
//#include "can.h"
//#include "DEL.h"
//#include "instruction.h"
//#include "memoire_24.h"
//#include "Minuterie.h"
//#include "PWM_MOTEUR.h"
#include "UART.h"
#include "byteCodeInterpreter.h"
//#include "Moteur.h"



int main(void){
	
	
	//BytecodeInterpreter bi;
	
	//bi.run();
	
    Memoire24CXXX memoire; 
    UART uart;
    for(uint8_t i=0; i<40; i++) {
        uint8_t  octet;
        memoire.lecture(i, &octet);
        uart.transmit_UART(octet);
    }
     	 
	return 0;
	

	
}
