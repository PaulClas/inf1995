#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include <util/delay.h>

class UART {
public:
	UART();
    void initialisation_UART ();
    void transmit_UART(uint8_t byte);
    void transmit_UART_number(uint16_t n);
	uint8_t USART_Receive(void);
};

#endif // UART_H
