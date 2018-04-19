//
//  detectionObstacle.cpp
//  
//
//  Created by Karima Salem on 18-04-04.
//
//
//
#include "detectionObstacle.h"
const uint16_t SEUILMAX=185; // 60cm 
const uint16_t SEUILMIN=545; // 10cm

detectionObstacle::detectionObstacle(){}

bool detectionObstacle :: obstacleDetecte(uint16_t valeurAnalogique){
    if (valeurAnalogique<SEUILMAX && valeurAnalogique>SEUILMIN)
        return true;
    else
        return false;
}

bool detectionObstacle :: identifierObstacle(uint16_t valeurAnalogique, bool isPoteau){
    _delay_ms(50);
    if(obstacleDetecte(valeurAnalogique))
        return (!isPoteau);
    else
        return isPoteau;
}
    
