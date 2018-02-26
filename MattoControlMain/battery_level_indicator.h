/*
 * battery_level_indicator.h
 *
 *  Created on: Feb 25, 2018
 *      Author: NRS1G15
 */

#ifndef BATTERY_LEVEL_INDICATOR_H_
#define BATTERY_LEVEL_INDICATOR_H_

double getBatteryLevel(uint16_t ADCData)
{
	double ADCV = (ADCData*3.3)/1024;
	double dividerNetwork = 120217.0 /(389735 + 120217);
	return ADCV/dividerNetwork; //Convert ADC hex to voltage then potential divider network of measured resistances
}

#endif /* BATTERY_LEVEL_INDICATOR_H_ */
//0.2357
