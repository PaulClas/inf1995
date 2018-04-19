#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "UART.h"
#include "MoteurDiag.h"
#ifndef _GESTIONNAIREMOTEUR_H
#define _GESTIONNAIREMOTEUR_H

class GestionnaireMoteur{

public:
	GestionnaireMoteur();
	void moteurDroite(uint8_t pourcentage);
	void moteurGauche(uint8_t pourcentage);
private:
	MoteurDiag moteur_;
};

#endif
