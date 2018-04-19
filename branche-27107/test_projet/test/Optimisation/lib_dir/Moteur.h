#include "PWM_MOTEUR_DIAG.h"

#ifndef Moteur_h
#define Moteur_h

class Moteur{
public:
    Moteur();
    void avancerdroite(uint8_t operande);
    void avancergauche(uint8_t operande);
    void reculerdroite(uint8_t operande);
    void reculergauche(uint8_t operande);
    void arreterdroite();
    void arretergauche();
    void initialisation();
    void tourner180(bool side);
    void avancer(uint8_t operande);
    void arreter();
    void reculer(uint8_t operande);
    void turnRight();
    void turnLeft();
    void slightTurnRight();
    void slightTurnLeft();
    void mediumTurnRight();
    void mediumTurnLeft();


};

#endif /* Header_h */
