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
	DDRB |= _BV(3);
	PORTB &= ~_BV(3);
}

void togglePhotosynthesisAssist(void){
	PINC ^= _BV(3);
}




#endif /* PHOTOSYNTHESIS_H_ */
