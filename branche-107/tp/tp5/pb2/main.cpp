#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

enum State {
    INITIAL, RED, GREEN, AMBRE, OFF, GREEN_2
};

volatile State currentState = INITIAL; // selon le nom de votre variable
volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

bool touchbutton();
void DEL_AMBRE();
void DEL_RED();
void DEL_GREEN();
void DEL_OFF();

ISR (TIMER1_COMPA_vect ) {
    minuterieExpiree = 1;
}

ISR (INT0_vect) {
    boutonPoussoir = 1;
    // anti-rebond
    _delay_ms(30);
}

void partirMinuterie ( uint16_t duree ) {
    minuterieExpiree = 0;
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0 ;
    OCR1A = duree;
    TCCR1A = (1 << COM1A0) | (1 << COM1A1); //| (1 << WGM12);
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
}

void initialisation ( void ) {
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
    EIMSK |= (1 << INT0) ;
    
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC01) ;
    
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}

int main()
{
    initialisation();
    
    
    
    _delay_ms(5000);
    DEL_RED();
    _delay_ms(100);
    DEL_OFF();
    
    
    partirMinuterie(7812); //1 seconde
        
    do {
            // attendre qu'une des deux variables soit modifiée
            // par une ou l'autre des interruptions.
    } while ( minuterieExpiree == 0 && boutonPoussoir == 0 );
        
    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli ();
    // Verifier la réponse
    if ( minuterieExpiree == 1 )
    {
        DEL_RED();
    }
    else
    {
        DEL_GREEN();
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
    DEL_RED();
    _delay_ms(3);
    DEL_GREEN();
    _delay_ms(7);
    
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


