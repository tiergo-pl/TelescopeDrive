#ifndef _parse_h_
#define _parse_h_

#include <string.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#include "globals.h"
#include "uart.h"

// commands in cli
#define CMD_SAVE "save"
#define CMD_SHOW "show"
#define CMD_HELP "?"
#define CMD_interval1 "i1" 
#define CMD_interval2 "i2" 
#define CMD_interval3 "i3"
#define CMD_freqBuzzer "freq"
#define CMD_random "rand"
#define CMD_testVar1 "t1"

//---------------------

 
uint8_t detectEndlCmdline(char *cmdline, char *inputString);
void parseCmdline(char * cmdLine);


#endif // !_parse_h_
