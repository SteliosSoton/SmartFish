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

void init_external_interrupts(void)
{
    DDRC &= ~_BV(2);
    PORTC |= _BV(2); //PULL UP THE INPUT
    EICRA &= ~_BV(ISC21) & ~_BV(ISC20); //SET INT2 ACTIVE ON LOW LEVEL
    EICRA |= _BV(ISC01) | _BV(ISC11); //Set trigger to rising edge for INT0
    PORTD |= _BV(PD2); //Enable pull-up on INT0 pin
    EIMSK |= _BV(INT0); //Enabled interrupt 0 (PD2)
    sei(); //Enable interrupts
}

ISR(INT0_vect) //interrupt 0 handler (used for triggering adc conversions)
{
    EIMSK &= ~_BV(INT0); //Disable interrupt 0 (PD2)
    printf("\nin INT0 interrupt");

    EIMSK |= _BV(INT0); //ReEnable interrupt 0 (PD2)
}

#endif /* EXTERNAL_INTERRUPT_H_ */
