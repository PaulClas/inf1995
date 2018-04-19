#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
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
    void slightTurnRight();
    void slightTurnLeft();

};

#endif /* Header_h */
