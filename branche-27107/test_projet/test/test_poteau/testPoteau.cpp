/***********************************************************************
 * Auteur: Karima
 * Sert a detecter poteau
 * Modification: Fonctionne en date du 12 avril.
 * 
 * 
 * ********************************************************************/


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "can.h"
#include "DEL.h"
#include "UART.h"
#include "Moteur.h"
#include "buttonTouch.h"
#include "Minuterie.h"
#include "Son.h"

const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0x00;
const uint16_t SEUILMIN=185; // 60cm
const uint16_t SEUILMAX=545; // 10cm
const uint16_t SEUIL_MUR_MIN = 460; // 13cm
const uint16_t SEUIL_MUR_MAX = 400; // 15cm



//int PROCHE =100;
//int TRES_PROCHE =230;
/***********************************************************************
 *
 **********************************************************************/
void init(){
    DDRB = SORTIE; //out
    DDRD = SORTIE;
    DDRC = SORTIE;
    DDRA = ENTREE; // in
}

int main()
{
    init();
    can convertisseurAnalogique;
    Moteur moteur;
    UART uart;
    DEL del(C);
    Son son;
    //uint32_t somme = 0;
    //uint16_t moyenne = 0;
    int i;
    const int MAX =100;
    uint16_t valeurAnalogiqueDroite, valeurAnalogiqueGauche;
    son.arret();

    for(;;){
        
        moteur.avancer(150);
        valeurAnalogiqueDroite = convertisseurAnalogique.lecture(0x00);
        
        if(valeurAnalogiqueDroite<185){
            _delay_ms(500);
            valeurAnalogiqueDroite = convertisseurAnalogique.lecture(0x00);
            if(valeurAnalogiqueDroite>=185){
                del.DEL_RED();
                _delay_ms(1300);
                valeurAnalogiqueDroite = convertisseurAnalogique.lecture(0x00);
                if(valeurAnalogiqueDroite<185){
                    del.DEL_GREEN();
                    son.initialisation();
                    son.chansonPoteau();
                }
            }
            else
                del.DEL_OFF();
        }

      //  }
        //else{
           // del.DEL_AMBRE();
            //moteur.arreter();
      //  }
 /*           if(!(valeurAnalogiqueDroite>= SEUILMIN && valeurAnalogiqueDroite <=SEUILMAX)){
                moteur.arreter(); //si il y a un vide, arrêt du robot
                del.DEL_GREEN();
                _delay_ms(500);
                moteur.avancer(250); //avance après une pause
                if(valeurAnalogiqueDroite>= SEUILMIN && valeurAnalogiqueDroite <=SEUILMAX){ //si on détecte un obstacle
                    del.DEL_RED();
                    moteur.arreter();
                    _delay_ms(500);
                    moteur.avancer(250); //avance après une pause
                    _delay_ms(500);
                    if(valeurAnalogiqueDroite>= SEUILMIN && valeurAnalogiqueDroite <=SEUILMAX){
                        moteur.avancer(250);
                    }
                    else{
                        del.DEL_AMBRE();
                        moteur.arreter();
                        son.chansonPoteau();
                    }
                }*/
            
        }
    }


