#include "MoteurDiag.h"

PWM_MOTEUR_DIAG moteurDiag_D(true);
PWM_MOTEUR_DIAG moteurDiag_G(false);


void MoteurDiag::avancerdroite(uint8_t operande)
{
	PORTD |= (1<<PD5);
	PORTD &= ~(1<<PD7);
	moteurDiag_D.startPWM_Moteur(operande);
}

void MoteurDiag::avancergauche(uint8_t operande)
{
	PORTD |= (1<<PD4);
	PORTD &= ~(1<<PD6);
	moteurDiag_G.startPWM_Moteur(operande);
}

void MoteurDiag::arreterdroite()
{
	PORTD &= ~(1<<PD5);
	PORTD &= ~(1<<PD7);
	moteurDiag_D.stopPWM_Moteur();

}

void MoteurDiag::arretergauche()
{
	PORTD &= ~(1<<PD4);
	PORTD &= ~(1<<PD6);
	moteurDiag_G.stopPWM_Moteur();
}

void MoteurDiag::reculerdroite(uint8_t operande)
{
	PORTD |= (1<<PD5) | (1<<PD7);
	moteurDiag_D.startPWM_Moteur(operande);
}

void MoteurDiag::reculergauche(uint8_t operande)
{
	PORTD |= (1<<PD4) | (1<<PD6);
	moteurDiag_G.startPWM_Moteur(operande);
}

MoteurDiag::MoteurDiag(){
	initialisation();
}

void MoteurDiag::initialisation(){
    DDRD |= 0xF0;
    moteurDiag_G.initialisation();
    moteurDiag_D.initialisation();
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
   _delay_ms(950);
}

void MoteurDiag::turnLeft(){
  reculergauche(200);
  avancerdroite(200);
  _delay_ms(950);
}

void MoteurDiag::C_avancer(uint8_t operande){
	PORTD = 0x30;
  moteurDiag_G.startPWM_Moteur(operande);
  moteurDiag_D.startPWM_Moteur(operande);
}

void MoteurDiag::C_arreter(){
	PORTD = 0x00;	
	moteurDiag_D.stopPWM_Moteur();
	moteurDiag_G.stopPWM_Moteur();
}

void MoteurDiag::C_reculer(uint8_t operande){
	PORTD = 0xF0;
	moteurDiag_G.startPWM_Moteur(operande);
	moteurDiag_D.startPWM_Moteur(operande);
}
	
void MoteurDiag::C_turnRight(){
	PORTD=0xB0;
	moteurDiag_G.startPWM_Moteur(200);
	moteurDiag_D.startPWM_Moteur(200);//reculer
	_delay_ms(950);
}
	
void MoteurDiag::C_turnLeft(){
	PORTD = 0x70;
	moteurDiag_G.startPWM_Moteur(200);
	moteurDiag_D.startPWM_Moteur(200);
	_delay_ms(950);
	
}
void MoteurDiag::C_slightTurnRight(){
	PORTD=0xB0;
	moteurDiag_G.startPWM_Moteur(120);
	moteurDiag_D.startPWM_Moteur(100);
	//_delay_ms(100);
	//moteurDiag_G.stopPWM_Moteur();
}

void MoteurDiag::C_slightTurnLeft(){
	PORTD = 0x70;
	//moteur_G.startPWM_Moteur(200);
	moteurDiag_D.startPWM_Moteur(130);
	moteurDiag_G.startPWM_Moteur(100);
	//_delay_ms(100);
}


