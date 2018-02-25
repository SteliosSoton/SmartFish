/*
 * external_interrupt.h
 *
 *  Created on: Feb 25, 2018
 *      Author: NRS1G15
 */

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

#include <avr/io.h>
#include "debug.h"
#include <avr/interrupt.h>
#include "power_saving.h"
#include "ADC.h"

#define SENSOR_COUNT 2

void init_external_interrupts(void)
{
    EICRA |= _BV(ISC01) | _BV(ISC11); //Set trigger to rising edge for INT0
    PORTD |= _BV(PD2); //Enable pull-up on INT0 pin
    EIMSK |= _BV(INT0); //Enabled interrupt 0 (PD2)
    sei(); //Enable interrupts
}

ISR(INT0_vect) //interrupt 0 handler (used for triggering adc conversions)
{
    EIMSK &= ~_BV(INT0); //Disable interrupt 0 (PD2)
    printf("\nin INT0 interrupt");

    ADCResults[0] = 0; //Reset ADCResalt counter bit
    ADMUX = 0xc0; //Reset ADC channel back to 0
    ADCSRA |= _BV(ADEN); //Enable ADC for conversion
    while(ADCResults[0] < SENSOR_COUNT) { //Repeat loop to keep IC in IDLE while conversion is done
        enterSleepMode(IDLE);
    }
    ADCSRA &= ~_BV(ADEN); //Disable ADC as no longer needed

    displayResults();
    _delay_ms(2); //Device enters sleep too fast for UART to send data
    EIMSK |= _BV(INT0); //ReEnable interrupt 0 (PD2)
}

#endif /* EXTERNAL_INTERRUPT_H_ */
