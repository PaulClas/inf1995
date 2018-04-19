/**
 * Nom: Probleme2
 * Autheur(e)s: Thomas McAdams (1904141), Paul Clas (1846912) & Emanuelle Roberge (1849263)
 * Date: 1 février 2017
 * Description: Ce programme permet de contrôler la DEL libre qui ce trouve sur notre robot. Une fois la
 *              carte mère activée, la DEL émettra de la lumière rouge. Lorsque l'usager pèse le bouton-
 *              poussoir pour une première fois, la DEL prend une couleur ambre. Par la suite, lorsqu'il
 *              relâchera le bouton-poussoir la DEL deviendra verte. Quand l'usager pèsera de nouveau, la
 *              DEL tournera au rouge et quand il va relâcher elle n'émettra plus de couleur.
 *              Finalement, en pesant sur le bouton-poussoir une dernière fois, la DEL émettra de la
 *              lumière verte. En relâchant, la DEL tournera au rouge et la carte mère reviendra
 *              ainsi à sa position initiale.
 */

#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define DEL_RED PORTB = 0x02 //À la place d'écrire la valeur du PORTB à chaque fois que nous voulons
#define DEL_OFF PORTB = 0x00 //qu'elle prenne une certaine couleur, nous les avons define ici.
#define DEL_GREEN PORTB = 0x01


/**
 * Fils: Le fils violet et gris, qui est de type femelle-femelle, est branché d'un côté sur
 *       le cavalier de l'interrupteur à son autre extrémité, il est braché dans le pin 0 et 1 du
 *       PORTB.
 * States:
 *      INITIAL: L'interrupteur n'a pas encore été pesé et la DEL est éteinte.
 *      RED: La DEL est rouge et l'interrupteur est pesé.
 *      GREEN: La DEL verte et l'interrupteur n'est pas pesé.
 *      AMBRE: LA DEL AMBRE et l'interrupteur est pesé.
 *      OFF: La DEL n'émet pas de lumière et l'interrupteur n'est pas pesé.
 *      GREEN_2: Ce deuxième état vert arrive lorque l'usager pèse sur l'interrupteur une fois que la
 *               carte mère est dans le state OFF.
 *
 * Table des états:
 *
 * BOUTON: -Le 1 represente l'action.
 *         -Le 0 représente l'absence d'action.
 *
 *  ---------------------------------------------------
 *  | ÉTAT PRÉSENT | BOUTON | ÉTAT SUIVANT | SORTIE Z |
 *  ---------------------------------------------------
 *  | INITIAL      |   0    | INITIAL      |   RED    |
 *  | INITIAL      |   1    | AMBRE        |  AMBRE   |
 *  | AMBRE        |   0    | AMBRE        |  AMBRE   |
 *  | AMBRE        |   1    | GREEN        |  GREEN   |
 *  | GREEN        |   0    | GREEN        |  GREEN   |
 *  | GREEN        |   1    | RED          |   RED    |
 *  | RED          |   0    | RED          |   RED    |
 *  | RED          |   1    | OFF          |   OFF    |
 *  | OFF          |   0    | OFF          |   OFF    |
 *  | OFF          |   1    | GREEN_2      |  GREEN   |
 *  | GREEN_2      |   0    | GREEN_2      |  GREEN   |
 *  | GREEN_2      |   1    | INITIAL      |   RED    |
 *  |-------------------------------------------------|
 *
 */

bool touchbutton();
void DEL_AMBRE();


enum State {
    INITIAL, RED, GREEN, AMBRE, OFF, GREEN_2
};


int main()
{
    DDRB = 0xff;
    DDRD = 0x00;
    
    
    
    State currentState = INITIAL;
    for(;;){
        switch(currentState){
            case INITIAL:
                DEL_RED;
                if (touchbutton()){
                    currentState = AMBRE;
                }
                break;
            case AMBRE:
                DEL_AMBRE();
                if (!touchbutton()){
                    currentState = GREEN;
                    }
                break;
            case GREEN:
                DEL_GREEN;
                if (touchbutton()){
                    currentState = RED;
                }
                break;
            case RED:
                DEL_RED;
                if (!touchbutton()){
                    currentState = OFF;
                }
                break;
                
            case OFF:
                DEL_OFF;
                if (touchbutton()){
                    currentState = GREEN_2;
                }
                break;
            case GREEN_2:
                DEL_GREEN;
                if (!touchbutton()){
                    currentState = INITIAL;
                }
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
    while(touchbutton()){
        DEL_RED;
        _delay_ms(3);
        DEL_GREEN;
        _delay_ms(7);
    }
}

