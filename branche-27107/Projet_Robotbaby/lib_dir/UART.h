#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include <util/delay.h>



class UART {
public:

	//const bool CAPTEUR_GAUCHE = true;
	//const bool CAPTEUR_DROITE = false;
	UART();
    void initialisation_UART ();
    void transmit_UART(uint8_t byte);
    void transmit_UART_number(uint16_t n);
    void transmit_UART_nombre(uint8_t n);
	uint8_t USART_Receive(void);
	void transmit_identification();
	void transmit_capteur(bool coteCapteur);
};

#endif // UART_H
