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
volatile uint16_t ADCResults[SENSOR_COUNT]; //array for holding adc conversion outputs. First bit used as a counter so interupt knows which bit to place result in
    
void init_power_saving(void);
void init_adc(void);
void init_external_interrupts(void);
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
    ADCSRA |= _BV(ADEN); //Enable ADC
}

void init_external_interrupts(void)
{
    EICRA |= _BV(ISC01) | _BV(ISC11); //Set trigger to rising edge for INT0
    PORTD |= _BV(PD2); //Enable pull-up on INT0 pin
    EIMSK |= _BV(INT0); //Enabled interrupt 0 (PD2)
    sei(); //Enable interrupts
}

void init_spi_master(void) //Setups atmega as a SPI master 
{ 
    DDRB = _BV(PB4) | _BV(PB5) | _BV(PB7); //Enable pullup resistors on portB pins 4, 5, 7
    SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPI2X);
    SPCR = _BV(SPIE) //Enables SPI transfer complete interrupt
}
void SPIMasterTransmit(char data) 
{ 
    SPDR = data;
    while(!(SPSR & _BV(SPIF))); 
}

uint8_t SPISlaveRecieve(void) 
{ 
    while(!(SPSR & _BV(SPIF)));
    return SPDR; 
 }

ISR(SPI_STC_vect)

ISR(INT0_vect) //interrupt 0 handler (used for triggering adc conversions)
{
    EIMSK &= ~_BV(INT0); //Disable interrupt 0 (PD2)
    printf("\nin INT0 interrupt");
    
    ADCResults[0] = 0; //Reset ADCResalt counter bit 
    ADMUX = 0xc0; //Reset ADC channel back to 0
    ADCSRA |= _BV(ADEN); //Enable ADC for conversion
    while(ADCResults[0] < SENSOR_COUNT) { //Repeat loop to keep IC in IDLE while conversion is done
        enterSleepMode(IDLE);
    }
    ADCSRA &= ~_BV(ADEN); //Disable ADC as no longer needed

    displayResults();
    _delay_ms(2); //Device enters sleep too fast for UART to send data 
    EIMSK |= _BV(INT0); //ReEnable interrupt 0 (PD2)
}

ISR(ADC_vect) //interrupt handler for completed adc conversion
{
    uint16_t result = ADC; //Read ADC register value 
    ADCResults[0] = ADCResults[0] + 1; //Add one to ADC results counter bit
    ADMUX = 0xc0 + ADCResults[0]; //Move channel along by 1 each time
    ADCResults[ADCResults[0]] = result; //Save result to ADCresults array
    ADCSRA |= _BV(ADSC); //Enable ADC for another conversion
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
    init_spi_master();
    for(;;) {
        SPIMasterTransmit('e');
        _delay_ms(500);
    }
    
        
	// init_debug_uart0();
    // printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	// printf("\nUART debug init complete");
    // init_adc();
    // printf("\nADC init complete");
    // init_power_saving();
    // printf("\nPower saving complete:\n\ttimer0 disabled \n\ttimer1 disabled \n\ttwi disabled \n\tusart1 disabled");
    // init_external_interrupts();
    // printf("\nINT0 external interupt enabled");
    // _delay_ms(1); //Device enters sleep too fast for UART to send data 
    
	// while(1) { enterSleepMode(STANDBY); //Keep device in standby while waiting for external interrupt
    // }
}