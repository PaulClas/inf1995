/*
 * Nom: pb1 tp7
*/
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t	rouge = 1;
uint8_t	vert = 2;
uint8_t eteint = 0;
volatile uint8_t dixieme_sec;
volatile uint8_t dureeState; // duree de l'etat quand il clignote vert
enum State {INITIAL = 0, INCR_COMPTEUR = 1, CLIGN_VERT = 2, ETEINT = 3, CLING_ROUGE = 4, VERT = 5 };
volatile State currentState;

volatile bool currentButtonState  = false;
void lightLed(State curState);
/******************************************************************************
******************************************************************************/
void initialisation ( void ) {
cli ();

DDRA = 0xFF; // PORT A est en mode sortie
DDRD = 0x00; // PORT D est en mode entree
dixieme_sec = 0;
dureeState = 0;
currentState = INITIAL;
lightLed(currentState);
EIMSK |= (1 << INT0) ;

EICRA |= (1 <<ISC01); // interruption de bouton se fait quand le bouton et apppuye et relache
// valeur de compare match pour chaque 10eme de second
sei ();
}
/******************************************************************************
* fonction partirTimer
******************************************************************************/
void partirTimer(uint16_t dure_interval){
  TCCR1B |=  _BV(WGM12) | _BV(CS12)| _BV(CS10); // mode compare match CTC et prescaler 1024
  OCR1A = dure_interval;
  TCNT1 = 0;
  TIMSK1 |= _BV(OCIE1A);
}
/******************************************************************************
* fonction arreterTimer
******************************************************************************/
void arreterTimer(){
  TCNT1 = 0;
  TCCR1B = 0;
  OCR1A = 0;
  TIMSK1 = 0;
}
/******************************************************************************
* fonction lightLed
******************************************************************************/
void lightLed(State curState){
  switch (curState) {
    case INITIAL:
      PORTA = eteint;
      break;
    case INCR_COMPTEUR:
      PORTA = eteint;
      break;
    case CLIGN_VERT:
      if (PORTA == vert)
        PORTA = eteint;
      else
        PORTA = vert;
      break;
    case ETEINT :
      PORTA = eteint;
      break;
    case CLING_ROUGE:
      if (PORTA == rouge)
        PORTA = eteint;
      else
        PORTA = rouge;
      break;
    case VERT:
      PORTA = vert;
      break;
  }
}

/******************************************************************************
******************************************************************************/
ISR (INT0_vect){
  _delay_ms(30);
  currentButtonState = ((PIND & 0x04)== 0);
  if (currentButtonState){
    currentState = INCR_COMPTEUR;
    partirTimer(781); // interruption a chaque 100ms
  }
}
/******************************************************************************
******************************************************************************/
ISR(TIMER1_COMPA_vect){
  currentButtonState = ((PIND & 0x04)== 0);
  switch (currentState) {
    case INCR_COMPTEUR :
      if (++dixieme_sec == 120 || !currentButtonState){
        currentState = CLIGN_VERT;
        partirTimer(391); // interruption a chaque 50ms
      }
      break;
    case CLIGN_VERT:
      if (++dureeState==10){ // 10 interruptions de 50ms chacun, 500ms au total
        currentState = ETEINT;
        lightLed(currentState);
        partirTimer(15625); //interruption a chaque 2s
        dureeState =0;
      }
      else
        lightLed(currentState);
      break;
    case ETEINT:
      currentState = CLING_ROUGE;
      partirTimer(1953); // interruption a chaque 250ms
      break;
    case CLING_ROUGE:
      if (--dixieme_sec == 0){
        currentState = VERT;
        lightLed(currentState);
        partirTimer(7812); // interruption a chaque 1s
      }
      else
        lightLed(currentState);
      break;
    case VERT:
      arreterTimer();
      initialisation();
      break;
  }
}


/******************************************************************************
******************************************************************************/
int main(){
  initialisation();
  for(;;){
  }
	return 0;
}
