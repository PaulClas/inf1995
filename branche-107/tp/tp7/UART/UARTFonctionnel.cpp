#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <avr/io.h>

/***********************************************************************
 * 
 **********************************************************************/
#if 0
void initialisation_UART ()
{
	UBRR0H = 0;
	UBRR0L = 0xCF;
	UCSR0A = 0;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
#endif
/***********************************************************************
 * 
 **********************************************************************/
#if 0
void transmit_UART(uint8_t byte)
{
	while( !(UCSR0A &(1<<UDRE0))){}
	
	UDR0=byte;
}
#endif
/***********************************************************************
 * 
 **********************************************************************/
#if 0
void transmit_UART_str(uint8_t * str)
{
    // transmettre str[i]; jusqua \0
    uint8_t c;
    while( (c = *str++) != 0)
        transmit_UART(c);
}
#endif 
/***********************************************************************
 * 
 **********************************************************************/
#if 0
void transmit_UART_number(uint16_t n)
{
    char buff[100];
    sprintf(buff, "number is %u\n", n);
    for(int i =0; i<20; i++){
 	transmit_UART(buff[i]);
	}
}
#endif
