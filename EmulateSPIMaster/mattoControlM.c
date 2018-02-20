/*
 * SPIsetup.c
 *
 *  Created on: 19 Feb 2018
 *      Author: Matt
 *      Editted by Nathan
 */

#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>

#define STANDBY 4
#define IDLE 0

void init_interrupts(void) {
    sei(); 
}
void init_spi_master(void) {
	// out: MOSI, SCK, SS (in: MISO)
	DDRB = _BV(PB4) | _BV(PB5) | _BV(PB7); // Set = 1: PB4 (SS), PB5 (MOSI), PB7(SCK)

	PORTB |= _BV(PB4); //Set SS pin high as this is default setting for SPI communications

	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0) | _BV(SPR1);	// SPI Control Register
    SPCR &= ~_BV(SPI2X);
	// SPE - the SPI is enabled when this bit is 1
	// MSTR - configures SPI as master
	// SPI2X, SPR0, SPR1 - configure SPI clock frequency (0 1 1 fosc/128)
}
void tx(uint8_t sendData) {
    PORTB &= ~_BV(PB4); //Set Atmega SS pin low so it knows it should listen
	SPDR = sendData;	// configure SPI Data Register
	while(!(SPSR & _BV(SPIF)));	// wait for transmission complete
    printf("\nSent data: %d", sendData);
    PORTB |= _BV(PB4); //Set atmega SS pin high 
}

int main(void)
{
	init_spi_master();	// initialise SPI as master or slave
	init_debug_uart0();	// initialise UART debug
    init_interrupts();
    
    uint8_t i;
	for(;;) {
        for(i = 0; i < 100; i++) {
			tx(i);
            _delay_ms(1000);
		}
	}
}
