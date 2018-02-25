#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>

#define STANDBY 4
#define IDLE 0
#define SENSOR_COUNT 2

/* | ------------- Slave -------------- |
*  |	  PD0	     -	    Audio Tx	|
*  |	  PD1	     -	    Audio Rx	|
*  |	  VCC	     -	    Audio VCC	|
*  |	  GND	     -	    Audio GND	|
*  |	  PB4	     -	   Master PB4	|
*  |	  PB5	     -	   Master PB5	|
*  |	  PB6	     -	   Master PB6	|
*  |	  PB7	     -	   Master PB7	|
*  | ---------------------------------- | */

// Actions from data sheet
#define ACT_NEXT 			0x01	// go to next song
#define ACT_PREV 			0x02	// go to previous song
#define ACT_PLAY_WITH_INDEX 0x03	// play song at index XX (01, 02, etc.)
#define ACT_VOL_UP 			0x04	// volume increases by 1 (0-30)
#define ACT_VOL_DOWN		0x05	// volume decreases by 1 (0-30)
#define ACT_VOL_SET 		0x06	// set volume to XX (0x1E = 30, 0x0F = 15)
#define ACT_S_CYCLE_PLAY	0x08	// single cycle play the first song
#define ACT_DEV_SEL 		0x09	// select the storage device to TF card
#define ACT_SLEEP_MODE 		0x0a	// chip enters sleep mode
#define ACT_WAKE	 		0x0b	// chip wakes up
#define ACT_RESET	 		0x0c	// chip reset
#define ACT_RESUME	 		0x0d	// resume play back
#define ACT_PAUSE	 		0x0e	// play back is paused
#define ACT_PLAY_WITH_FF	0x0f	// play the song with the directory /ZZ/YYYxxx.mp3
#define ACT_STOP	 		0x16	// stop play back completely
#define ACT_F_CYCLE_PLAY	0x17	// cycle play through folder XX
#define ACT_SHUFFLE_PLAY	0x18	// shuffle play through folder XX
#define ACT_PLAY_WITH_VOL	0x22	// set the volume to XX and play song YY

//Data
#define NONE				0x00	// no data - 00
#define SD					0x02	// microSD storage device
#define TRACK1				0x01	// Monteverdi Maria Vespers - Ave Maris Stella (8:20)
#define TRACK2				0x02	// Mozart - Piano Concerto #21 In C, Andante (6:46)
#define TRACK3				0x03	// Mozart - Symphony #41 In C,  Jupiter  Finale   Molto Allegro (6:23)
#define TRACK4				0x04	// TCHAIKOVSKY - Symphony no6 (Pathetique) - Karajan - movt 2 (8:56)

char TxData[8];

void init_power_saving(void);
void init_spi_slave(void);
void enterSleepMode(uint8_t m);

void init_uart0(void);
char vol(int vol);
void sendCommand(char action, char data1, char data2);
void send_ch(uint8_t byte);
void send_str(char * str);


void init_power_saving(void)
{
    power_timer0_disable();
    power_timer1_disable();
    power_twi_disable();
}

void init_spi_slave(void) { //Atmega is slave to ESP
    DDRB = _BV(PB6); //Enable pull-up resistor on SS pin
    SPCR = _BV(SPE) | _BV(SPIE); // Enable SPI and SPI interrupt
    sei();//Enable interrupts
}

char vol(int vol){ return vol; } // return the int as a char -> hex!

ISR(SPI_STC_vect) { //interrupt handler for SPI complete transfer
	char rx = SPDR;

    switch(rx){
    case '1':
    	sendCommand(ACT_PLAY_WITH_VOL, vol(20), TRACK1); // play track 1 at volume 20/30
    	break;
    case '2':
    	sendCommand(ACT_PLAY_WITH_VOL, vol(20), TRACK2); // play track 2 at volume 20/30
    	break;
    case '3':
    	sendCommand(ACT_PLAY_WITH_VOL, vol(20), TRACK3); // play track 3 at volume 20/30
    	break;
    case '4':
    	sendCommand(ACT_PLAY_WITH_VOL, vol(20), TRACK4); // play track 4 at volume 20/30
    	break;
    case 'p':
    	sendCommand(ACT_PAUSE, NONE, NONE); // pause play back
    	break;
    case 'r':
    	sendCommand(ACT_RESUME, NONE, NONE); // resume play back
    	break;
    case '+':
    	sendCommand(ACT_VOL_UP, NONE, NONE); // increase volume by 1
    	break;
    case '-':
    	sendCommand(ACT_VOL_DOWN, NONE, NONE); // decrease volume by 1
    	break;
    case '<':
    	sendCommand(ACT_PREV, NONE, NONE); // go back to previous song
    	break;
    case '>':
    	sendCommand(ACT_NEXT, NONE, NONE); // go to next song
    	break;
    case 's':
    	sendCommand(ACT_STOP, NONE, NONE); // go to next song
    	break;
    case 'z':
    	sendCommand(ACT_SLEEP_MODE, NONE, NONE); // go to next song
    	break;
    case 'w':
    	sendCommand(ACT_WAKE, NONE, NONE); // go to next song
    	break;
    default:
    	// send SPI communication back to say no command match found
    	break;
    }

    /*
    * Here will go matt code for getting data to string and then depending on string,
    * call ADC function or something like water pump function (has yet to be made).
    * I have put all the ADC code in function getADCData so you just call this and it will place
    * conversions in the ADCResults variable.
    */
}

/* ------------------- Power Management ---------------------- */
void enterSleepMode(uint8_t m) {
    set_sleep_mode(m); //Set wanted sleep mode
    sleep_enable(); //Set sleep bit
    sei(); //Force enable interrupts while CPU in sleep
    sleep_cpu(); //Put CPU to sleep
    sleep_disable(); //Clear sleep bit
}
/* ------------------ Power Management End ------------------- */

/* ------------------------------------ UART start ------------------------------------ */
void init_uart0(void)
{
	const int baud_rate = 9600;
	UBRR0H = (F_CPU/(baud_rate*16L)-1) >> 8;
	UBRR0L = (F_CPU/(baud_rate*16L)-1);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

void send_ch(uint8_t byte)
{
	while (!(UCSR0A & _BV(UDRE0)));	// end of transmission marker
	UDR0 = byte;					// USART Data Register - into Tx shift register to send
}

void send_str(char * str)
{
	for(int x=0;x<8;x++)	// loops through 8 bytes of Transmit Data
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
/* ------------------------------------ UART  end ------------------------------------ */

int main(void)
{
    init_power_saving();
    init_spi_slave();
    
    init_uart0();						// initialise UART for Audio control
	sendCommand(ACT_DEV_SEL, NONE, SD);	// setup audio module by selecting storage device

	while(1) { enterSleepMode(IDLE); } 	//Keep device in IDLE while waiting for SPI transfer complete interrupt
}
