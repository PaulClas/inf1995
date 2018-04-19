valeurAnalogiqueGauche = convertisseurAnalogique.lecture(0x02);
        valeurAnalogiqueDroite = convertisseurAnalogique.lecture(0x00);
        /************Case_longer*********************
         * Ce test copmmence par longer un mur a gauche du robot.
         * Le robot va determiner si il y a un obstacle a sa droite.
         * Ensuite si cette obstacle est un poteau ou pas.
         * Si l obstacle n est pas un poteau alors le robot
         * va suivre le mur droit pendant 10 seconde.
         * Fini avec jeu de DEL
        ************************************************/
        
       /* Capteur gauche est entre 13 et 15 cm
        robot decide suivre gauche
        robot avance
        robot detecte obtsalkce entre 13 et 15 cm a droite
        robot decide suivre droit
        robot avance 20 seconde.*/
        if(coterASuivre == 'g' && valeurAnalogiqueDroite < distance_au_mur_de_15cm_ ){
			if(valeurAnalogiqueGauche <= distance_au_mur_de_15cm_){
				moteur.slightTurnLeft();
				del.DEL_RED();}
			if(valeurAnalogiqueGauche >= distance_au_mur_de_10cm_){
				moteur.slightTurnRight();}
			else{
				del.DEL_GREEN();
				moteur.avancer(150);
			}
		}
		if(coterASuivre == 'g' && valeurAnalogiqueDroite >= distance_au_mur_de_15cm_){
			coterASuivre ='d';
		}
		
		if(coterASuivre == 'd' && valeurAnalogiqueGauche < distance_au_mur_de_15cm_){  
			if(valeurAnalogiqueDroite <= distance_au_mur_de_15cm_){
				moteur.slightTurnRight();
				del.DEL_RED();}
			if(valeurAnalogiqueDroite >= distance_au_mur_de_10cm_){
				moteur.slightTurnLeft();}
			else{
				del.DEL_GREEN();
				moteur.avancer(150);
			}
		}
		if(coterASuivre == 'd' && valeurAnalogiqueGauche >= distance_au_mur_de_15cm_){
			coterASuivre ='g';
		}

  valeurAnalogiqueGauche = convertisseurAnalogique.lecture(0x02);
        valeurAnalogiqueDroite = convertisseurAnalogique.lecture(0x00);
        /************Case_longer*********************
         * Ce test copmmence par longer un mur a gauche du robot.
         * Le robot va determiner si il y a un obstacle a sa droite.
         * Ensuite si cette obstacle est un poteau ou pas.
         * Si l obstacle n est pas un poteau alors le robot
         * va suivre le mur droit pendant 10 seconde.
         * Fini avec jeu de DEL
        ************************************************/
        
       /* Capteur gauche est entre 13 et 15 cm
        robot decide suivre gauche
        robot avance
        robot detecte obtsalkce entre 13 et 15 cm a droite
        robot decide suivre droit
        robot avance 20 seconde.*/
        if(coterASuivre == 'g' && compteur <10){
			if(valeurAnalogiqueGauche <= distance_au_mur_de_15cm_){
				moteur.slightTurnLeft();
				del.DEL_RED();}
			if(valeurAnalogiqueGauche >= distance_au_mur_de_10cm_){
				moteur.slightTurnRight();}
			else{
				del.DEL_GREEN();
				moteur.avancer(150);
				
			}
			compteur++;
		}
		if(coterASuivre == 'g' && compteur == 10){
			coterASuivre ='d';
			compteur =0;
			del.DEL_RED();
			_delay_ms(50);
			del.DEL_GREEN();
			_delay_ms(50);
			del.DEL_RED();
			_delay_ms(50);
			del.DEL_GREEN();
			_delay_ms(50);
			
		}
		
		if(coterASuivre == 'd' && compteur <10){  
			if(valeurAnalogiqueDroite <= distance_au_mur_de_15cm_){
				moteur.slightTurnRight();
				del.DEL_RED();}
			if(valeurAnalogiqueDroite >= distance_au_mur_de_10cm_){
				moteur.slightTurnLeft();}
			else{
				del.DEL_GREEN();
				moteur.avancer(150);
			}
			compteur++;
		}
		if(coterASuivre == 'd' && compteur == 10){
			coterASuivre ='g';
			compteur =0;
			del.DEL_RED();
			_delay_ms(50);
			del.DEL_GREEN();
			_delay_ms(50);
			del.DEL_RED();
			_delay_ms(50);
			del.DEL_GREEN();
			_delay_ms(50);
		}
