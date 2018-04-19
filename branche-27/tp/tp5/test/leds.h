#define leds_H_

uint8_t	red = 0x55;
uint8_t	green = 0xAA;

enum State {RED = 0, AMBER = 1, GREEN = 2, OFF = 3};
volatile State currentState = RED;

volatile bool currentButtonState  = false;


void lightLed(State curState);
