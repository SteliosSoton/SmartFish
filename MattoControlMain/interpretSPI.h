/*
 * interpretSPI.h
 *
 *  Created on: 26 Feb 2018
 *      Author: mp7g16
 */

#ifndef INTERPRETSPI_H_
#define INTERPRETSPI_H_

#include "UART_audio_module.h"
#include "pump_control.h"
#include "RGB_control.h"

#define WATER_PLANT 0x01
#define REQUEST_SENSOR_DATA 0x02
#define AUDIO 0x03
#define RGB_CONTROL 0x04

uint16_t * sensorArray;	// array to hold sensor data

uint16_t *getSensorArray(void){
	return sensorArray;
}

void testReceived(SPIdata received){
    	// Check command to see what to do (where to send the "commandInfo")
    	switch(received.command){
    	case WATER_PLANT:	// water plant
    		printf("\nWatering Plant...\n");
    		togglePump(received.commandInfo[0]);
    		break;
    	case REQUEST_SENSOR_DATA:	// request data
    		//printf("\nGetting ADC data...");
    		sensorArray = getSensorData();
    		break;
    	case AUDIO:	// audio
    		sendCommand(received.commandInfo[0], received.commandInfo[1], received.commandInfo[2]);
    		break;
    	case RGB_CONTROL:
    		setRGBColour(received.commandInfo[0], received.commandInfo[1], received.commandInfo[2]);
    		break;
    	}
}

#endif /* INTERPRETSPI_H_ */
