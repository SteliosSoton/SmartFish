/*
 *      Author: Nathan
 *      Contributions: Matt
 */

#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>

#define STANDBY 4
#define IDLE 0

#define SENSOR_COUNT 2

#define RECIEVE_MODE 'R';
#define TRANSMIT_MODE 'T';
volatile char SPIStatus = TRANSMIT_MODE;
volatile uint8_t temp;

volatile uint16_t ADCResults[SENSOR_COUNT]; //array for holding adc conversion outputs. First bit used as a counter so interupt knows which bit to place result in
    
void init_power_saving(void);
void init_adc(void);
void init_spi_slave(void);
void getADCData(void);
void displayResults(void);
void enterSleepMode(uint8_t m);

void init_power_saving(void)
{
    power_timer0_disable();
    power_timer1_disable();
    power_twi_disable();
}

void init_adc(void)
{
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1); //ADC rate
    ADMUX |= _BV(REFS0) | _BV(REFS1); //Reference voltages for all 
    ADCSRA |= _BV(ADIE); //Enable ADC interrupt
}

void init_spi_slave(void) { //Atmega is slave to ESP
    DDRB = _BV(PB6); //Enable pull-up resistor on SS pin
    SPCR = _BV(SPE) | _BV(SPIE); // Enable SPI and SPI interrupt
    sei();//Enable interrupts
}

ISR(SPI_STC_vect) { //interrupt handler for SPI complete transfer
    switch(SPIStatus) {
    case 'T':
    	SPDR = temp + 1;
    	printf("\nSent data: %d", temp + 1);
    	SPIStatus = RECIEVE_MODE;
    	break;
    case 'R':
    	temp = SPDR;
    	printf("\nRecieved data: %d", temp);
    	SPIStatus = TRANSMIT_MODE;
    	break;
    }
    /*
    * Here will go matt code for getting data to string and then depending on string,
    * call ADC function or something like water pump function (has yet to be made).
    * I have put all the ADC code in function getADCData so you just call this and it will place 
    * conversions in the ADCResults variable.
    */
}

ISR(ADC_vect) //interrupt handler for completed adc conversion
{
    uint16_t result = ADC; //Read ADC register value 
    ADCResults[0] = ADCResults[0] + 1; //Add one to ADC results counter bit
    ADMUX = 0xc0 + ADCResults[0]; //Move channel along by 1 each time
    ADCResults[ADCResults[0]] = result; //Save result to ADCresults array
    ADCSRA |= _BV(ADSC); //Enable ADC for another conversion
}

void getADCData(void)
{
    ADCResults[0] = 0; //Reset ADCResalt counter bit 
    ADMUX = 0xc0; //Reset ADC channel back to 0
    ADCSRA |= _BV(ADEN); //Start conversion
    while(ADCResults[0] < SENSOR_COUNT) { //Repeat loop to keep IC in IDLE while conversion is done
        enterSleepMode(IDLE);
    }
    ADCSRA &= ~_BV(ADEN); //Ensure ADC is disabled by clearing by manually

    displayResults();
    _delay_ms(2); //Device enters sleep too fast for UART to send data 
}

    
void displayResults(void) //Will be used for transmission of data when needed
{
    uint8_t i;
    for(i = 0; i < SENSOR_COUNT; i++) {    printf("\nchannel %d: %4d", i, ADCResults[i + 1]); }
    
}

void enterSleepMode(uint8_t m) {
    set_sleep_mode(m); //Set wanted sleep mode
    sleep_enable(); //Set sleep bit
    sei(); //Force enable interrupts while CPU in sleep
    sleep_cpu(); //Put CPU to sleep
    sleep_disable(); //Clear sleep bit
}

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
