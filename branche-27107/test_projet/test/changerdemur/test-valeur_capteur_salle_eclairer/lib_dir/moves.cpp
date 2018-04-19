//
//  moves.cpp
//  
//
//  Created by Karima Salem on 18-04-04.
//
//
//

#include "moves.h"
const uint16_t SEUIL_MUR_MIN = 460; // 13cm
const uint16_t SEUIL_MUR_MAX = 400; // 15cm 

moves::moves(){}

void moves::turnAroundWall(bool aDroite){
    if(aDroite)
        moteur_.turnRight(); //or slightlyTurn????????????
    else
        moteur_.turnLeft();
}
void moves::turnOnSelf(bool aDroite){
	if(aDroite)
		moteur_.turnLeft();
	else
		moteur_.turnRight();
}

void moves::longerMur(uint16_t moyenne, bool aDroite){
    if(aDroite){
        if(moyenne<= SEUIL_MUR_MIN && moyenne >=SEUIL_MUR_MAX){
            moteur_.avancer(150);}
        if(moyenne<=SEUIL_MUR_MAX){
            moteur_.slightTurnRight();}
        if(moyenne>=SEUIL_MUR_MIN){
            moteur_.slightTurnLeft();}
    }
    else{
        if(moyenne<= SEUIL_MUR_MIN && moyenne >=SEUIL_MUR_MAX){
            moteur_.avancer(150);}
        if(moyenne<=SEUIL_MUR_MAX){
            moteur_.slightTurnLeft();}
        if(moyenne>=SEUIL_MUR_MIN){
            moteur_.slightTurnRight();}
    }
}

void moves::switchMur(uint16_t moyenne, bool aDroite){
    if(aDroite){
        if(moyenne<=SEUIL_MUR_MAX)
            moteur_.slightTurnLeft();
        aDroite=false;
    }
    else{
        if(moyenne<=SEUIL_MUR_MAX)
            moteur_.slightTurnRight();
        aDroite=true;
    }
}

void moves::routinePoteau(){
    moteur_.arreter();
    son_.chansonPoteau();
    
}
