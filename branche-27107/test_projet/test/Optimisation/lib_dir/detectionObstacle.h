//
//  detectionObstacle.h
//  
//
//  Created by Karima Salem on 18-04-04.
//
//
//

#ifndef detectionObstacle_h
#define detectionObstacle_h

#include <stdio.h>
#include <util/delay.h>
class detectionObstacle{
public:
    detectionObstacle();
    bool obstacleDetecte(uint16_t valeurAnalogique);
    bool identifierObstacle(uint16_t valeurAnalogique, bool isPoteau);
};
#endif /* detectionObstacle_h */
