/*
 * sensors.h
 *
 *  Created on: Feb 27, 2018
 *      Author: NRS1G15 and Stelios
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#define HUMIDITY_SENSORS 1
volatile uint16_t humidityResults[HUMIDITY_SENSORS +1]; /*array for holding humidity sensor outputs.
														First bit used as a counter so interrupt
														knows which bit to place result in*/
double getBatteryLevel(uint16_t ADCData)
{
	double ADCV = (ADCData*3.3)/1024;
	double dividerNetwork = 120217.0 /(389735 + 120217);
    double percentage = 18.182 * (ADCV/dividerNetwork) - 118.18;
    if(percentage > 100)
    	return 100;
    else
    	return percentage; //Convert ADC hex to voltage then potential divider network of measured resistances
}

uint8_t getLDRpercentage(uint16_t ADCValue){

	double voltage = ADCValue*3.3/1024; /*Convert to voltage*/

	if(voltage<=0.074) return 0;
	else if(voltage>=1.931) return 100;
	else return (24.516*(voltage*voltage*voltage) - 36.362*(voltage*voltage) + 32.111*(voltage) + 4.2014);
}

uint16_t getTemperature(uint16_t ADCValue) {
	double voltage = ADCValue*3.3/1024; /*Convert to voltage*/

	return voltage*100 - 273; /*Temperature formula, accurate enough.. */ //????? how does this work -Magic!
} /* With a 1k0 Resistor Temp=voltage*100 *K, then we subtract 273 to turn into *C*/

void initHumiditySense(void){
	DDRB &= ~_BV(1);/*Set Pin B1 as input*/
	PORTB &= ~_BV(1);/*Pull down the resistor*/

	TCCR1A= 0x00;
	TCCR1B= 0x00;
	TCCR1C= 0x00;
	TCNT1 = 0x0000;

	DDRC |= _BV(0) | _BV(6);/*Set Pins C0, C1 as outputs (for activating the humidity sensors), Add more for more sensors*/
	PORTC &= ~_BV(0) & ~_BV(6);/*Pull down the resistors*/
}

uint8_t getHumidityPercentage(void){/*Not yet percentage, more of a humidity id->needs soil testing to associate with humidity states*/
	TCNT1 = 0x0000; /* Clear Timer 1 */
	uint8_t  i;
	for( i=1; i<(HUMIDITY_SENSORS+1); i++) {/* Go through all the soil humidity sensors*/

		switch(i) {
		case 1:
			PINC |= _BV(0);/*Activate first Sensor*/
			break;
		case 2:
			PINC |= _BV(1);/*Activate second Sensor*/
			break;/*Add cases for extra sensors */
		}

		TCCR1B |= _BV(CS12)| _BV(CS11) | _BV(CS10); /* Start Timer 1 :External Clock on T1 Pin, rising edge */

		_delay_ms(10); /*Wait a fixed amount of time for general reference*/

		TCCR1B &= ~_BV(CS12) & ~_BV(CS11) & ~_BV(CS10);/* Stop Timer 1*/

		humidityResults[0] = i; /*Increment sensor count bit*/
		humidityResults[i] = TCNT1; /* Read Timer 1*/
		TCNT1 = 0x0000; /* Clear Timer 1 */

		humidityResults[i]=humidityResults[i]/4045.0*100;

		switch(i) {
		case 1:
			PINC |= _BV(0);/*Deactivate first Sensor*/
			break;
		case 2:
			PINC |= _BV(1);/*Deactivate second Sensor*/
			break;/*Add cases for extra sensors */
		}
	}
 return humidityResults[1];

}
double getWaterLevel(uint16_t ADCData)
{
	double ADCV = (ADCData*3.3)/1024.0;
	if (ADCV<=0.2) return 0;
	else if ((ADCV>0.2)&&(ADCV<=0.3)) return 20;
	else if ((ADCV>0.3)&&(ADCV<=0.4)) return 30;
	else if ((ADCV>0.4)&&(ADCV<=0.5)) return 40;
	else if ((ADCV>0.5)&&(ADCV<=0.6)) return 50;
	else if ((ADCV>0.6)&&(ADCV<=0.7)) return 60;
	else if ((ADCV>0.7)&&(ADCV<=0.8)) return 70;
	else if ((ADCV>0.8)&&(ADCV<=0.9)) return 80;
	else if ((ADCV>0.9)&&(ADCV<=1)) return 90;
	else if ((ADCV>1)) return 100;
		 
    
}

#endif /* SENSORS_H_ */
