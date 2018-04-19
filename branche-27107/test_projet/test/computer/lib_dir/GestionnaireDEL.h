#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "UART.h"
#include "DEL.h"
#ifndef _GestionnaireDEL_H_
#define _GestionnaireDEL_H_


class GestionnaireDEL {
	public:
		GestionnaireDEL();
		void changerCouleur(uint8_t color);
};

#endif
