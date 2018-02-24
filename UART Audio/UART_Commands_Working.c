#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

// use 2nd Il Matto as SPI inputs for commands - controlled by push buttons etc.?
// change bunch of defines into arrays for each command with matching data?

// Actions from data sheet
#define ACT_NEXT		0x01	// go to next song
#define ACT_PREV		0x02	// go to previous song
#define ACT_PLAY_WITH_INDEX	0x03	// play song at index XX (01, 02, etc.)
#define ACT_VOL_UP		0x04	// volume increases by 1 (0-30)
#define ACT_VOL_DOW		0x05	// volume decreases by 1 (0-30)
#define ACT_VOL_SET		0x06	// set volume to XX (0x1E = 30, 0x0F = 15)
#define ACT_S_CYCLE_PLAY	0x08	// single cycle play the first song
#define ACT_DEV_SEL		0x09	// select the storage device to TF card
#define ACT_SLEEP_MODE		0x0a	// chip enters sleep mode
#define ACT_WAKE		0x0b	// chip wakes up
#define ACT_RESET		0x0c	// chip reset
#define ACT_PLAY		0x0d	// resume play back
#define ACT_PAUSE		0xOe	// play back is paused
#define ACT_PLAY_WITH_FF	0x0f	// play the song with the directory /ZZ/YYYxxx.mp3
#define ACT_STOP		0x16	// stop play back completely
#define ACT_F_CYCLE_PLAY	0x17	// cycle play through folder XX
#define ACT_SHUFFLE_PLAY	0x18	// shuffle play through folder XX
#define ACT_PLAY_WITH_VOL	0x22	// set the volume to XX and play song YY

//Volume (Hex -> Decimal 0-30)
#define V_0			0x00
#define V_1			0x01
#define V_2			0x02
#define V_3			0x03
#define V_4			0x04
#define V_5			0x05
#define V_6			0x06
#define V_7			0x07
#define V_8			0x08
#define V_9			0x09
#define V_10			0x0a
#define V_11			0x0b
#define V_12			0x0c
#define V_13			0x0d
#define V_14			0x0e
#define V_15			0x0f
#define V_16			0x10
#define V_17			0x11
#define V_18			0x12
#define V_19			0x13
#define V_20			0x14
#define V_21			0x15
#define V_22			0x16
#define V_23			0x17
#define V_24			0x18
#define V_25			0x19
#define V_26			0x1a
#define V_27			0x1b
#define V_28			0x1c
#define V_29			0x1d
#define V_30			0x1e

//Data
#define NONE			0x00	// no data - 00
#define SD			0x02	// microSD storage device
#define TRACK1			0x01	// Monteverdi Maria Vespers - Ave Maris Stella (8:20)
#define TRACK2			0x02	// Mozart - Piano Concerto #21 In C, Andante (6:46)
#define TRACK3			0x03	// Mozart - Symphony #41 In C,  Jupiter  Finale   Molto Allegro (6:23)
#define TRACK4			0x04	// TCHAIKOVSKY - Symphony no6 (Pathetique) - Karajan - movt 2 (8:56)

char TxData[8];

void init_uart0(void)
{
	/* Configure 9600 baud, 8-bit, no parity and one stop bit */

	const int baud_rate = 9600;
	UBRR0H = (F_CPU/(baud_rate*16L)-1) >> 8;	// Register H/L pair represents 16-bit value UBRRn
	UBRR0L = (F_CPU/(baud_rate*16L)-1);		// UBRRnL [7:0], UBRRnH [15:8]

	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	// Control and Status Register B - [RXCIE TXCIE UDRIE RXEN TXEN UCSZ2 RXB8 TXB8]
	// RX Complete Interrupt Enable, TX Complete Interrupt Enable
	// USART Data Register Empty Interrupt Enable
	// Transmit and Receive Enable bits (TXEN & RXEN)
	// Character Size - combined with the UCSZ[1:0] bit in UCSRnC, sets number of data bits in a frame the receiver and transmitter use
	// Receive Data Bit 8 - 9th data bit of the received character when operating with serial frames with 9 data bits
	// Transmit Data Bit 8 - 9th data bit in the character to be transmitted when operating with serial frames with 9 data bits

	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
	// Control and Status Register C [UMSEL UMSEL UOM UPM USBS UCSZ1 UCSZ0 UCPOL]
	// Mode Select[0 0] - Asynchronous USART ([0 1] - Synchronous)
	// Parity Mode[0 0] - disabled, [0 1] - reserved, [1 0] - enabled even parity, [1 1] enabled odd parity
	// Stop Bit Select[0] - 1-bit, [1] - 2-bit
	// Character Size[2:0] - [000] 5-bit, [001] 6-bit, [010] 7-bit, [011] 8-bit, [111] 9-bit
	// Clock Parity [0] asynchronous mode - T_Rising R_Falling, [1] - T_Falling R_Rising
}

void send_ch(uint8_t byte)
{
	while (!(UCSR0A & _BV(UDRE0)));	// end of transmission marker
	UDR0 = byte;			// USART Data Register - into Tx shift register to send
}

void send_str(char * str)
{
	for(int x=0;x<8;x++)		// loops through 8 bytes of Transmit Data
	{
		send_ch(*str++);	// loops through byte (string) sending each char
	}
}

void sendCommand(char action, char data1, char data2){
		TxData[0] = 0x7e;	// Every command starts with 0x7E - start byte
		TxData[1] = 0xff;	// Version Information
		TxData[2] = 0x06;	// # bytes in command without start & end bytes
		TxData[3] = action;	// command from predefined list in data sheet
		TxData[4] = 0x00;	// 0x00 = not feedback, 0x01 = feedback
		TxData[5] = data1;	// 1st half of data
		TxData[6] = data2;	// 2nd half of data
		TxData[7] = 0xef;	// end byte

		send_str(TxData);	// send TxData byte strings
}

int main(void)
{
	init_uart0();

	_delay_ms(500);

	// select storage device
	sendCommand(ACT_DEV_SEL, NONE, SD);

	_delay_ms(200);

	// play track 2 at volume 20/30
	sendCommand(ACT_PLAY_WITH_VOL, V_20, TRACK2);

	_delay_ms(150000);

	// change to the next song (doesn't loop round ends)
	sendCommand(ACT_NEXT, NONE, NONE);

	//_delay_ms(300000);
	// stop the play back
	//sendCommand(ACT_STOP, V_20, TRACK2);

}
