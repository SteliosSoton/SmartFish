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

#define RECIEVE_MODE 'R';
#define TRANSMIT_MODE 'T';
volatile char SPIStatus = TRANSMIT_MODE;
volatile uint8_t temp;

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
    switch(SPIStatus) {
    case 'T':
    	for(uint8_t i = 0; i < strlen(sendData); i++) {
			PORTB &= ~_BV(PB4);
			SPDR = sendData[i];
			while(!(SPSR & _BV(SPIF)));
			printf("\nSent data: %c", sendData[i]);
			PORTB |= _BV(PB4);
			_delay_ms(10);
    	}
    	SPIStatus = RECIEVE_MODE;
    	break;
    case 'R':
    	while(!(bufferBit == '$')) {
			PORTB &= ~_BV(PB4);
			SPDR = 120;
			while(!(SPSR & _BV(SPIF)));
			bufferBit = SPDR;
			if(firstBit) {
				bufferBit = '*';
				firstBit = 0;
			}
			printf("\nRecieved data: %c", bufferBit);
			PORTB |= _BV(PB4);
    	}
		SPIStatus = TRANSMIT_MODE;
    	break;
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
			_delay_ms(10);
		}
	}
}
