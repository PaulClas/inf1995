#include "GestionnaireDEL.h"

enum couleurDEL{GREEN = 0x01,RED = 0x02};

GestionnaireDEL::GestionnaireDEL(){
	
}

void GestionnaireDEL::changerCouleur(uint8_t color){
	
	DEL del_(B);
	
	switch (color){
		case GREEN:
			del_.DEL_GREEN();
			break;
		case RED:
			del_.DEL_RED();
			break;
		default:
			del_.DEL_OFF();
			break;
	}
	
}
