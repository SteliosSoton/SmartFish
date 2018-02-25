/*
 *      Author: NRS1G15
 *
 */

#include "ADC.h"
#include "debug.h"
#include "power_saving.h"
#include "SPI_slave.h"

int main(void)
{
	init_debug_uart0();
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\nUART debug init complete");
    init_adc();
    printf("\nADC init complete");
    init_power_saving();
    printf("\nPower saving complete:\n\ttimer0 disabled \n\ttimer1 disabled \n\ttwi disabled \n\tusart1 disabled");
    init_spi_slave();
    printf("\nSPI slave enabled");
    _delay_ms(1); //Device enters sleep too fast for UART to send data 
    
	while(1) { enterSleepMode(IDLE); //Keep device in IDLE while waiting for SPI transfer complete interrupt
    }
}
