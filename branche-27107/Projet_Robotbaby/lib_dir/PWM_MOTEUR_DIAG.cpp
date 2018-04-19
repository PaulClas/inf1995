#include "PWM_MOTEUR_DIAG.h"

PWM_MOTEUR_DIAG::PWM_MOTEUR_DIAG(){
	
}

PWM_MOTEUR_DIAG::PWM_MOTEUR_DIAG(bool roue):roue_(roue){
	
	initialisation();
}

void PWM_MOTEUR_DIAG::initialisation(){

	//top_= 0x00FF;

	TCNT1 = 0;
	TCCR1B |= (1 << CS12); //| (1 << CS10);
	TCCR1A |= (1 << WGM10);//|(1 << COM1A1) | (1 << COM1B1) | (0 << COM1A0) | (0 << COM1B0);
	//TIMSK1 |= (1 << OCIE1B) | (1 << OCIE1A);


}

void PWM_MOTEUR_DIAG::startPWM_Moteur(uint8_t percent){


	if(roue_ == true){				//roue droite
		TCCR1A |= (1 << COM1A1);
		OCR1A = percent;
	}
	else{							//roue gauche
		TCCR1A |= (1 << COM1B1);
		OCR1B = percent;
	}
}

void PWM_MOTEUR_DIAG::stopPWM_Moteur(){

	if(roue_ == true){
	  TCCR1A &= ~(1 << COM1A1);
	}
	else{
	   TCCR1A &= ~(1 << COM1B1);
	}
}
