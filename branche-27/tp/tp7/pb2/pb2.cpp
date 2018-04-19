#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <can.h>

#define ledRouge 0x01
#define ledVerte 0x02


int main() {
  DDRA = 0x00;
  DDRB = 0xFF;
  uint8_t pos =0;
  uint8_t seuilVert = 85;
  uint8_t seuilRouge = 130;
  uint8_t valeurCaptee;
  can convertisseur;
  for(;;){
    valeurCaptee = convertisseur.lecture(pos);
    if(valeurCaptee >= seuilRouge){
      PORTB = ledRouge;
    }
    else if(valeurCaptee <= seuilVert){
      PORTB = ledVerte;
    }
    else if (valeurCaptee > seuilVert && valeurCaptee < seuilRouge){
      PORTB = ledRouge;
      _delay_ms(25);
      PORTB = ledVerte;
      _delay_ms(20);
    }
  }
  return 0;
}
