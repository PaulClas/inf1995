#ifndef MINUTERIE_H
#define MINUTERIE_H

#include <avr/io.h>
#include <util/delay.h>
class Minuterie{

	public:
	
		Minuterie();
		void partirMinuterie ( uint16_t duree );
		void resetMinuterie ( uint16_t duree );
		uint8_t getMinuterieExpiree();
		uint8_t getDixiemesSecondes();
		
		
	private:
		
	uint8_t	minuterieExpiree_;
	uint8_t	dixiemesSecondes_;

};
#endif 

