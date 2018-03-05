/*
 * photosynthesis.h
 *
 *  Created on: 3 Ìבס 2018
 *      Author: admin
 */

#ifndef PHOTOSYNTHESIS_H_
#define PHOTOSYNTHESIS_H_

#include <avr/io.h>

void initPhotosynthesisAssist(void);
void togglePhotosynthesisAssist(void);

void initPhotosynthesisAssist(void){
	MCUCR |= _BV(JTD);
	MCUCR |= _BV(JTD);
	DDRC |= _BV(4);
	PORTC &= ~_BV(4);
}

void togglePhotosynthesisAssist(void){
	PINC |= _BV(4);
}




#endif /* PHOTOSYNTHESIS_H_ */
