/*
 * pump_control.h
 *
 *  Created on: Feb 26, 2018
 *      Author: Sil
 */

#ifndef PUMP_CONTROL_H_
#define PUMP_CONTROL_H_

#include <avr/io.h>
#include <util/delay.h>

void togglePump(uint8_t duration) {
	PORTC |= _BV(PB6);
	_delay_ms(duration*10);
	PORTC &= ~_BV(PB6);
}

#endif /* PUMP_CONTROL_H_ */
