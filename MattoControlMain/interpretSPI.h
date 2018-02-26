/*
 * interpretSPI.h
 *
 *  Created on: 26 Feb 2018
 *      Author: mp7g16
 */

#ifndef INTERPRETSPI_H_
#define INTERPRETSPI_H_

#include "UART_audio_module.h"

void testReceived(SPIdata received){
    	// Check command to see what to do (where to send the "commandInfo")
    	switch(received.command){
    	case 0x01:	// water plant
    		printf("\nWatering Plant...");
    		//water_plant();
    		break;
    	case 0x02:	// request data
    		printf("\nGetting ADC data...");
    		//getADCdata();
    		break;
    	case 0x03:	// audio
    		sendCommand(received.commandInfo[0], received.commandInfo[1], received.commandInfo[2]);
    		break;
    	}
}

#endif /* INTERPRETSPI_H_ */
