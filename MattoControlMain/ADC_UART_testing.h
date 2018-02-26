/*
 * ADC_UART_testing.h
 *
 *  Created on: Feb 26, 2018
 *      Author: NRS1G15
 */

#ifndef ADC_UART_TESTING_H_
#define ADC_UART_TESTING_H_

#include "debug.h"
#include "avr/interrupt.h"
#include <avr/io.h>
#include "debug.h"
#include "power_saving.h"
#include "ADC.h"

#define SENSOR_COUNT 2

ISR(USART0_RX_vect) {
	printf("\nReceived: %c", UDR0);

	ADCResults[0] = 0; //Reset ADCResalt counter bit
	ADMUX = 0xc0; //Reset ADC channel back to 0
	ADCSRA |= _BV(ADEN); //Enable ADC for conversion
	while(ADCResults[0] < SENSOR_COUNT) { //Repeat loop to keep IC in IDLE while conversion is done
		enterSleepMode(IDLE);
	}
	ADCSRA &= ~_BV(ADEN); //Disable ADC as no longer needed

	displayResults();
	_delay_ms(2); //Device enters sleep too fast for UART to send data
}


#endif /* ADC_UART_TESTING_H_ */
