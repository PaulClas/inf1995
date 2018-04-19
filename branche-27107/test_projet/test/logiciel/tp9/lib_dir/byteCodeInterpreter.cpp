
#include "byteCodeInterpreter.h"


#define DBT  0x01	// début
#define ATT  0x02	// attendre
#define DAL  0x44	// allumer la DEL
#define DET  0x45	// éteindre la DEL
#define SGO  0x48	// jouer une sonorité
#define SAR  0x09	// arrêter de jouer la sonorité
#define MAR0 0x60	// arrêter les moteurs		//REVOIR CAR SI ON FAIT MAR1 JUSTE LE 1 ARRETE
#define MAR1 0x61	// arrêter les moteurs		//////
#define MAV  0x62	// avancer
#define MRE  0x63	// reculer
#define TRD  0x64	// tourner à droite
#define TRG  0X65	// tourner à gauche
#define DBC  0xC0	// début de boucle
#define FBC  0xC1	// fin de boucle
#define FIN  0xFF	// fin

uint16_t adresse=0x02;
uint16_t ancienne_adresse;
uint8_t instruction;
uint8_t operande;
uint8_t nbBoucle;
bool dbt_lue = true;
bool fin_lue = false;
DEL del_(A);
uint8_t temp = 0;
BytecodeInterpreter::BytecodeInterpreter() {}
	
void BytecodeInterpreter::run(){
	mem_.lecture(0, &temp);
	mem_.lecture(1, &temp);
	while(!fin_lue){
		mem_.lecture(adresse++, &instruction);
		mem_.lecture(adresse++, &operande);
		dispatch_instruction(instruction, operande);		
	}
}

void BytecodeInterpreter::dispatch_instruction(uint8_t instruction, uint8_t operande){
	DDRA = 0xFF;
	switch(instruction){
		case(DBT): 
			exec_DBT();
			break;
		case(ATT):	
			exec_ATT(operande);
			break;
		case(DAL):
			exec_DAL(operande);
			break;
		case(DET): 
			exec_DET(operande);
			break;
		case(SGO):
			exec_SGO(operande);
			break;
		case(SAR):
			exec_SAR();
			break;
		case(MAR0):	
		case(MAR1):
			exec_MAR();
			break;
		case(MAV):
			exec_MAV(operande);
			break;
		case(MRE):
			exec_MRE(operande);
			break;
		case(TRD):
			exec_TRD();
			break;
		case(TRG):
			exec_TRG();
			break;
		case(DBC):
			ancienne_adresse = adresse;													
			nbBoucle = operande - 1;	
			break;
		case(FBC): 
			if(nbBoucle > 0)
			{
				adresse = ancienne_adresse;
				nbBoucle--; 
			}
			break;
		case(FIN):
			exec_FIN();
			fin_lue = true;
			break;
		}
	}



void BytecodeInterpreter::exec_DBT(){
	for (int i = 0; i < 5; i++) {
		del_.DEL_RED();
		_delay_ms(500);
		del_.DEL_GREEN();
		_delay_ms(500);
	}
	del_.DEL_OFF();	
}
void BytecodeInterpreter::exec_ATT(uint8_t operande){
	
	for (int i = 0; i < operande; i++) {
		_delay_ms(25);
	}
}

void BytecodeInterpreter::configTimer1(){
	
	moteur_.initialisation();
	
}

void BytecodeInterpreter::exec_DAL(uint8_t operande){
	
	del_.DEL_RED();
	
	switch (operande){
		case(0x00):
			del_.DEL_OFF();
			break;
		case(0x01):
			del_.DEL_RED();
			break;
		case(0x02):
			del_.DEL_GREEN();
			break;
		default:
			del_.DEL_RED();
			//del_.DEL_AMBRE(); //Pour être allumé en d'autre couleur...
		}

}

void BytecodeInterpreter::exec_DET(uint8_t operande){
	del_.DEL_OFF();
}

void BytecodeInterpreter::exec_SGO(uint8_t operande){

	son_.initialisation();
	son_.jouerSon(operande);	
}
void BytecodeInterpreter :: exec_FIN(){
	son_.initialisation();
	son_.chansonDeFin();
	son_.arret();
}

void BytecodeInterpreter::exec_SAR(){

	son_.arret();
	
}
	
	
void BytecodeInterpreter::exec_MAR(){
	
	moteur_.arreter();
	
}
	
void BytecodeInterpreter::exec_MAV(uint8_t operande){
	
	moteur_.avancer(operande);
	
}
	
void BytecodeInterpreter::exec_MRE(uint8_t operande){
	
	moteur_.reculer(operande);
	
}

void BytecodeInterpreter::exec_TRD(){
	
	moteur_.turnRight();
}

void BytecodeInterpreter::exec_TRG(){
	
	moteur_.turnLeft();
}

