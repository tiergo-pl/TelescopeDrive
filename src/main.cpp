// #include <Arduino.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/atomic.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#include "globals.h"
#include "uart.h"
#include "debug.h"
#include "parse.h"
#include "Stepper.h"
#include "keyboard.h"

void timer_init(void)
{
  OCR2A = 2 * MAIN_CLOCK_TICK - 1;                    // reset Timer2 at 2 * MAIN_CLOCK_TICK
  TCCR2A = 0b00000010;                                //((1<<WGM21) | (0<<WGM20));        // Timer2 CTC mode
  TCCR2B = ((0 << CS22) | (1 << CS21) | (0 << CS20)); // clk/8
  TIMSK2 = (1 << OCIE2A);                             // Timer/Counter Interrupt Mask
}

void port_init(void)
{
  DDRB = (1 << Led_builtin) | _BV(debugPin1); // Led builtin (13)
  //DDRC = (1 << debugPin0) | (1 << debugPin1) | (1 << debugPin2) | _BV(Keys);
  DDRD = (1 << LED_STATUS);
}

ISR(TIMER2_COMPA_vect) // TIMER2 interrupt
{
  //  PORTC |= _BV(debugPin1);
  mainClock_us++;
  //  PORTC &= ~_BV(debugPin1);
}

int main()
{
  timer_init();
  port_init();
  keyboardInit();
  uart_init();
  stepperInit();
  sei();

  interval1 = eeprom_read_dword(saved_interval1);
  interval2 = eeprom_read_dword(saved_interval2);
  interval3 = eeprom_read_dword(saved_interval3);
  intervalKeys = eeprom_read_dword(saved_intervalKeys);
  testVar1 = eeprom_read_dword(saved_testVar1);
  char uartInputString[64] = "\0";
  char cmdLine[64] = "\0";
  uint8_t prevKeysState = 0;
  uint8_t keyHoldCounter = 0;
  uint32_t clkMove4X = 0;
  uint32_t clkMove8X = 0;

  while (1)
  {

    ATOMIC_BLOCK(ATOMIC_FORCEON)
    {
      mainClock_us_temp = mainClock_us;
    }

    if ((mainClock_us_temp - clk1) >= interval1)
    {
      clk1 = mainClock_us_temp;
      PORTB ^= 1 << Led_builtin;
    }
    if ((mainClock_us_temp - clk2) >= interval2)
    {
      clk2 = mainClock_us_temp;

      if ((workMode & (1 << MOVE_FOLLOW_STARS)) && !(workMode & (0b01111110)))
      {
        if (workMode & (1 << MOVE_DIRECTION))
        {
          stepHalfUp();
        }
        else
        {
          stepHalfDown();
        }
      }
    }

    if ((mainClock_us_temp - clk3) >= interval3)
    {
      clk3 = mainClock_us_temp;
      if (workMode & (1 << MOVE_FORWARD_MAX))
      {
        if (workMode & (1 << MOVE_DIRECTION))
        {
          stepHalfUp();
        }
        else
        {
          stepHalfDown();
        }
      }
      if (workMode & (1 << MOVE_REVERSE_MAX))
      {
        if (workMode & (1 << MOVE_DIRECTION))
        {
          stepHalfDown();
        }
        else
        {
          stepHalfUp();
        }
      }
    }

    if ((mainClock_us_temp - clkMove8X) >= interval3 * 2)
    {
      clkMove8X = mainClock_us_temp;
      if (workMode & (1 << MOVE_FORWARD_8X))
      {
        if (workMode & (1 << MOVE_DIRECTION))
        {
          stepHalfUp();
        }
        else
        {
          stepHalfDown();
        }
      }
      if (workMode & (1 << MOVE_REVERSE_8X))
      {
        if (workMode & (1 << MOVE_DIRECTION))
        {
          stepHalfDown();
        }
        else
        {
          stepHalfUp();
        }
      }
    }

    if ((mainClock_us_temp - clkMove4X) >= interval3 * 4)
    {
      clkMove4X = mainClock_us_temp;
      if (workMode & (1 << MOVE_FORWARD_4X))
      {
        if (workMode & (1 << MOVE_DIRECTION))
        {
          stepHalfUp();
        }
        else
        {
          stepHalfDown();
        }
      }
      if (workMode & (1 << MOVE_REVERSE_4X))
      {
        if (workMode & (1 << MOVE_DIRECTION))
        {
          stepHalfDown();
        }
        else
        {
          stepHalfUp();
        }
      }
    }

    if ((mainClock_us_temp - clkKeys) >= intervalKeys)
    {
      clkKeys = mainClock_us_temp;
      prevKeysState = readKeys(prevKeysState, keyHoldCounter);
    }

    if (uartEcho())
    {
      if (sizeof(uartInputString) < (strlen(uartInputString) + 2))
        uartInputString[0] = 0;
      uartReceiveString(uartInputString);
      if (detectEndlCmdline(cmdLine, uartInputString))
      {
        parseCmdline(cmdLine);
      }
    }
  }
}
