#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "memoire_24.h"

void lightOnRed();
void lightOnGreen();
void lightOff();

/**
* The main function. It does the logic.
*/
int main()
{
	DDRA = 0x03;

	Memoire24CXXX memoire = Memoire24CXXX();

	uint8_t stringInitial[] = "*E*C*O*L*E* *P*O*L*Y*T*E*C*H*N*I*Q*U*E*";

	mem.ecriture(0, stringInitial, 40);
	_delay_ms(5);

	uint8_t stringAComparer[];

	mem.lecture(0, stringAComparer, 40);

	uint8_t comparer = 0;

	for (uint8_t i = 0; i < 40; i++) {
		if (stringAComparer[i] != stringInitial[i]) {
			comparer = 1;
		}
	}

	if (comparer) {
			lightOnRed();
			_delay_ms(10000);
	}
	else {
			lightOnGreen();
			_delay_ms(10000);
	}

	return 0;
}

void lightOff()
{
	PORTA = 0x0;
}
void lightOnRed()
{
	PORTA = 0x1;

}
void lightOnGreen()
{
	PORTA = 0x2;
}
