/*
 * SPIsetup.c
 *
 *  Created on: 19 Feb 2018
 *      Author: Matt
 */

#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

char data;
char toSend[10] = "abcdefghij";


void init_spi_master(void) {
	// out: MOSI, SCK, SS (in: MISO)
	DDRB = _BV(PB4) | _BV(PB5) | _BV(PB7); // Set = 1: PB4 (SS), PB5 (MOSI), PB7(SCK)

	PORTB = 0xFF; //This is very important!! need to toggle Slave select line from

	SPCR = (1 << SPE) | (1 << MSTR) | (0 << SPI2X) | (1 << SPR0) | (1 << SPR1);	// SPI Control Register
	// SPE - the SPI is enabled when this bit is 1
	// MSTR - configures SPI as master
	// SPI2X, SPR0, SPR1 - configure SPI clock frequency (0 1 1 fosc/128)

	PORTB &= ~(1 << PB4); //toggle slave select line from high to low

}
		//uint8_t
void tx(char sendData) {
	SPDR = sendData;	// configure SPI Data Register
	while(!(SPSR & _BV(SPIF)));	// wait for transmission complete
}

int main(void)
{
	init_spi_master();	// initialise SPI as master or slave
	init_debug_uart0();	// initialise UART debug

	while(1){

		for(int j=0;j<sizeof(toSend);j++){
			tx(toSend[j]);
			printf("\n%c", toSend[j]);
			_delay_ms(5);
		}


		/*
		for(int i=0;i<254;i++)
		{
			tx(i);
			printf("\n%d", i);
			_delay_ms(10);
		}
		*/

	}

}
