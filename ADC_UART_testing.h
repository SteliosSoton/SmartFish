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



ISR(USART0_RX_vect) {
	printf("\nReceived: %c", UDR0);

	uint16_t *sensorData = getSensorData(); //Gets a pointer that points to the memory where the sensor data array is stored
	for(uint8_t i = 0; i < sizeof(sensorData)/sizeof(sensorData[0]); i++) //Gets size of array by taking size of the overall array divided by size of the type of data enclosed.
		printf("\nSensorData %d: %d", i, sensorData[i]);
	_delay_ms(2); //Device enters sleep too fast for UART to send data
}


#endif /* ADC_UART_TESTING_H_ */
