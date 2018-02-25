/*
 * PowerSaving.h
 *
 *  Created on: Feb 25, 2018
 *      Author: NRS1G15
 */

#ifndef POWER_SAVING_H_
#define POWER_SAVING_H_

#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>

#define STANDBY 4
#define IDLE 0

void init_power_saving(void);
void enterSleepMode(uint8_t m);

void init_power_saving(void)
{
    power_timer0_disable();
    power_timer1_disable();
    power_twi_disable();
}

void enterSleepMode(uint8_t m) {
    set_sleep_mode(m); //Set wanted sleep mode
    sleep_enable(); //Set sleep bit
    sei(); //Force enable interrupts while CPU in sleep
    sleep_cpu(); //Put CPU to sleep
    sleep_disable(); //Clear sleep bit
}

#endif /* POWER_SAVING_H_ */
