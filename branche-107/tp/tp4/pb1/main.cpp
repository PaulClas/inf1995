/*
 */

#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define DEL_RED PORTB = 0x02 //À la place d'écrire la valeur du PORTB à chaque fois que nous voulons
#define DEL_OFF PORTB = 0x00 //qu'elle prenne une certaine couleur, nous les avons define ici.
#define DEL_GREEN PORTB = 0x01




bool touchbutton();
void DEL_AMBRE();


enum State {
    INITIAL, RELEASE, TRANSITION_RED, TRANSITION_GREEN
};


int main()
{
    DDRB = 0xff;
    DDRD = 0x00;


	int b = 1000;

	int a = 1000; //Au début a vaut 1000, car le signal est toujours à 1 (DEL ON)
	

	//1kHz ---> 1 miliseconde (0.001 s)
      
    State currentState = INITIAL;
    for(;;){
        switch(currentState){
            case INITIAL:
                DEL_OFF;
				if (touchbutton()) {
					currentState = RELEASE;
				}
                break;
                
            case RELEASE:
                if (!touchbutton()){
                   currentState = TRANSITION_RED;
                }
                break;


            case TRANSITION_RED:

				for (int i = 0; i < 1000; i++) {
					for (int j = 0; j < 3; j++) {
                        DEL_RED;
                        for (int x = 0; x < a; x++){
                            _delay_us(0.001);
                        }
                        
						DEL_OFF;
                        for (int x = 0; x < (b-a); x++){
                            _delay_us(0.001);
                        }
					}
					a--;
				}
                
                a=1000;
                
                currentState = TRANSITION_GREEN;
                break;    
                
            case TRANSITION_GREEN:
                
                for (int i = 0; i < 1000; i++) {
                    for (int j = 0; j < 3; j++) {
                        DEL_GREEN;
                        for (int x = 0; x < a; x++){
                            _delay_us(0.001);
                        }
                        
                        DEL_OFF;
                        for (int x = 0; x < (b-a); x++){
                            _delay_us(0.001);
                        }
                    }
                    a--;
                }
                
                a=1000;
                currentState = INITIAL;
                break;
        }
    }
    
    return 0;
}


bool touchbutton()
{
    bool boutonpresser = false;
    if(PIND & 0x04){
        _delay_ms(10);
        if(PIND & 0x04)
            boutonpresser = true;
    }
    return boutonpresser;
}

void  DEL_AMBRE()
{
    while(touchbutton()){
        DEL_RED;
        _delay_ms(3);
        DEL_GREEN;
        _delay_ms(7);
    }
}
