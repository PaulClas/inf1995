  /************TEST_CAPTEUR_DROIT**********************
      * Ce test sert a voir si le robot suit un mur sur
      * son coter droit
      * Modification derniere: 4 avril 2018
      * ************************************************
        
        if(valeurAnalogiqueDroite <= distance_max_au_mur){
			moteur.slightTurnRight();
			del.DEL_RED();}
		if(valeurAnalogiqueDroite >= distance_minimal_au_mur){
			moteur.slightTurnLeft();}
		else{
			del.DEL_GREEN();
			moteur.avancer(150);
			}
		**************************************************/
