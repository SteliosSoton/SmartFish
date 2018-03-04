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
#include "RGBW.h"

#define WATER_PLANT 0x01
#define REQUEST_SENSOR_DATA 0x02
#define AUDIO 0x03
#define RGB_CONTROL 0x04

int muted = 0;	// boolean for mute toggle

uint8_t RGBStatus[3];

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
    		if(received.commandInfo[0] == 0x06){	// mute toggle command
    			printf("toggling mute: %d\n", muted);
    			if(muted == 0){
    				sendCommand(received.commandInfo[0], received.commandInfo[1], received.commandInfo[2]); // mute it as requested
    				muted = 1;
    			}
    			else if(muted == 1){
    				sendCommand(received.commandInfo[0], received.commandInfo[1], 0x1E);	// unmute it back to volume 20 (0x14)
    				muted = 0;
    			}
    		}
    		else{
    			sendCommand(received.commandInfo[0], received.commandInfo[1], received.commandInfo[2]);
    		}
    		break;
    	case RGB_CONTROL:
			RGBStatus[0]=received.commandInfo[0]; RGBStatus[1]=received.commandInfo[1]; RGBStatus[2]=received.commandInfo[2];
			RGBWaterLevel();
    		break;
    	}
}

#endif /* INTERPRETSPI_H_ */
