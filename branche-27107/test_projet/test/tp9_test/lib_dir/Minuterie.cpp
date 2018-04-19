#include "Minuterie.h"


Minuterie::Minuterie(){
	
	minuterieExpiree_ = 0;
    dixiemesSecondes_ = 0;
}


void Minuterie::partirMinuterie ( uint16_t duree )
{
    minuterieExpiree_ = 0;
    dixiemesSecondes_ = 0;
    TCNT1 = 0;

    OCR1A = duree;
    TCCR1A = (1 << COM1A0) | (1 << COM1A1); 

    // mode CTC du timer
    TCCR1B |= (1 << WGM12);

    // Mettre le prescaler a 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    TCCR1C = 0;

    // Enable l'interruption TIMER1_COMPA
    TIMSK1 = (1 << OCIE1A);
}

void Minuterie::resetMinuterie ( uint16_t duree )
{
    // Disable l'interruption TIMER1_COMPA
    TIMSK1 = (0 << OCIE1A);
}

uint8_t Minuterie::getMinuterieExpiree()
{
	
	return minuterieExpiree_;
	
}

uint8_t Minuterie::getDixiemesSecondes()
{
	
    return dixiemesSecondes_;
	
}
