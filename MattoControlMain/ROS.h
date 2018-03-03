#include <avr/io.h>
#include "debug.h"
#include "external_interupt.h"
#include "sensors.h"
#include "RGB_control.h"

#ifndef ROS_H_
#define ROS_H_


ISR(INT2_vect) //interrupt 2 handler
{
    EIMSK &= ~_BV(INT2); //Disable interrupt 2 (PB2)
    printf("\nin INT2 interrupt");
    setRGBColour(1,0,0);
    _delay_ms(333);
    setRGBColour(0,1,0);
    _delay_ms(333);
    setRGBColour(0,0,1);
    _delay_ms(333);
    int i = getWaterLevel();
    
    switch (i){
          case 100 : //white 1,1,1
            setRGBColour(1,1,1);
            break;
          case 90  : //cyan 0,1,1
            setRGBColour(0,1,1);
            break;
          case 80  : //blue 0,0,1
            setRGBColour(0,0,1);
            break;
          case 70  : //blue 0,0,1
            setRGBColour(0,0,1);
            break;
          case 60  : //green 0,1,0
            setRGBColour(0,1,0);
            break;
          case 50  : //green 0,1,0
            setRGBColour(0,1,0);
            break;
          case 40  : //yellow 1,1,0
            setRGBColour(1,1,0);
            break;
          case 30  : //yellow 1,1,0
            setRGBColour(1,1,0);
            break;
          case 20  : //red 1,0,0
            setRGBColour(1,0,0);
            break;
          default  : //red 1,0,0
            setRGBColour(1,0,0);
            break;
    }
                
   
    EIMSK |= _BV(INT2); //ReEnable interrupt 2 (PB2)
    if (PINB&&_BV(2)) {
    setRGBColour(0,0,1);
    _delay_ms(333);
    setRGBColour(0,1,0);
    _delay_ms(333);
    setRGBColour(1,0,0);
    _delay_ms(333);
    }
}
#endif
