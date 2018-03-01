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
#define MISO 0x7d
volatile int slaveTransmit = 0;
volatile int ZeroRX;
volatile int OneRX;
volatile int TwoRX;
volatile int slaveTransmitStarted;

#define WATER_PLANT 0x01			// header tags for data sent in "command"
#define REQUEST_SENSOR_DATA 0x02	// actually hex data/command sent in "commadInfo"
#define AUDIO 0x03

volatile char SPIStatus = RECEIVE_MODE; //Tells SPI interrupt which mode to be in, transmission or receive

uint16_t * sensorData;	// local array to hold sensor data

void init_spi_slave(void);

volatile SPIdata receive; 	//Create new instance of data for receive transmissions
volatile SPIdata transmit; 	//transmit transmissions


void init_spi_slave(void) { 		//Atmega is slave to ESP
    DDRB = _BV(PB6); 				//Enable pull-up resistor on SS pin
    SPCR = _BV(SPE) | _BV(SPIE);	// Enable SPI and SPI interrupt
    sei();
}
						// char request
uint8_t setupTransmitData() { //Gets the data requested by ESP command
	uint8_t dataRequestComplete = 0;

	//printf("setupSlaveTransmitRegister()\n");

	sensorData = getSensorArray();	// get array from  ADC.h

	// convert ADC double values into hex
	int ADCdata0I = sensorData[0];	// can only do to 3 decimal places as a byte is 8 bits [largest = 255 (25.5)]
	char ADCdata0 = ADCdata0I;
	char ADCdata1 = sensorData[1];
	char ADCdata2 = sensorData[2];

	printf("%d, %d, %d\n", sensorData[0], sensorData[1],sensorData[2]);
	printf("%x, %x, %x\n\n", ADCdata0, ADCdata1, ADCdata2);

	transmit.version = 0x01;				// fill slave register as normal
	transmit.command = REQUEST_SENSOR_DATA; //send back command to master to ensure request was correctly identified
	transmit.commandInfoLength = 0x03;		// 3 bytes of info - battery level, light, humidity
	transmit.commandInfo[0] = ADCdata0;		// battery data
	transmit.commandInfo[1] = ADCdata1;		// light data
	transmit.commandInfo[2] = ADCdata2;		// humidity data
	transmit.feedback = 0x00;

	dataRequestComplete = 1; //Successful data request so return value set to 1

	return dataRequestComplete;
}

void SetSlaveRegister(char aaaa){
	//printf("SPDR in function: %x\n", aaaa);
	if(aaaa == 0x7d){
		//printf("STARTED\n");
		slaveTransmitStarted = 1;
	}
	else if(aaaa == 0x00) {
		SPDR = transmit.commandInfo[0];
		//printf("transmit.commandInfo[0]: %x\n", transmit.commandInfo[0]);
		ZeroRX = 1;
	}
	else if(aaaa == 0x01){
		SPDR = transmit.commandInfo[1];
		//printf("transmit.commandInfo[1]: %x\n", transmit.commandInfo[1]);
		OneRX = 1;
	}
	else if(aaaa == 0x02){
		SPDR = transmit.commandInfo[2];
		//printf("transmit.commandInfo[2]: %x\n", transmit.commandInfo[2]);
		TwoRX = 1;
	}
	else{
		int sum = ZeroRX + OneRX + TwoRX;
		//SPDR = sum;	// random value to test
		//printf("Sum: %d", sum);

		if(slaveTransmit == 1){
			//printf("\n\n[slaveTransmit - SUCCESSFUL]\n");
			if(slaveTransmitStarted == 1){
				//printf("[Started - SUCCESSFUL]\n");
				if(sum == 3){
					//printf("[Sum - SUCCESSFUL]\n");
					SPDR = 0x32; // set register to success tag 0x32 (d50)
				}
				else{
					//printf("[Sum - FAILED]\n");
					SPDR = 0x64; // set register to fail tag 0x64 (d100)
				}
			}
			else{
				//printf("[Started - FAILED]\n");
				SPDR = 0x64; // set register to fail tag 0x64 (d100)
			}
		}
		else{
			//printf("[slaveTransmit - FAILED]\n");
			SPDR = 0x64; // set register to fail tag 0x64 (d100)
		}
	}
}


