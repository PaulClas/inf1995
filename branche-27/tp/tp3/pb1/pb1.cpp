/* States   Push (A)*   Next_State      Sortie(Couleur_LED)
 *   Init     false           Init             0  (Eteinte) 
 *   Init      true           Init             0  
 *   Init     false         Appui1             0   
 * Appui1      true         Appui1             0    
 * Appui1     false         Appui2             0    
 * Appui2      true         Appui2             0    
 * Appui2     false         Appui3             0 
 * Appui3      true         Appui3             0
 * Appui3     false         Appui4             0
 * Appui4      true         Appui4             0 
 * Appui4     false         Appui5             0
 * Appui5     false           Init             1    (Rouge)
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

  enum States{Init, Appui1, Appui2, Appui3, Appui4, Appui5};
  States states = Init;
  bool push = false; // Boolean Push pour le bouton release

  for(;;)  // boucle sans fin
  {
    switch(states)
    {
        case Init:
            PORTA = delEteinte;
            if(PIND & 0x04){
              _delay_ms(10);
              push = true;  // True car bouton push
            }
            if(!(PIND & 0x04) && push == true){ // Bouton release et verification de l'appui precedent
              _delay_ms(10);
              push = false;  // False car bouton release
              states = Appui1;  
            }
            break;
        case Appui1:
            if(PIND & 0x04){
              _delay_ms(10);  
              push = true;  
            }
            if(!(PIND & 0x04) && push == true){
              _delay_ms(10);  
              push = false;  
              states = Appui2;  
            }
            break;
        case Appui2:
            if(PIND & 0x04){
              _delay_ms(10);  
              push = true;  
            }
            if(!(PIND & 0x04) && push == true){
              _delay_ms(10);  
              push = false;  
              states = Appui3;  
            }
            break;
        case Appui3:
            if(PIND & 0x04){
              _delay_ms(10);  
              push = true;  
            }
            if(!(PIND & 0x04) && push == true){
              _delay_ms(10);  
              push = false;  
              states = Appui4;  
            }
            break;
        case Appui4:
            if(PIND & 0x04){
              _delay_ms(10);  
              push = true;  
            }
            if(!(PIND & 0x04) && push == true){
              _delay_ms(10);  
              push = false;  
              states = Appui5; 
            }
            break;
        case Appui5:
            PORTA = delRouge; // Allumage de la LED apres 5 appuis
            _delay_ms(1000); // 1 seconde de delay pour la LED
            states = Init; // retour au state Initial
            _delay_ms(10);
            break;
    }    
  }
  return 0; 
}
