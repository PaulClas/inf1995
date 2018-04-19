#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include <util/delay.h>

class UART {
public:
    void initialisation_UART ();
    void transmit_UART(uint8_t byte);
    void transmit_UART_number(uint16_t n);
private:
};

#endif // UART_H
