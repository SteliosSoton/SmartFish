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

	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPI2X);	// SPI Control Register
	// SPE - the SPI is enabled when this bit is 1
	// MSTR - configures SPI as master
	// SPI2X - double SPI Speed bit, SPI speed (SCK Frequency) doubles in Master Mode
	/* F_SCK = F_CPU/2 */
}

void init_spi_slave(void) { /* out: MISO, in: MOSI, SCK, /SS */
    DDRB = _BV(PB6); SPCR = _BV(SPE); /* Enable SPI */ 
}

uint8_t rx(void) {
    while(!(SPSR & _BV(SPIF))); 
    return SPDR; 
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
    // init_spi_slave();
    
    // while(1) {
        // printf("%d", rx(););
    // }
    
	while(1){
		tx(150);
		_delay_ms(500);
	}
}
