#/**
 * Nom: Probleme1
 * Autheur(e)s: Thomas McAdams (1904141), Paul Clas (1846912) & Emmanuelle Roberge (1849263)
 * Date: 1 février 2017
 * Description: Ce programme permet de contrôler la DEL libre sur notre robot. Une fois la
 *              carte mère activée, la DEL n'émettera pas de lumière. Lorsque l'usager pèse
 *              et relâche le bouton-poussoir 5 fois, la DEL s'allumera en rouge pour une
 *              seconde et le programme sera réinitialisé à nouveau permettant d'effectuer
 *              cette action autant de fois désirées.
 */

#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define DEL_RED PORTB = 0x02 //À la place d'écrire la valeur du PORTB à chaque fois que nous
#define DEL_OFF PORTB = 0x00 //voulons qu'elle fasse quelque chose nous les avons define ici.

/**
 * Fils: Le fils violet et gris, qui est de type femelle-femelle, est braché d'un côté sur
 *       le cavalier de l'interrupteur et sur l'autre côté il est braché dans le pin 0 et 1 du
 *       PORTB.
 * States:
 *      INITIAL: L'interrupteur n'a pas encore été pesé et la DEL est éteinte.
 *      RELEASE: L'état est atteinte lorsque le bouton-poussoir a été pesé. La DEL est éteinte.
 *      TOUCH: L'état est atteinte lorsque le bouton-poussoir a été relaché. La DEL est éteinte.
 *      ON: Le bouton-poussoir a été pesé et relaché cinq fois donc la DEL s'allume en rouge pour
 *          une seconde et par la suite le programme retourne a son état initial.
 *
 *
 *
 * Table des états:
 *
 *  --------------------------------------------------------------
 *  | ÉTAT PRÉSENT | BOUTON | Compteur | ÉTAT SUIVANT | SORTIE Z |
 *  --------------------------------------------------------------
 *  | INITIAL      |    0   |    0     | INITIAL      |     0    |
 *  | INITIAL      |    1   |    0     | RELEASE      |     0    |
 *  | RELEASE      |    0   |    0     | RELEASE      |     0    |
 *  | RELEASE      |    1   |    1     | TOUCH        |     0    |
 *  | TOUCH        |    0   |    1     | TOUCH        |     0    |
 *  | TOUCH        |    1   |    1     | RELEASE      |     0    |
 *  | RELEASE      |    0   |    1     | RELEASE      |     0    |
 *  | RELEASE      |    1   |    2     | TOUCH        |     0    |
 *  | TOUCH        |    0   |    2     | TOUCH        |     0    |
 *  | TOUCH        |    1   |    2     | RELEASE      |     0    |
 *  | RELEASE      |    0   |    2     | RELEASE      |     0    |
 *  | RELEASE      |    1   |    3     | TOUCH        |     0    |
 *  | TOUCH        |    0   |    3     | TOUCH        |     0    |
 *  | TOUCH        |    1   |    3     | RELEASE      |     0    |
 *  | RELEASE      |    0   |    3     | RELEASE      |     0    |
 *  | RELEASE      |    1   |    4     | TOUCH        |     0    |
 *  | TOUCH        |    0   |    4     | TOUCH        |     0    |
 *  | TOUCH        |    1   |    4     | RELEASE      |     0    |
 *  | RELEASE      |    0   |    4     | RELEASE      |     0    |
 *  | RELEASE      |    1   |    5     | ON           |     1    |
 *  | ON           |    X   |    5     | INITIAL      |     0    |
 *  --------------------------------------------------------------
 *
 */
 
 bool touchbutton();



enum State {
    INITIAL, TOUCH, RELEASE, ON
};


int main()
{
    DDRB = 0xff;
    DDRD = 0x00;
    
    int compteur = 0;
    
    State currentState = INITIAL;
    
    for(;;){
        
        switch(currentState){
                
            case INITIAL:
                compteur = 0;
                DEL_OFF;
                if (touchbutton())
					currentState = RELEASE;
                break;
                
            case RELEASE:
                if (!touchbutton()){
					currentState = TOUCH;
					compteur++;
					if (compteur == 5)
						currentState = ON;
				}
                break;
                
            case TOUCH:
                if (touchbutton())
                    currentState = RELEASE;
                break;
                
            case ON:
				DEL_RED;
                _delay_ms(1000);
                DEL_OFF;
                currentState = INITIAL;
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


