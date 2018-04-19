#include "PWM_MOTEUR.h"

PWM_MOTEUR::PWM_MOTEUR(bool roue):roue_(roue){
	
	initialisation();
}

void PWM_MOTEUR::initialisation(){

	//top_= 0x00FF;

	TCNT1 = 0;
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TCCR1A |= (1 << WGM10);
	TIMSK1 |= (1 << OCIE1B) | (1 << OCIE1A);


}

void PWM_MOTEUR::startPWM_Moteur(uint8_t percent){

	//uint8_t val = 255*percent/100;

	if(roue_ == true){				//roue droite
		TCCR1A |= (1 << COM1A1);
		OCR1A = percent;
	}
	else{							//roue gauche
		TCCR1A |= (1 << COM1B1);
		OCR1B = percent;
	}
}

void PWM_MOTEUR::stopPWM_Moteur(){

	if(roue_ == true){
	  TCCR1A &= ~(1 << COM1A1);
	}
	else{
	   TCCR1A &= ~(1 << COM1B1);
	}
}
