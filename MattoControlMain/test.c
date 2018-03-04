/*
 * test.c
 *
 *  Created on: 3 Ìבס 2018
 *      Author: admin
 */


#include <avr/io.h>
#include "debug.h"
#include <util/delay.h>
//#include "photosynthesis.h"
int main(){
	init_debug_uart0();
	//initPhotosynthesisAssist();
	DDRC &= ~_BV(1);
	PORTC &= ~_BV(1);

	while(1){
		_delay_ms(1000);
		//togglePhotosynthesisAssist();
		if(PINC & _BV(1)){ printf("\n\n high");}
		else { printf("\n\n low"); }

	}

}
