/*
 *      Author: NRS1G15
 *
 */

#include "ADC.h"
#include "debug.h"
#include "power_saving.h"
#include "SPI_slave.h"
#include "external_interrupt.h"
#include "ADC_UART_testing.h" // COMMENT OUT WHEN USING AUDIO MODULE
#include "interpretSPI.h"
//#include "UART_audio_module.h"
#include "RGB_control.h"
#include "photosynthesis.h"

int main(void)
{
	/*
	 * Removed inits when they are not needed for certain testing.
	 * E.G when when using external interrupt for testing ADC comment out SPI init.
	 */

	init_debug_uart0();
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\nUART0 debug init complete");
	//init_uart1();	// initialize UART for Audio module
	//printf("\nUART1 init for audio module complete");
    init_adc();
    printf("\nADC init complete");
    initHumiditySense();
    printf("\nHumidity sensor enabled.");
    initPhotosynthesisAssist();
    printf("\nPhotosynthesis Assist Enabled");
    init_power_saving();
    printf("\nPower saving complete:\nttwi disabled");
    init_spi_slave();
    printf("\nSPI slave enabled");
    init_external_interrupts();
    printf("\nInt0,2 enabled");
    printf("\nADC_UART_testing included: type any char to active all channels ADC.");
    init_RGB_LEDs();
    printf("\nRGB control enabled");
    _delay_ms(1); //Device enters sleep too fast for UART to send data 
    
	while(1) { enterSleepMode(IDLE); //Keep device in IDLE while waiting for SPI transfer complete interrupt
    }
}
