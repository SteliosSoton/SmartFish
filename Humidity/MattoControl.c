#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>

#ifndef STANDBY
#define STANDBY 4
#endif

#ifndef IDLE
#define IDLE 0
#endif

#define SENSOR_COUNT 2
#define HUMIDITY_SENSORS 1
volatile uint16_t ADCResults[SENSOR_COUNT +1]; /*array for holding adc conversion outputs.
												First bit used as a counter so interupt
												knows which bit to place result in*/
volatile uint16_t humidityResults[HUMIDITY_SENSORS +1]; /*array for holding humidity sensor outputs.
														First bit used as a counter so interupt
														knows which bit to place result in*/


    
void init_power_saving(void);
void init_adc(void);
void init_external_interrupts(void);
void displayResults(void);
void enterSleepMode(uint8_t m);
void humiditySense(void); 
void initHumiditySense(void);


void humiditySense(void){
	
	TCNT1 = 0x00; /* Clear Timer 1 */
	
	int i;/* Isn't INT obvious? I'll see myself out...*/
	
	for( i=1; i<(HUMIDITY_SENSORS+1); i++){/* Go through all the soil humidity sensors*/
	
	if(i==1) PINC |= _BV(0);
	else if (i==2) |= _BV(1);
	
	TCCR1B |= _BV(CS12) | _BV(CS11) | _BV(CS10); /* Start Timer 1 :External Clock on T1 Pin, rising edge */
	
	_delay_ms(0.1); /*Wait a fixed amount of time for general reference*/
	
	TCCR1B &= ~_BV(CS12) & ~_BV(CS11) & ~_BV(CS10);/* Stop Timer 1*/
	
	humidityResults[0] = i; /*Increment sensor count bit*/
	humidityResults[i] = TCNT1; /* Read Timer 1*/
	TCNT1 = 0x00; /* Clear Timer 1 */
	
	if(i==1) PINC &= ~_BV(0);
	else if (i==2) &= ~_BV(1);
	}
	
}

void initHumiditySense(void){
	
	DDRB &= ~_BV(1);/*Set Pin B1 as input*/
	PORTB &= ~_BV(1);/*Pull down the resistor*/
	
	DDRC |= _BV(0) | _BV(1);/*Set Pins C0, C1 as ouputs (for activating the humidity sensors)*/
	PORTC &= ~_BV(0) & ~_BV(1);/*Pull down the resistors*/

}

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

ISR(INT0_vect) //interrupt 0 handler (used for starting gathering sensor data)
{
    EIMSK &= ~_BV(INT0); //Disable interrupt 0 (PD2)
    printf("\nin INT0 interrupt");
	
	humiditySense();/*Start the Humidity Sensing prior to ADC Sensing*/
	
    ADCResults[0] = 0; //Reset ADCResult counter bit 
    ADMUX = 0xc0; //Reset ADC channel back to 0
    ADCSRA |= _BV(ADEN); //Enable ADC for conversion
    while(ADCResults[0] < SENSOR_COUNT) { //Repeat loop to keep IC in IDLE while conversion is done
        enterSleepMode(IDLE);
    }
    ADCSRA &= ~_BV(ADEN); //Disable ADC as no longer needed

    displayResults();/*Upgraded for outputting all senses*/
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
	for(i = 1; i<(HUMIDITY_SENSORS+1); i++) printf("\nchannel %d: %4d", i, humidityResults[i]); 
    
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
	initHumiditySense();
	printf("\nHumidity Sense Initialised");
    init_power_saving();
    printf("\nPower saving complete:\n\ttimer0 disabled \n\ttimer1 disabled \n\ttwi disabled \n\tusart1 disabled");
    init_external_interrupts();
    printf("\nINT0 external interupt enabled");
    _delay_ms(1); //Device enters sleep too fast for UART to send data 
    
	while(1) { enterSleepMode(STANDBY); //Keep device in standby while waiting for external interrupt
    }
}
