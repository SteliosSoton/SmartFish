/*
 *      Author: Nathan
 *      Contributions: Matt
 */

#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <string.h>

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
void tx(char *sendData) {
	uint8_t firstBit = 1;
	char bufferBit = 0;
	/* The following code assumes the following:
	 * The master will send a command then the slave will return some data back. Using the format % is start bit and $ is end bit.
	 * TODO  certain commands are only a one way communcation so this needs to be accounted for
	 */

	for(uint8_t i = 0; i < strlen(sendData); i++) { // For the length of the string (command) sending
		PORTB &= ~_BV(PB4); // set SS pin low for transmission
		SPDR = sendData[i]; // Set SPI register to nth character of command
		while(!(SPSR & _BV(SPIF))); // Wait for transmission complete
		printf("\nSent data: %c", sendData[i]);
		PORTB |= _BV(PB4); // Set SS pin high again after transmission
		_delay_ms(10);
	}

	while(!(bufferBit == '$')) { // Keeps looping until end bit $ is recieved from slave
		PORTB &= ~_BV(PB4);
		SPDR = 120; // Dummy data just to start master SCK (SPI clock) which slave uses to send data with
		while(!(SPSR & _BV(SPIF))); // Wait for transmission (receiving) complete
		bufferBit = SPDR; // Read SPDR register (which now has received byte from slave or still 120 if slave hasnt sent anything)
		if(firstBit) { /* From my code there is 1 cycle where slave sends nothing (even if data sent straight away)
		 	 	 	 	* so $ is still in SPDR which bufferBit will become ending the while loop straight away. This just sets bufferBit to *
		 	 	 	 	* so it doesnt end loop. */
			bufferBit = '*';
			firstBit = 0;
		}
		printf("\nRecieved data: %c", bufferBit);
		PORTB |= _BV(PB4);
	}
}


int main(void)
{
	init_spi_master();	// initialise SPI as master or slave
	init_debug_uart0();	// initialise UART debug
    init_interrupts();
    
    uint8_t i;
	for(;;) {
        for(i = 0; i < 100; i++) {
			tx("%HelloBOBPants$");
			_delay_ms(100);
		}
	}
}
