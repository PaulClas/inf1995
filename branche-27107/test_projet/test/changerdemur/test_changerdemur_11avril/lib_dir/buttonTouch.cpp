/*********************************************************************************
 * Fonction: touchbutton()
 * Description: Permet d'indiquer si le bouton a été appuyé ou pas
 *
 *********************************************************************************/
#include "buttonTouch.h"

bool touchbutton()
{
    bool boutonpresser = false;
    _delay_ms(10);
    boutonpresser = ((PIND & 0x04)!=0);
    return boutonpresser;
}
