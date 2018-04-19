#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "PWM_MOTEUR.h"

#ifndef Header_h
#define Header_h

class Moteur{
public:
    Moteur();
    void initialisation();
    void avancer(uint8_t operande);
    void arreter();
    void reculer(uint8_t operande);
    void turnRight();
    void turnLeft();


};

#endif /* Header_h */
