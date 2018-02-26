/*
 * SPI.h
 *
 *  Created on: Feb 25, 2018
 *      Author: NRS1G15
 */

#ifndef SPI_SLAVE_H_
#define SPI_SLAVE_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"
#include "dataStruct.h"
#include "interpretSPI.h"
#include "UART_audio_module.h"

#define RECEIVE_MODE 'R'
#define TRANSMIT_MODE 'T'

#define START 0x7e
#define END 0x7f

volatile char SPIStatus = RECEIVE_MODE; //Tells SPI interrupt which mode to be in, transmission or receive

void init_spi_slave(void);
uint8_t getRequestedData(char request);

volatile SPIdata receive; 		//Create new instance of data for receive transmissions
volatile SPIdata transmit; 	//transmit transmissions


void init_spi_slave(void) { 		//Atmega is slave to ESP
    DDRB = _BV(PB6); 				//Enable pull-up resistor on SS pin
    SPCR = _BV(SPE) | _BV(SPIE);	// Enable SPI and SPI interrupt
    sei();
}

uint8_t getRequestedData(char request) { //Gets the data requested by ESP command
	uint8_t dataRequestComplete = 0;
	switch(request) {
	case REQUEST_SENSOR_DATA: //request identified as REQUEST_SENSOR_DATA
		transmit.version = 0x01;
		transmit.command = REQUEST_SENSOR_DATA; //send back command to master to ensure request was correctly identified
		transmit.commandInfoLength = 0x02;
		transmit.commandInfo[0] = 0x0f;
		transmit.commandInfo[1] = 0x01;
		transmit.feedback = 0x00;

		dataRequestComplete = 1; //Successful data request so return value set to 1
		break;
	}
	return dataRequestComplete;
}


ISR(SPI_STC_vect) { //interrupt handler for SPI complete transfer or received (works by when SPDR is full it creates interrupt flag).
	static char transmissionCounter = 0; 			//Keeps track of current stage in communications.
	static uint8_t validCommand = 0;				//turns to 1 when currently in a valid command, START bit has been seen.
	static uint8_t commandInfoLengthCounter = 0; 	//Keeps track of how far into commandInfo communication is currently.
	static char dataReady = 0; 						//Flag for when data is ready to be sent back, if feedback was 1.
	char receivedData = SPDR; 						//Get received data from register.

    switch(SPIStatus) {
    case 'T': 					// Transmission case
    	switch(dataReady) { 	//Data might not be ready straight away so this ensure no data is sent until then
    	case 0: 				//Data not ready yet so just do nothing
    		break;
    	case 1: 				//Data is ready
    		transmissionCounter = transmissionCounter + 1; //Adds one each time there is a transfer so current data-bit is tracked.
    		switch(transmissionCounter) { //Switch based on how far into transmission
    		case 0x01: 		//First data bit (send start bit)
    			SPDR = START;
    			break;
    		case 0x02: 		//Second data bit (send version)
    			SPDR = transmit.version;
    			break;
    		case 0x03: 		//Third data bit (send command)
    			SPDR = transmit.command;
    			break;
    		case 0x04: 		//Fourth data bit (send commandInfo length)
    			SPDR = transmit.commandInfoLength;
    			break;
    		case 0x05: 		//Fifth to nth data bit depending how how much data being sent
				if(commandInfoLengthCounter < (transmit.commandInfoLength - 1)) //If counter isn't at end of commandInfo array
					transmissionCounter = transmissionCounter - 1; 				//Counteract increase in transmission counter (L78) to keep transmission in this case until array is complete
				SPDR = transmit.commandInfo[commandInfoLengthCounter]; 			//Place current commandInfo data into register
				commandInfoLengthCounter = commandInfoLengthCounter + 1; 		//increase commandInfo counter so next time next byte is send
				break;
    		case 0x06: //6th or nth + 1 data bit (feedback)
    			SPDR = transmit.feedback;
    			break;
    		case 0x07: //ending data bit
    			SPDR = END;
				commandInfoLengthCounter = 0; //Resets for next receive
				transmissionCounter = 0; //Resets for next transmission
				SPIStatus = RECEIVE_MODE; //Places slave back into receive mode for next transfer
    			break;
    			}
    		}
    	break;

    case 'R': // Receive case
    	switch(receivedData) {
		case START:
			printf("\nStart command is: %x", receivedData);
			validCommand = 1; // Signals next received bytes are command bits
			break;

		case END:
			if(validCommand) { // Checks if start bit has been seen before end bit - Other wise it knows it started to see transmission after it began
				validCommand = 0; // Command is over so this is reset
				commandInfoLengthCounter = 0; //Resets for next receive
				transmissionCounter = 0; //Resets for next transmission
				printf("\nEnd command is: %x", receivedData);
				if(receive.feedback) {
					dataReady = getRequestedData(receive.command); //Get requested data
					SPIStatus = TRANSMIT_MODE; // Sets program to transmission mode to reply to master
				}
			}
			break;

		default:
			if(validCommand) {// If bit received is after start bit and isn't end bit it increments buffer counter
				transmissionCounter = transmissionCounter + 1;  //Adds one each time there's a transfer so current data-bit is tracked. (same as L78)
				switch(transmissionCounter) { //Below is very similar to receiving, saves the received data instead of sending saved data
				case 0x01:
					receive.version = receivedData;
					printf("\nVersion is: %x", receivedData);
					break;
				case 0x02:
					receive.command = receivedData;
					printf("\nCommand is: %x", receivedData);
					break;
				case 0x03:
					receive.commandInfoLength = receivedData;
					printf("\nCommandInfoLength is: %x", receivedData);
					if(!(receive.commandInfoLength))
						transmissionCounter = transmissionCounter + 1;
					break;
				case 0x04:
					if(commandInfoLengthCounter < (receive.commandInfoLength - 1))
						transmissionCounter = transmissionCounter - 1;
					receive.commandInfo[commandInfoLengthCounter] = receivedData;
					printf("\nCommandInfo is: %x", receivedData);
					commandInfoLengthCounter = commandInfoLengthCounter + 1;
					break;
				case 0x05:
					receive.feedback = receivedData;
					printf("\nFeedback is: %x", receivedData);
					break;
				}
			}
		}

    	testReceived(receive);	// interpret the received command in "interpretSPI.h"

    break;
    }
}

#endif /* SPI_SLAVE_H_ */
