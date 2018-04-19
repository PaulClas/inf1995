#include "Moteur.h"

PWM_MOTEUR moteur_D(true);
PWM_MOTEUR moteur_G(false);

Moteur::Moteur(){
	initialisation();
}

void Moteur::initialisation(){
    DDRD |= 0xF0;
    moteur_G.initialisation();
    moteur_D.initialisation();
}
void Moteur::avancer(uint8_t operande){
  PORTD = 0x30;
  moteur_G.startPWM_Moteur(operande);
  moteur_D.startPWM_Moteur(operande);

}

void Moteur::arreter(){
	
	PORTD = 0x00;	
	moteur_D.stopPWM_Moteur();
	moteur_G.stopPWM_Moteur();

}
void Moteur::reculer (uint8_t operande){
	
	PORTD = 0xF0;

	moteur_G.startPWM_Moteur(operande);
	moteur_D.startPWM_Moteur(operande);

	}
void Moteur::turnRight(){
	PORTD=0xB0;
	moteur_G.startPWM_Moteur(150);
	moteur_D.startPWM_Moteur(150);//reculer
	_delay_ms(950);
}

void Moteur::turnLeft(){
	PORTD = 0x70;
  moteur_G.startPWM_Moteur(150);
  moteur_D.startPWM_Moteur(150);
  _delay_ms(950);
}

void Moteur::slightTurnRight(){
	PORTD=0xB0;
	moteur_G.startPWM_Moteur(100);
	_delay_ms(100);
	
}
void Moteur::slightTurnLeft(){
	PORTD = 0x70;
	moteur_D.startPWM_Moteur(100);
	_delay_ms(100);

}

void Moteur::tourner180(bool side){
    if(side == true){
        turnRight();
        _delay_ms(400);
        arreter();
    }
    else {
        turnLeft();
        _delay_ms(400);
        arreter();
    }
}



