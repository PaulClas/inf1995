#include "PWM_MOTEUR_DIAG.h"

#ifndef MoteurDiag_h
#define MoteurDiag_h

class MoteurDiag{
public:
    MoteurDiag();
    void avancerdroite(uint8_t operande);
    void avancergauche(uint8_t operande);
    void reculerdroite(uint8_t operande);
    void reculergauche(uint8_t operande);
    void arreterdroite();
    void arretergauche();
    void initialisation();
    void avancer(uint8_t operande);
    void arreter();
    void reculer(uint8_t operande);
    void turnRight();
    void turnLeft();
    //ancier moteur.h
    //void initialisation();
    void C_avancer(uint8_t operande);
    void C_arreter();
    void C_reculer(uint8_t operande);
    void C_turnRight();
    void C_turnLeft();
    void C_slightTurnRight();
    void C_slightTurnLeft();


};

#endif /* Header_h */

