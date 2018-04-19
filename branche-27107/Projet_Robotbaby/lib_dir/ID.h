#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "UART.h"

enum transfert{transfertNom = 0xf0,
			transfertEquipe = 0xf1,
			tranfertGroupe = 0xf2,
			transfertSession = 0xf3,
			transfertCouleurBase = 0xf4
};
		
struct Info{
	char nomRobot[10] = {transfertNom,'R', 'o', 'b', 'o', 't', 'b', 'a', 'b', 'y'};
	char numeroEquipe[6] = {transfertEquipe,'2', '7', '1', '0', '7'};
	char numeroSection[2] = {tranfertGroupe, 0x02};
	char session[5] = {transfertSession,'1', '8', '-', '1'};
	char couleurBase[2] = {transfertCouleurBase,0x01};
};

#ifndef ID_H
#define ID_H

class ID{
	
	public:
		ID();
		Info getInformations();
			
	private:
		Info id_;
};

#endif
