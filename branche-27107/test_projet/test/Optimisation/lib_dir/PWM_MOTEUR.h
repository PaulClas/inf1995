#ifndef PWM_MOTEUR_H
#define PWM_MOTEUR_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/*
* PWM phase and frequency correct avec options ICRn et set OCR1x en downcounting sans prescaler;
*/

class PWM_MOTEUR{
  public:
    PWM_MOTEUR(bool roue);
    void initialisation();
    void startPWM_Moteur(uint8_t percent);
    void stopPWM_Moteur();
  private:
    bool roue_;
    uint8_t top_;
};
#endif /* PWM_MOTEUR_H */
