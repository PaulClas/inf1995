//
//  moves.h
//  
//
//  Created by Karima Salem on 18-04-04.
//
//
//

#ifndef moves_h
#define moves_h

#include <stdio.h>
#include "Moteur.h"
#include "Son.h"
class moves{
public:
	moves();
    void turnAroundWall(bool aDroite);
    void turnOnSelf(bool aDroite);
    void longerMur(uint16_t moyenne, bool aDroite);
    void switchMur(uint16_t moyenne, bool aDroite);
    void routinePoteau();
    
private:
    Moteur moteur_;
    Son son_;
    
};
#endif /* moves_h */
