/*
 * battery_level_indicator.h
 *
 *  Created on: Feb 25, 2018
 *      Author: NRS1G15
 */

#ifndef BATTERY_LEVEL_INDICATOR_H_
#define BATTERY_LEVEL_INDICATOR_H_

uint16_t getBatteryLevel(uint16_t ADCData)
{
        return (((ADCData*3.3)/1024)/(120207/(389728 + 120207))); //Convert ADC hex to voltage then potential divider network of measured resistances
}

#endif /* BATTERY_LEVEL_INDICATOR_H_ */
