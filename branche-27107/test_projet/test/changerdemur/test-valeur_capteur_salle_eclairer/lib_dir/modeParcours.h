#ifndef MODEPARCOURS_H
#define MODEPARCOURS_H

#include <avr/io.h>
#include 

class ModeParcours {

	public :
		ModeParcours();
		void run();
		//void dispatch_instruction(uint8_t instruction, uint8_t operande);
		void configTimer1();
		void longerMur(uint16_t valeurAnalogiqueDroite, uint16_t valeurAnalogiqueGauche);
		void faire180surMur(uint16_t valeurAnalogiqueDroite, uint16_t valeurAnalogiqueGauche);
		void routinePoteau(uint16_t valeurAnalogiqueDroite, uint16_t valeurAnalogiqueGauche);
		void longerAutreMur(uint16_t valeurAnalogiqueDroite, uint16_t valeurAnalogiqueGauche);
		void changerMur(uint16_t valeurAnalogiqueDroite, uint16_t valeurAnalogiqueGauche);
	private :
		// DEL del_;
		Son son_;
		Moteur moteur_;
		Memoire24CXXX mem_;
		bool autreMur;
		bool murLongePresent;
		bool poteauDetecte
		bool routineterminer

};

#endif /* MODEPARCOURS_H */
