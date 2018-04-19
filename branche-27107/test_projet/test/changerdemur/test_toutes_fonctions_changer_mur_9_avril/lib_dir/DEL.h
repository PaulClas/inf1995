#ifndef DEL_H
#define DEL_H

#include <avr/io.h>
#include <util/delay.h>
/******************************************************************************
* Class DEL permet d'allumer une del selon le port
******************************************************************************/
enum PORTx {A, B, C, D};
class DEL{

	public:
	
	
		//DEL();
		DEL(PORTx portx);

		void DEL_RED();

		void DEL_GREEN();

		void DEL_OFF();

		void DEL_AMBRE();

	private:

		PORTx port_;
};

#endif 
