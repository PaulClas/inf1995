#include "Moteur.h"

PWM_MOTEUR_DIAG moteur_D(true);
PWM_MOTEUR_DIAG moteur_G(false);


void Moteur::avancerdroite(uint8_t operande)
{
	PORTD |= (1<<PD5);
	PORTD &= ~(1<<PD7);
	moteur_D.startPWM_Moteur(operande);
}

void Moteur::tourner180(bool side){
    if(side == true){
        turnRight();
        _delay_ms(1500);
        arreter();
    }
    else {
        turnLeft();
        _delay_ms(1500);
        arreter();
    }
}
void Moteur::avancergauche(uint8_t operande)
{
	PORTD |= (1<<PD4);
	PORTD &= ~(1<<PD6);
	moteur_G.startPWM_Moteur(operande);
}

void Moteur::arreterdroite()
{
	PORTD &= ~(1<<PD5);
	PORTD &= ~(1<<PD7);
	moteur_D.stopPWM_Moteur();

}

void Moteur::arretergauche()
{
	PORTD &= ~(1<<PD4);
	PORTD &= ~(1<<PD6);
	moteur_G.stopPWM_Moteur();
}

void Moteur::reculerdroite(uint8_t operande)
{
	PORTD |= (1<<PD5) | (1<<PD7);
	moteur_D.startPWM_Moteur(operande);
}

void Moteur::reculergauche(uint8_t operande)
{
	PORTD |= (1<<PD4) | (1<<PD6);
	moteur_G.startPWM_Moteur(operande);
}

Moteur::Moteur(){
	initialisation();
}

void Moteur::initialisation(){
    DDRD |= 0xF0;
    moteur_G.initialisation();
    moteur_D.initialisation();
}
void Moteur::avancer(uint8_t operande){
   avancergauche(operande);
   avancerdroite(operande);
}

void Moteur::arreter(){
   arreterdroite();
   arretergauche();

}
void Moteur::reculer (uint8_t operande){

   reculergauche(operande);
   reculerdroite(operande);
}
void Moteur::turnRight(){
   avancergauche(150);
   reculerdroite(100);//reculer

}

void Moteur::turnLeft(){
  reculergauche(100);
  avancerdroite(150);
}

void Moteur::slightTurnRight(){
	avancergauche(100);
    _delay_ms(400);
    arreter();
    //moteur_D.startPWM_Moteur(200);//reculer
}
void Moteur::slightTurnLeft() {
	avancerdroite(100);
	_delay_ms(400);
	arreter();
}

void Moteur::mediumTurnRight(){
    turnRight();
    _delay_ms(400);
    arreter();
}

void Moteur::mediumTurnLeft(){
    turnLeft();
    _delay_ms(400);
    arreter();
}