ISR(SPI_STC_vect) { //interrupt handler for SPI complete transfer or received (works by when SPDR is full it creates interrupt flag).
	static char transmissionCounter = 0; 			//Keeps track of current stage in communications.
	static uint8_t validCommand = 0;				//turns to 1 when currently in a valid command, START bit has been seen.
	static uint8_t commandInfoLengthCounter = 0; 	//Keeps track of how far into commandInfo communication is currently.
	//static char dataReady = 0; 						//Flag for when data is ready to be sent back, if feedback was 1.

	char receivedData = SPDR; //Get received data from register.

    switch(SPIStatus) {
    case 'T': 					// Transmission case
    	printf("SPDR : %x\n", SPDR);
    	switch(receivedData) { 	//Data might not be ready straight away so this ensure no data is sent until then
		case MISO:				// master sends signal to prompt slave to fill its register
			slaveTransmit = 1; 	// slave transmitting
			break;
    	case END:
    		slaveTransmit = 0;
    		SPIStatus = RECEIVE_MODE; //Places slave back into receive mode for next transfer
    		break;
    	default:
    		//printf("T defaulted.\n");
    		//SPDR = 0x0E;
    		break;
    	}
    	break;

    case 'R': // Receive case
		switch(receivedData) {
		case START:
			//printf("\nStart command is: %x", receivedData);
			validCommand = 1; // Signals next received bytes are command bits
			break;

		case END:
			if(validCommand) { // Checks if start bit has been seen before end bit - Other wise it knows it started to see transmission after it began
				validCommand = 0; // Command is over so this is reset
				commandInfoLengthCounter = 0; //Resets for next receive
				transmissionCounter = 0; //Resets for next transmission
				//printf("\nEnd command is: %x\n\n", receivedData);
				if(receive.feedback) {
					ZeroRX = 0;
					OneRX = 0;
					TwoRX = 0;
					slaveTransmitStarted = 0;
					SPIStatus = TRANSMIT_MODE;	// Sets program to transmission mode to reply to master
					setupTransmitData();		// Setup transmit data ready to fill slave transmit register
				}
			}
			break;

		default:
			if(validCommand) {// If bit received is after start bit and isn't end bit it increments buffer counter
				transmissionCounter = transmissionCounter + 1;  //Adds one each time there's a transfer so current data-bit is tracked. (same as L78)
				switch(transmissionCounter) { //Below is very similar to receiving, saves the received data instead of sending saved data
				case 0x01:
					receive.version = receivedData;
					//printf("\nVersion is: %x", receivedData);
					break;
				case 0x02:
					receive.command = receivedData;
					printf("Command is: %x\n", receivedData);
					break;
				case 0x03:
					receive.commandInfoLength = receivedData;
					//printf("\nCommandInfoLength is: %x", receivedData);
					if(!(receive.commandInfoLength))
						transmissionCounter = transmissionCounter + 1;
					break;
				case 0x04:
					if(commandInfoLengthCounter < (receive.commandInfoLength - 1))
						transmissionCounter = transmissionCounter - 1;
					receive.commandInfo[commandInfoLengthCounter] = receivedData;
					printf("CommandInfo is: %x\n", receivedData);
					commandInfoLengthCounter = commandInfoLengthCounter + 1;
					break;
				case 0x05:
					receive.feedback = receivedData;
					printf("Feedback is: %x\n", receivedData);
					break;
				}
			}
		}

    	testReceived(receive);	// interpret the received command in "interpretSPI.h"

    break;
    }

    // at the end of each receive if in transmit mode set the SPDR for next receive/transmit
    if(slaveTransmit == 1) SetSlaveRegister(receivedData);
    //printf("\nslaveTransmit: %d\tSPIStatus: %c", slaveTransmit, SPIStatus);
    //printf("\n--------------------\n");
}

#endif /* SPI_SLAVE_H_ */
