/*
 * RGB_control.h
 *
 *  Created on: Mar 2, 2018
 *      Author: NRS1G15
 */

#ifndef RGB_CONTROL_H_
#define RGB_CONTROL_H_

#include <avr/io.h>

#define REDLED PC1 		//Port c pin 1 is red leds
#define GREENLED PC2	//Port c pin 1 is green leds
#define BLUELED PC3		//Port c pin 1 is blue leds

void init_RGB_LEDs(void) {
	DDRC |= _BV(REDLED); 	//Sets port c pin 1 as output
	DDRC |= _BV(GREENLED);	//Sets port c pin 2 as output
	DDRC |= _BV(BLUELED);	//Sets port c pin 3 as output

	PORTC |= _BV(REDLED);	//Sets red led low (low turns off LEDs)
	PORTC |= _BV(GREENLED); //Sets green led low
	PORTC |= _BV(BLUELED);  //Sets blue led low
}

void toggleLED(char led, uint8_t status) {
	if(status)
		PORTC &= ~_BV(led);
	else
		PORTC |= _BV(led);
}
void setRGBColour(uint8_t red, uint8_t green, uint8_t blue) {
	printf("\nsetRGBcolour() in RGB_control.h\n");
	printf("R: %d\nG: %d\nB: %d\n", red, green, blue);
	toggleLED(REDLED, red);
	toggleLED(BLUELED, blue);
	toggleLED(GREENLED, green);
}

#endif /* RGB_CONTROL_H_ */
