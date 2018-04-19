#include <avr/io.h>
#include <util/delay.h>
#ifndef _IDENTIFICATION_
#define _IDENTIFICATION_


class Identification{
	
	puclic:
		Identification();
		void transmettreInfo();
		uint8_t getEtatInterrupt();
		uint8_t getdistanceCapteurG();
		uint8_t getdistanceCapteurD();

	private:
		char nomRobot_[9];
		char numeroEquipe_[5];
		char numeroSection_;
		char session_[4];
		uint8_t couleurBase_;
		uint8_t etatInterrupt_;
		uint8_t distanceCapteurG_;
		uint8_t distanceCapteurD_;
};
