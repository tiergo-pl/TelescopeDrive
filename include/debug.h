#ifndef _debug_h_
#define _debug_h_

#include <avr/io.h>

#define debugPin0 PB0
#define debugPin1 PB1


/*
    PORTB |= _BV(debugPin1);
    PORTB &= ~_BV(debugPin1);
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    PORTB |= _BV(debugPin1);
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    PORTB &= ~_BV(debugPin1);
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    PORTB |= _BV(debugPin1);
    PORTB &= ~_BV(debugPin1);
*/
/*
          PORTB |= _BV(debugPin1);
          PORTB &= ~_BV(debugPin1);
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
          PORTB |= _BV(debugPin1);
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
          PORTB &= ~_BV(debugPin1);
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
          PORTB |= _BV(debugPin1);
          PORTB &= ~_BV(debugPin1);

                _delay_us (1000);

          PORTB |= _BV(debugPin1);
          asm("nop");
          asm("nop");
          PORTB &= ~_BV(debugPin1);
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
          PORTB |= _BV(debugPin1);
          PORTB &= ~_BV(debugPin1);

*/



#endif