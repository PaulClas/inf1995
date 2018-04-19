#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Son.h"

uint8_t tableau[]={note45,note46,note47,note48,note49,note50,note51,
	note52,note53,note54,note55,note56,note57,note58,note59,note60,
	note61,note62,note63,note64,note65,note66,note67,note68,note69,
	note70,note71,note72,note73,note74,note75,note76,note77,note78,
	note79,note80,note81};
	
Son::Son(){
    initialisation();
    
}

void Son::arret() {
    OCR0A=0;
    TCCR0B=0;
    TCCR0A=0;
}

void Son::initialisation(){
   // DDRB |=0xFF;
    PORTB=0b00001000;
    TCNT0 = 0;
    TCCR0A=(1<<COM0A0)|(1<<WGM01); //mode ctc, toggle compare match
    TCCR0B=(1<<CS02); //starts the timer & prescaling (clk/256)
}

void Son::chansonDeFin(){
    OCR0A= tableau[5];
    _delay_ms(500);
    OCR0A = tableau[15];
    _delay_ms(500);
    OCR0A= tableau[30];
    _delay_ms(500);
    OCR0A = tableau[15];
    _delay_ms(500);
    arret();
}

void Son::jouerSon(uint8_t operande)
{
    if(45<= operande && operande <=81)
        OCR0A = tableau[operande-45];
    else
        arret();
}

void Son::son(){
    OCR0A= tableau[5];
    _delay_ms(50);
    arret();
}

void Son::pause(){
    arret();
    _delay_ms(100);
    initialisation();
}

void Son::chansonPoteau(){
    OCR0A= tableau[11];
    _delay_ms(200);
    pause();
    OCR0A = tableau[18];
    _delay_ms(200);
    pause();
    OCR0A= tableau[19];
    _delay_ms(200);
    pause();
    arret();
}

