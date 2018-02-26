/*
 * ADC.h
 *
 *  Created on: Feb 25, 2018
 *      Author: NRS1G15
 */

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"
#include <util/delay.h>
#include "power_saving.h"
#include "battery_level_indicator.h"

#define SENSOR_COUNT 2

volatile uint16_t ADCResults[SENSOR_COUNT]; //array for holding adc conversion outputs. First bit used as a counter so interupt knows which bit to place result in

void init_adc(void);
void getADCData(void);
void displayResults(void);

void init_adc(void)
{
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1); //ADC rate
    ADMUX |= _BV(REFS0) | _BV(REFS1); //Reference voltages for all
    ADCSRA |= _BV(ADIE); //Enable ADC interrupt
    sei();
}


ISR(ADC_vect) //interrupt handler for completed adc conversion
{
    uint16_t result = ADC; //Read ADC register value
    ADCResults[0] = ADCResults[0] + 1; //Add one to ADC results counter bit
    ADMUX = 0xc0 + ADCResults[0]; //Move channel along by 1 each time
    ADCResults[ADCResults[0]] = result; //Save result to ADCresults array
    ADCSRA |= _BV(ADSC); //Enable ADC for another conversion
}

void getADCData(void)
{
    ADCResults[0] = 0; //Reset ADCResalt counter bit
    ADMUX = 0xc0; //Reset ADC channel back to 0
    ADCSRA |= _BV(ADEN); //Start conversion
    while(ADCResults[0] < SENSOR_COUNT) { //Repeat loop to keep IC in IDLE while conversion is done
        enterSleepMode(IDLE);
    }
    ADCSRA &= ~_BV(ADEN); //Ensure ADC is disabled by clearing by manually

    displayResults();
    _delay_ms(2); //Device enters sleep too fast for UART to send data
}

void displayResults(void) //Will be used for transmission of data when needed
{
    for(uint8_t i = 0; i < SENSOR_COUNT; i++) {
    	switch((char)i) {
    	case 0:
    		printf("\nBattery voltage: %.2f", getBatteryLevel(ADCResults[i + 1]));
    	}
    	printf("\nChannel %d: %4d", i, ADCResults[i + 1]);
    }

}

#endif /* ADC_H_ */
