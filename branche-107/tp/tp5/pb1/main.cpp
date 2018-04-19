#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

enum State {
    INITIAL, RED, GREEN, AMBRE, OFF, GREEN_2
};

volatile State currentState = INITIAL; // selon le nom de votre variable

bool touchbutton();
void DEL_AMBRE();
void DEL_RED();
void DEL_GREEN();
void DEL_OFF();


// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR (INT0_vect) {
    // laisser un delai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms( 30 );
    // se souvenir ici si le bouton est pressé ou relâché
    if(1) {
        switch(currentState){
            case INITIAL:
                currentState = AMBRE;
                break;
            case AMBRE:
                currentState = GREEN;
                break;
            case GREEN:
                currentState = RED;
                break;
            case RED:
                currentState = OFF;
                break;
            case OFF:
                currentState = GREEN_2;
                break;
            case GREEN_2:
                currentState = INITIAL;
                break;
    
        }
        EIFR |= (1 << INTF0) ;
    }
}


void initialisation (void) {
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli ();
    
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRB = 0xff;
    DDRD = 0x00;
    
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);
    
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC00);
    
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}



int main()
{
    initialisation();
    for(;;){
        switch(currentState){
            case INITIAL:
                DEL_RED();
                break;
                
            case AMBRE:
                DEL_AMBRE();
                break;
                
            case GREEN:
                DEL_GREEN();
                break;
                
            case RED:
                DEL_RED();
                break;
                
            case OFF:
                DEL_OFF();
                break;
                
            case GREEN_2:
                DEL_GREEN();
                break;
                
        }
    }
    
    return 0;
}

/*********************************************************************************
 * Fonction: touchbutton()
 * Description: Permet d'indiquer à notre main() si le bouton a été appuyé ou pas
 * Dernière Modification: 29 janvier 2018, 14h13
 *
 *********************************************************************************/
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
/*********************************************************************************
 * Fonction: DEL_AMBRE()
 * Description: Permet d'afficher la couleur ambré (alternance de rouge et de vert).
 * Dernière Modification: 29 janvier 2018, 14h15
 *
 *********************************************************************************/
void  DEL_AMBRE()
{
  // while(touchbutton())
    {
        DEL_RED();
        _delay_ms(3);
        DEL_GREEN();
        _delay_ms(7);
    }
}

void DEL_RED()
{
    PORTB = 0x02;
}

void DEL_GREEN()
{
    PORTB = 0x01;
}

void DEL_OFF()
{
    PORTB = 0x00;
}


