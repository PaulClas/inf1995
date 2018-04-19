#include "GestionnaireMoteur.h"
GestionnaireMoteur::GestionnaireMoteur(){}
void  GestionnaireMoteur::moteurDroite(uint8_t pourcentage){

		switch(pourcentage){
		
			case 100:
				moteur_.avancerdroite(255);
				break;
				
			case 75:
				moteur_.avancerdroite(191);
				break;
			
			case 50:
				moteur_.avancerdroite(128);
				break;
			
			case 25:
				moteur_.avancerdroite(25*255/100);
				break;
				
			case 0:
				moteur_.arreterdroite();
				break;
				
			case 231:
				moteur_.reculerdroite(25*255/100);
				break;
			
			case 206:
				moteur_.reculerdroite(50*255/100);
				break;
			
			case 181:
				moteur_.reculerdroite(75*255/100);
				break;
			
			case 156:
				moteur_.reculerdroite(100*255/100);
				break;
			default:
				moteur_.arreterdroite();
				break;
			
		
		}

}

void GestionnaireMoteur::moteurGauche(uint8_t pourcentage){
	

		switch(pourcentage){
		
			case 100:
				moteur_.avancergauche(255);
				break;
				
			case 75:
				moteur_.avancergauche(75*255/100);
				break;
			
			case 50:
				moteur_.avancergauche(50*255/100);
				break;
			
			case 25:
				moteur_.avancergauche(25*255/100);
				break;
				
			case 0:
				moteur_.arretergauche();
				break;
				
			case 231:
				moteur_.reculergauche(25*255/100);
				break;
			
			case 206:
				moteur_.reculergauche(50*255/100);
				break;
			
			case 181:
				moteur_.reculergauche(75*255/100);
				break;
			
			case 156:
				moteur_.reculergauche(100*255/100);
				break;
			default:
				moteur_.arretergauche();
				break;
		
		}

}
