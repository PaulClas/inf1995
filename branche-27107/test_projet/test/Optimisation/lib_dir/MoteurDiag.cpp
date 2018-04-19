#include "MoteurDiag.h"

PWM_MOTEUR_DIAG moteur_D(true);
PWM_MOTEUR_DIAG moteur_G(false);


void MoteurDiag::avancerdroite(uint8_t operande)
{
	PORTD |= (1<<PD5);
	PORTD &= ~(1<<PD7);
	moteur_D.startPWM_Moteur(operande);
}

void MoteurDiag::avancergauche(uint8_t operande)
{
	PORTD |= (1<<PD4);
	PORTD &= ~(1<<PD6);
	moteur_G.startPWM_Moteur(operande);
}

void MoteurDiag::arreterdroite()
{
	PORTD &= ~(1<<PD5);
	PORTD &= ~(1<<PD7);
	moteur_D.stopPWM_Moteur();

}

void MoteurDiag::arretergauche()
{
	PORTD &= ~(1<<PD4);
	PORTD &= ~(1<<PD6);
	moteur_G.stopPWM_Moteur();
}

void MoteurDiag::reculerdroite(uint8_t operande)
{
	PORTD |= (1<<PD5) | (1<<PD7);
	moteur_D.startPWM_Moteur(operande);
}

void MoteurDiag::reculergauche(uint8_t operande)
{
	PORTD |= (1<<PD4) | (1<<PD6);
	moteur_G.startPWM_Moteur(operande);
}

MoteurDiag::MoteurDiag(){
	initialisation();
}

void MoteurDiag::initialisation(){
    DDRD |= 0xF0;
    moteur_G.initialisation();
    moteur_D.initialisation();
}
void MoteurDiag::avancer(uint8_t operande){
   avancergauche(operande);
   avancerdroite(operande-75);
}

void MoteurDiag::arreter(){	
   arreterdroite();
   arretergauche();

}
void MoteurDiag::reculer (uint8_t operande){
	
   reculergauche(operande);
   reculerdroite(operande-50);
}
void MoteurDiag::turnRight(){
   avancergauche(200);
   reculerdroite(200);//reculer

}

void MoteurDiag::turnLeft(){
  reculergauche(200);
  avancerdroite(200);
  _delay_ms(950);
}

void MoteurDiag::slightTurnRight(){
    moteur_G.startPWM_Moteur(100);
    _delay_ms(100);
    moteur_G.stopPWM_Moteur();
    //moteur_D.startPWM_Moteur(200);//reculer
}

void MoteurDiag::mediumTurnRight(){
    turnRight();
    _delay_ms(500);
    arreter();
}

void MoteurDiag::mediumTurnLeft(){
    turnLeft();
    _delay_ms(500);
    arreter();
}

