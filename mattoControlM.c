/*
 * SPIsetup.c
 *
 *  Created on: 19 Feb 2018
 *      Author: Matt
 */

#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

void init_spi_master(void) {
	/* out: MOSI, SCK, /SS, in: MISO */
	DDRB = _BV(PB4) | _BV(PB5) | _BV(PB7); // ?: PB4 (SS), PB5 (MOSI), PB7(SCK)

	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0) | _BV(SPR1);	// SPI Control Register
	// SPE - the SPI is enabled when this bit is 1
	// MSTR - configures SPI as master
	// SPI2X, SPR0, SPR1 - configure SPI clock frequency (0 1 1 fosc/128)
}

void tx(uint8_t b) {
	SPDR = b;	// configure SPI Data Register
	while(!(SPSR & _BV(SPIF)));	// wait for transmission complete
}

void init_spi_slave(void) {
	/* out: MISO, in: MOSI, SCK, /SS */
	DDRB = _BV(PB6);	// Pull-up resistor
	SPCR = _BV(SPE);	/* Enable SPI */
}

uint8_t rx(void) {
	while(!(SPSR & _BV(SPIF)));	// wait for transmission complete
	return SPDR;
}

int main(void)
{
	init_spi_master();	// initialise SPI as master or slave
	init_debug_uart0();
    // init_spi_slave();

    // while(1) {
        // printf("%d", rx(););
    // }

	int i=0;

	while(1){
		tx(i);
        printf("\n%d", i);

		if(i < 254) i++;
		else i =0;
	}
}
