/*
 *      Author: NRS1G15
 *
 */

#include "debug.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void init_spi_slave(void) { 		//Atmega is slave to ESP
    DDRB = _BV(PB4); 				//Enable pull-up resistor on SS pin
    SPCR = _BV(SPE) | _BV(SPIE);	// Enable SPI and SPI interrupt
    sei();
}

ISR(SPI_STC_vect) { //interrupt handler for SPI complete transfer or received (works by when SPDR is full it creates interrupt flag).
	cli();
	while (1) {
		static uint16_t temp = 0;
		if((SPDR - temp) > 1)
			printf("\nerror");
		temp = SPDR;
		while(!(SPSR & _BV(SPIF))); //Wait for transfer complete
	}

}

int main(void)
{
	init_debug_uart0();
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\nUART0 debug init complete");
	init_spi_slave();

	while(1);
}

