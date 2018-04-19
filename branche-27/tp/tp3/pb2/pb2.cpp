/* States   Push (A)*   Next_State      Sortie(Couleur_LED)
 *   Init     false           Init             1    (Rouge)
 *   Init      true           Init             1.2  (Ambre)  
 *   Init     false             S1             2    (Verte)
 *     S1      true             S1             1    (Rouge)
 *     S1     false             S2             0    (Eteinte)
 *     S2      true             S2             2    (Verte)
 *     S2     false           Init             1    (Rouge)
 * 
 * *(Le push false signifie bouton release)
 */
#include <avr/io.h> 
#include <util/delay.h>
#define delRouge 0x01
#define delVerte 0x02
#define delEteinte 0x00


int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRD = 0x00; // Entree

  enum States{Init, S1, S2};
  States states = Init;
  bool push = false; // Boolean Push utilise pour le release

  for(;;)  // boucle sans fin
  {
    switch(states)
    {
        case Init:
            PORTA = delRouge; 
            if(PIND & 0x04){ 
              _delay_ms(10);
              while (PIND & 0x04) // Boucle pour la couleur Ambre
              {
                PORTA = delRouge;          
                _delay_us(25);  // Delay court pour obtenir la couleur Ambre
                PORTA = delVerte;      
                _delay_us(20);
              }
              push = true; //Bouton Appuye 
            }
            if(!(PIND & 0x04) && push == true){ // Bouton release et verification de l'appui precedent
              _delay_ms(10);
              PORTA = delVerte;
              push = false;  // False car bouton release
              states = S1;  
            }
            break;
        case S1:
            if(PIND & 0x04){
              _delay_ms(10); 
              PORTA = delRouge;
              push = true;  
            }
            if(!(PIND & 0x04) && push == true){
              _delay_ms(10);
              PORTA = delEteinte;
              push = false;  
              states = S2;  
            }
            break;
        case S2:
            if(PIND & 0x04){
              _delay_ms(10);
              PORTA = delVerte;
              push = true;  
            }
            if(!(PIND & 0x04) && push == true){
              _delay_ms(10);
              push = false;  
              states = Init;  
            }
            break;
    }    
  }
  return 0; 
}

