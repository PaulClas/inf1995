#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void ajustementPWM ( uint8_t percent ) {
    // mise à un des sorties OC1A et OC1B sur comparaison
    
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
    // page 177 de la description technique du ATmega324PA)
    OCR1A = TOP*percent/100;
    OCR1B = TOP*percent/100;
    
    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1A =
    TCCR1B = 'modifier ici' ;
    TCCR1C = 0;
}

int main()
{
    DDRD = 0xff;
}
