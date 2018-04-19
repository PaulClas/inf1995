/*
 * 
 * Code pour faire bouger les roues
 */

#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define ENGIN_ON PORTB= 0x04 //À la place d'écrire la valeur du PORTB à chaque fois que nous voulons
#define ENGIN_OFF PORTB= 0x00 //qu'elle prenne une certaine couleur, nous les avons define ici.
#define ENGIN2_ON PORTB = 0x02
#define ENGIN2_OFF PORTB = 0x00






bool touchbutton();


enum State {
    INITIAL, ON ,OFF
};



int main()
{
    DDRB = 0x04;
    DDRD = 0x00;


	
	
	ENGIN_ON;
	_delay_ms(6000);
	

	//1kHz ---> 1 miliseconde (0.001 s)
	
	
     /*
      * int b = 600;
      * int a = 600; 
      * State currentState = INITIAL;
    for(;;){
        switch(currentState){
            case INITIAL:
                ENGIN_OFF;
				if (touchbutton()) {
					currentState = ON;
				}
                break;
                
            case OFF:
                if (!touchbutton()){
                   currentState = INITIAL;
                }
                break;


            case ON:

				for (int i = 0; i < 1000; i++) {
					
					for (int j = 0; j < 10; j++) {
                        ENGIN_ON, ENGIN2_ON;
                        for (int x = 0; x < 1000; x++){
                            _delay_us(0.001);
                        }
                        
						ENGIN_OFF, ENGIN2_OFF;
                        for (int x = 0; x < 0; x++){
                            _delay_us(0.001);
                        }
					}
					a--;
				}
                
                a=600;
                currentState = OFF;
                break;    
                
        }
    }
    
            */ 
    
    
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


