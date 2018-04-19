#include "Moteur.h"

PWM_MOTEUR moteur_D(true);
PWM_MOTEUR moteur_G(false);

Moteur::Moteur(){
	initialisation();
}

void Moteur::initialisation(){
    DDRD |= 0xFF;
    moteur_G.initialisation();
    moteur_D.initialisation();
}
void Moteur::avancer(uint8_t operande){
  PORTD = 0xF0;//PORTD =0xF0;
  moteur_G.startPWM_Moteur(operande);
  moteur_D.startPWM_Moteur(operande);
}

void Moteur::arreter(){
	
	PORTD = 0x00;	
	moteur_D.stopPWM_Moteur();
	moteur_G.stopPWM_Moteur();

}
void Moteur::reculer (uint8_t operande){
	
	PORTD = 0xFC;

	moteur_G.startPWM_Moteur(operande);
	moteur_D.startPWM_Moteur(operande);
	}
void Moteur::turnRight(){
	PORTD=0xF8;
	moteur_G.startPWM_Moteur(200);
	moteur_D.startPWM_Moteur(200);//reculer
	_delay_ms(950);
}

void Moteur::turnLeft(){
	PORTD = 0xF4;
  moteur_G.startPWM_Moteur(200);
  moteur_D.startPWM_Moteur(200);
  _delay_ms(950);
}
