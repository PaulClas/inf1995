#include "DEL.h"

/*Constructeur de DEL qui prend en parametre la lettre identifiant le port*/
//DEL::DEL(){}
DEL::DEL(PORTx portx): port_(portx)
{
}



/***********************************************************************
 *
 **********************************************************************/
void DEL::DEL_RED()
{
		switch (port_) {
			case A:
				PORTA = 0x02;
			case B:
				PORTB = 0x02;
			case C:
				PORTC = 0x02;
			case D:
				PORTD = 0x02;
		}

}
/***********************************************************************
 *
 **********************************************************************/
void DEL::DEL_GREEN()
{
	switch (port_) {
		case A:
			PORTA = 0x01;
		case B:
			PORTB = 0x01;
		case C:
			PORTC = 0x01;
		case D:
			PORTD = 0x01;
	}
}
/***********************************************************************
 *
 **********************************************************************/
void DEL::DEL_OFF()
{
	switch (port_) {
		case A:
			PORTA = 0x00;
		case B:
			PORTB = 0x00;
		case C:
			PORTC = 0x00;
		case D:
			PORTD = 0x00;
	}
}
/***********************************************************************
 *
 **********************************************************************/
void DEL::DEL_AMBRE()
{
        DEL_RED();
        _delay_ms(3);
        DEL_GREEN();
        _delay_ms(7);
}
