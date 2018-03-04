/*
 * test.c
 *
 *  Created on: 3 Ìבס 2018
 *      Author: admin
 */


#include <avr/io.h>
#include "debug.h"
#include <util/delay.h>
#include "photosynthesis.h"
int main(){
	init_debug_uart0();
	initPhotosynthesisAssist();

	while(1){
		_delay_ms(5000);
		togglePhotosynthesisAssist();
		if(PINC & _BV(1)){ printf("\n\nset low");}
		else { printf("\n\nset high"); }

	}

}
