/*
 *      Author: NRS1G15
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"

void init_spi_slave(void) { 		//Atmega is slave to ESP
    DDRB = _BV(PB6); 				//Enable pull-up resistor on SS pin
    SPCR = _BV(SPE) | _BV(SPIE);	// Enable SPI and SPI interrupt
    sei();
}

ISR(SPI_STC_vect) { //interrupt handler for SPI complete transfer or received (works by when SPDR is full it creates interrupt flag).
	printf("\nRecieved: SPDR");
}
int main(void)
{
	while(1);
}
