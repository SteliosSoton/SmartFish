/*
 * SPIsetup.c
 *
 *      Author: Nathan
 */

#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

void init_spi_slave(void) { 
    DDRB = _BV(PB6); //Enable pull-up resistor on SS pin
    SPCR = _BV(SPE); // Enable SPI 
}

uint8_t rx(void) {
    while(!(SPSR & _BV(SPIF))); 
    return SPDR; 
}

int main(void) {
    init_spi_slave();
    init_debug_uart0();
    
    while(1) {
        printf("\nData recieved: %d", rx());
    }
}
