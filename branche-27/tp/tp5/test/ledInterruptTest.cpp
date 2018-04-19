  /*
   * Nom: ledInterruptTest
  */
  #define F_CPU 8000000UL
  #include <avr/io.h>
  #include <util/delay.h>
  #include <leds.h>
  #include <avr/interrupt.h>

  void initialisation ( void ) {
  cli ();

  DDRA = 0xff; // PORT A est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  PORTA = red;

  EIMSK |= (1 << INT0) ;

  EICRA |= (1 <<ISC00);

  sei ();
  }

  ISR (INT0_vect){
    _delay_ms(10); // delai d'anti-rebond
      currentButtonState = ((PIND & 0x04)!= 0);
      switch (currentState) {
        case RED:
            if (currentButtonState)
              currentState = AMBER;
            else
              currentState = OFF;
            break;

        case AMBER:
          if (!currentButtonState)
            currentState = GREEN;
          break;

        case GREEN:
            currentState = RED;
          break;

        case OFF:
          if (currentButtonState)
            currentState = GREEN;
          break;
        }
        lightLed(currentState);
        EIFR |= (1 << INTF0) ;
  }
  int main(){
    initialisation();
    for(;;){ // boucle sans fin
      if (currentState == AMBER)
        lightLed(currentState);
  	}
  	return 0;
  }

  /******************************************************************************
  * fonction lightLed
  ******************************************************************************/
  void lightLed(State curState){
    switch (curState) {
      case RED:
        PORTA = red;
        break;
      case GREEN:
        PORTA = green;
        break;
      case OFF:
        PORTA = OFF;
        break;
      case AMBER:
        PORTA = green;
        _delay_ms(7);
        PORTA = red;
        _delay_ms(3);
        break;
    }
  }
