#include "parse.h"

uint8_t detectEndlCmdline(char *cmdline, char *inputString)
{
  uint8_t i = 0;
  while (i < strlen(inputString))
  {
    if (inputString[i] == '\n' || inputString[i] == '\r')
    {
      cmdline[0] = 0;
      strncpy(cmdline, inputString, i);
      cmdline[i] = 0;
      inputString[0] = 0;
      return i;
    }
    else
      ++i;
  }
  return 0;
}

void parseCmdline(char *cmdLine)
{
  char uartOutputString[128];
  char *s_value;
  uint32_t value;
  char *end_str;
  char *token = strtok_r(cmdLine, " ", &end_str);

  while (token != NULL)
  {
    char *end_token;
    char *cmd = strtok_r(token, "=-:", &end_token);
    s_value = strtok_r(NULL, "=-:", &end_token);
    value = atol(s_value);

    if (!strcmp(cmd, CMD_SAVE))
    {
      eeprom_update_dword(saved_interval1, interval1);
      eeprom_update_dword(saved_interval2, interval2);
      eeprom_update_dword(saved_interval3, interval3);
      eeprom_update_dword(saved_intervalBuzzer, intervalBuzzer);
      eeprom_update_dword(saved_testVar1, testVar1);
      uartTransmitString((char *)"...Saved\r\n");
    }
    else if (!strcmp(cmd, CMD_SHOW))
    {
      sprintf(uartOutputString, "mainClk= %lu, cmdLine: [%s], interval1= %lu, interval2= %lu, interval3= %lu, intervalBuzzer= %lu , testVar1= %lu\r\n", mainClock_us_temp, cmd, interval1, interval2, interval3, intervalBuzzer, testVar1);
      uartTransmitString(uartOutputString);
    }
    else if (!strcmp(cmd, CMD_HELP))
    {
      uartTransmitString((char *)"Usage: [COMMAND] ... [VARIABLE=VALUE] ... \r\nexample: i2=100000 freq=1000 save show ?\r\n");
      for (size_t i = 0; i < testVar1; i++)
      {
        if (uartTXBuf.isNotEmpty())
        {
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
        }
        if (uartTXBuf.isEmpty())
        {
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
        }
      }

      uartTransmitString((char *)"Commands:\r\ni[n]=[t]\t set intervals n=1..3 to time tx10 microseconds\r\n");
      uartTransmitString((char *)"save\tsave parameters to eeprom\r\nshow\t show active parameters\r\n");
    }
    else if (!strcmp(cmd, CMD_interval1))
    {
      if (value)
      {
        interval1 = value / MAIN_CLOCK_TICK;
      }
      else
        uartTransmitString((char *)"Input valid number of microseconds. Nothing changed yet...\r\n");
    }
    else if (!strcmp(cmd, CMD_interval2))
    {
      if (value)
      {
        interval2 = value / MAIN_CLOCK_TICK;
      }
      else
        uartTransmitString((char *)"Input valid number of microseconds. Nothing changed yet...\r\n");
    }
    else if (!strcmp(cmd, CMD_interval3))
    {
      if (value)
      {
        interval3 = value / MAIN_CLOCK_TICK;
      }
      else
        uartTransmitString((char *)"Input valid number of microseconds. Nothing changed yet...\r\n");
    }
    else if (!strcmp(cmd, CMD_freqBuzzer))
    {
      if (value)
      {
        intervalBuzzer = 50000 / value;
      }
      else
        uartTransmitString((char *)"Input valid frequency in Hz. Nothing changed yet...\r\n");
    }
    else if (!strcmp(cmd, CMD_random))
    {
      int val_rand = rand();
      if (value)
      {
        val_rand %= value;
      }
      sprintf(uartOutputString, "Random number is: %i \r\n", val_rand);
      uartTransmitString(uartOutputString);
    }
    else if (!strcmp(cmd, CMD_testVar1))
    {
      testVar1 = value;
    }

    else
      uartTransmitString((char *)"Wrong command or nothing entered\r\n");

    token = strtok_r(NULL, " ", &end_str);
  }
}