/*
 * dataStruct.h
 *
 *  Created on: 26 Feb 2018
 *      Author: Matt
 */

#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_

typedef struct dataSPI { 	//Create new type for holding SPI transmission data
	char version; 			//Version of device sending the data
	char command; 			//Command hex code
	char commandInfoLength; //Length of data sent over command and before end
	char commandInfo[50]; 	//Buffer for command info
	char feedback; 			//If sender wants data in return
}SPIdata; 					//Call this new type of variable 'dataSPI'

typedef struct dataUART { 	//Create new type for holding UART transmission data
	char start; 			// Every command starts with 0x7E - start byte
	char version; 			// Version Information
	char numBytes; 			// # bytes in command without start & end bytes
	char action; 			// command from predefined list in data sheet
	char feedback; 			// 0x00 not feedback , 0x01 feedback
	char data1; 			// 1st data byte
	char data2; 			// 2nd data byte
	char end; 				// end byte
}UARTdata; 					//Call this new type of variable 'dataUART'

#endif /* DATASTRUCT_H_ */
