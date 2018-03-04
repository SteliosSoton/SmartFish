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
	DDRC |= _BV(1);
	PORTC &= ~_BV(1);
}

void togglePhotosynthesisAssist(void){
	if(PINC & _BV(1)){ printf("\n\nset low");}
	else { printf("\n\nset high"); }
	PINC |= _BV(1);


}




#endif /* PHOTOSYNTHESIS_H_ */
