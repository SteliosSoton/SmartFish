/*
 * photosynthesis.h
 *
 *  Created on: 3 Ìבס 2018
 *      Author: admin
 */

#ifndef PHOTOSYNTHESIS_H_
#define PHOTOSYNTHESIS_H_

void initPhotosynthesisAssist(void);
void togglePhotosynthesisAssist(void);

void initPhotosynthesisAssist(void){
	MCUCR |= _BV(JTD);
	MCUCR |= _BV(JTD);
	DDRC |= _BV(4);
	PORTC &= ~_BV(4);
}

void togglePhotosynthesisAssist(void){
	if(PINC & _BV(4)){ printf("\n\nset low");}
	else { printf("\n\nset high"); }
	PINC |= _BV(4);


}




#endif /* PHOTOSYNTHESIS_H_ */
