#include "UART.h"
#include <stdio.h>

void UART::initialisation_UART ()
{
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART::transmit_UART(uint8_t byte)
{
    while( !(UCSR0A &(1<<UDRE0))){}
    
    UDR0=byte;
}

void UART::transmit_UART_number(uint16_t n)
{
    char buff[100];
    sprintf(buff, "number is %u\n", n);
    for(int i =0; i<20; i++){
        transmit_UART(buff[i]);
    }
}


