#include "Identification.h"
#include "UART"

	Identification(){
		nomRobot_ = {'R', 'o', 'b', 'o', 't', 'b', 'a', 'b', 'y'};
		numeroEquipe_ = {'2', '7', '1', '0', '7'};
		numeroSection_ = 0x02;
		session_= {'1', '8', '-', '1'};
		couleurBase_ = 0x01; //Couleur noire, normal que les lignes soient blanches
		etatInterrupt_ = 0x01;
		distanceCapteurG_ = 0x00;
		distanceCapteurD_ = 0x00;
		
		}
	void transmettreInfo();
	uint8_t getEtatInterrupt();
	uint8_t getdistanceCapteurG(){
		UART uart
		uint8_t octet = uart.USART_Receive();
		uint8_t distance = octet/255*100;
		
		return distance;
		
		};
	uint8_t getdistanceCapteurD();

