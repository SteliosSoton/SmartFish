#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <inttypes.h>

#define STANDBY 4
#define IDLE 0

/* | ------------- Master ------------- |
*  |	  PD0	     -	     C232 Tx	|
*  |	  PD1	     -	     C232 Rx	|
*  |	  PB4	     -	    Slave PB4	|
*  |	  PB5	     -	    Slave PB5	|
*  |	  PB6	     -	    Slave PB6	|
*  |	  PB7	     -	    Slave PB7	|
*  | ---------------------------------- | */

/* | ------------ Commands ------------ |
*  |	  1	     -	  play track 1	|
*  |	  2	     -	  play track 2	|
*  |	  3	     -	  play track 3	|
*  |	  4	     -	  play track 4	|
*  |	  p	     -	    pause	|
*  |	  r	     -	    resume	|
*  |	  +	     -	 increment vol	|
*  |	  -	     -	 decrement vol	|
*  |	  <	     -	 previous song	|
*  |	  >	     -	   next song	|
*  |	  s	     -	     stop	|
*  |	  z	     -	    sleep	|
*  |	  w	     -	     wake	|
*  | ---------------------------------- | */

/* ------------------------------ SPI ------------------------------ */
void init_interrupts(void) {
    sei();
}

void init_spi_master(void) {
	// out: MOSI, SCK, SS (in: MISO)
	DDRB = _BV(PB4) | _BV(PB5) | _BV(PB7); // Set = 1: PB4 (SS), PB5 (MOSI), PB7(SCK)

	PORTB |= _BV(PB4); //Set SS pin high as this is default setting for SPI communications

	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0) | _BV(SPR1);	// SPI Control Register
    SPCR &= ~_BV(SPI2X);
	// SPE - the SPI is enabled when this bit is 1
	// MSTR - configures SPI as master
	// SPI2X, SPR0, SPR1 - configure SPI clock frequency (0 1 1 fosc/128)
}

void tx(uint8_t sendData) {
    PORTB &= ~_BV(PB4); //Set Atmega SS pin low so it knows it should listen
	SPDR = sendData;	// configure SPI Data Register
	while(!(SPSR & _BV(SPIF)));	// wait for transmission complete
    //printf("\nSent data: %d", sendData);
    PORTB |= _BV(PB4); //Set atmega SS pin high
}
/* ---------------------------- SPI end ----------------------------- */



/* ------------------------------ UART ------------------------------ */
void init_uart0(void)
{
	/* Configure 9600 baud, 8-bit, no parity and one stop bit */
	const int baud_rate = 9600;
	UBRR0H = (F_CPU/(baud_rate*16L)-1) >> 8;
	UBRR0L = (F_CPU/(baud_rate*16L)-1);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

char get_ch(void)
{
	while(!(UCSR0A & _BV(RXC0)));
	return UDR0;
}

void put_ch(char ch)
{
	while (!(UCSR0A & _BV(UDRE0)));
	UDR0 = ch;
}

void put_str(char *str)
{
	int i;
	for(i=0; str[i]; i++) put_ch(str[i]);
}
/* ---------------------------- UART end ----------------------------- */


int main(void)
{
	init_spi_master();	// initialise SPI as master or slave
	//init_debug_uart0();	// initialise UART debug
    init_interrupts();

    char ch;
    init_uart0();
    put_str("\n\rHello from Il Matto\n\r");

    /* forever loop */
    for (;;)
    {
    	/* get character from UART */
    	ch = get_ch();
    	/* send message back to the host terminal */
    	put_str("You sent the character '");
        _delay_ms(10);

    	put_ch(ch);	// UART out
        _delay_ms(10);
        tx(ch);		// SPI out

        _delay_ms(10);

    	put_str("'\n\r");
    }

}
