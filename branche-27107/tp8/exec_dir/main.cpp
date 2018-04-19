#include <avr/io.h>
#include "DEL.h"
#include "buttonTouch.h"


int main(){
  DDRA = 0xff; // PORT A est en mode sortie
  DDRD = 0x00; // Entree
  DEL del(A);
  del.DEL_OFF();
  for(;;){
    if(touchbutton())
      del.DEL_RED();
  }
  return 0;
}
