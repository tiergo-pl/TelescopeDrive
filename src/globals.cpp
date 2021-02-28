#include "globals.h"
 
volatile uint32_t mainClock_us = 0; //Software counter incremented by timer interrupt
volatile uint32_t mainClock_us_temp;
volatile uint32_t clk1 = 0;
volatile uint32_t clk2 = 0;
volatile uint32_t clk3 = 0;
volatile uint32_t interval1;                        //use variable for mutable value readable from eeprom
uint32_t *saved_interval1 = (uint32_t *)0; //and pointer to its saved value
volatile uint32_t interval2;                        //use variable for mutable value readable from eeprom
uint32_t *saved_interval2 = (uint32_t *)4; //and pointer to its saved value
volatile uint32_t interval3;                        //use variable for mutable value readable from eeprom
uint32_t *saved_interval3 = (uint32_t *)8; //and pointer to its saved value

volatile uint32_t clkKeys;
volatile uint32_t intervalKeys;
uint32_t *saved_intervalKeys = (uint32_t *)12;

volatile int32_t testVar1;
uint32_t *saved_testVar1 = (uint32_t *)16;

volatile uint8_t workMode = 0;


