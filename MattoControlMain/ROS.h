#include <avr/io.h>
#include "debug.h"
#include "external_interupts.h"
#include "sensors.h"
#include "RGBS.h"

ISR(INT2_vect) //interrupt 2 handler
{
    EIMSK &= ~_BV(INT2); //Disable interrupt 2 (PB2)
    printf("\nin INT2 interrupt");
    toggle_LEDs(1,0,0);
    _delay_ms(33);
    toggle_LEDs(0,1,0);
    _delay_ms(33);
    toggle_LEDs(0,0,1);
    _delay_ms(33);
    int i = getWaterLevel();
    switch (i)
          case 100 : //white
          case 90  : //blue
          case 80  : //blue
          case 70  : //green
          case 60  : //green
          case 50  : //yellow
          case 40  : //yellow
          case 30  : //amber
          case 20  : //red
          default  : //red
          
                
   
    EIMSK |= _BV(INT2); //ReEnable interrupt 2 (PB2)
    if (PINC&&_BV(2)) {
    toggle_LEDs(0,0,1);
    _delay_ms(33);
    toggle_LEDs(0,1,0);
    _delay_ms(33);
    toggle_LEDs(1,0,0);
    _delay_ms(33);
    }
}


