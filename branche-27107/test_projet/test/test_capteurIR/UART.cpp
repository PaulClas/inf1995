#include "UART.h"
#include <stdio.h>
UART::UART(){
    initialisation_UART();
}
void UART::initialisation_UART ()
{
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART::transmit_UART(uint16_t byte)
{
    while( !(UCSR0A &(1<<UDRE0))){}
    
    UDR0=byte;
}
uint8_t UART:: USART_Receive(void){
		while (!(UCSR0A & (1 << RXC0)));
		return UDR0;
}
/*void transmit_UART_str(uint16_t str)
{
    // transmettre str[i]; jusqua \0
    uint8_t c;
    while( (c = str++) != 0){
        transmit_UART(c);
	}
}*/
void UART::transmit_UART_number(uint16_t n)
{
    char buff[100];
    sprintf(buff, "number is %u\n", n);
    for(int i =0; i<20; i++){
        transmit_UART(buff[i]);
    }
}


