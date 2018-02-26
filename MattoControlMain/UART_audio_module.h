/*
 * interpretSPI.h
 *
 *  Created on: 26 Feb 2018
 *      Author: mp7g16
 */

#ifndef UART_AUDIO_MODULE_H_
#define UART_AUDIO_MODULE_H_

volatile UARTdata TxData;

void init_uart1(void)
{
	const int baud_rate = 9600;
	UBRR1H = (F_CPU/(baud_rate*16L)-1) >> 8;
	UBRR1L = (F_CPU/(baud_rate*16L)-1);
	UCSR1B = _BV(RXEN1) | _BV(TXEN1);
	UCSR1C = _BV(UCSZ10) | _BV(UCSZ11);
}

void send_byte(uint8_t byte)
{
	while (!(UCSR1A & _BV(UDRE1)));	// end of transmission marker
	UDR1 = byte;					// USART Data Register - into Tx shift register to send
}

void send_data(UARTdata transmit)
{
	for(int x=0;x<8;x++)	// loops through 8 bytes of Transmit Data
	{
		switch(x){
			case 0:
				send_byte(transmit.start);
				break;
			case 1:
				send_byte(transmit.version);
				break;
			case 2:
				send_byte(transmit.numBytes);
				break;
			case 3:
				send_byte(transmit.action);
				break;
			case 4:
				send_byte(transmit.feedback);
				break;
			case 5:
				send_byte(transmit.data1);
				break;
			case 6:
				send_byte(transmit.data2);
				break;
			case 7:
				send_byte(transmit.end);
				break;
			default:
				break;
		}
	}
}

void sendCommand(char action, char data1, char data2){
		TxData.start	= 0x7e;	// Every command starts with 0x7E - start byte
		TxData.version 	= 0xff;	// Version Information
		TxData.numBytes = 0x06;	// # bytes in command without start & end bytes
		TxData.action 	= action;	// command from predefined list in data sheet
		TxData.feedback = 0x00;	// 0x00 = not feedback, 0x01 = feedback
		TxData.data1 	= data1;	// 1st half of data
		TxData.data2 	= data2;	// 2nd half of data
		TxData.end		= 0xef;	// end byte

		send_data(TxData);	// send TxData byte strings
}


#endif /* UART_AUDIO_MODULE_H_ */
