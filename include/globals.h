#ifndef _globals_h_
#define _globals_h_

#include <stdint.h>
//-----------------------------
// macros and vars used in software clock
// remember [extern] statement
extern volatile uint32_t mainClock_us; //Software timer incremented by hw timer interrupt
extern volatile uint32_t mainClock_us_temp; //Copy of sw timer used in calculations
extern volatile uint32_t clk1;
extern volatile uint32_t clk2;
extern volatile uint32_t clk3;
extern volatile uint32_t clkBuzzer; // buzzer tone generation
#define MAIN_CLOCK_TICK 10 // 1 tick of mainClock_us duration in microseconds (max 128 due to hw limitations)
// set following values in microsecs.:
extern volatile uint32_t interval1;                        //use variable for mutable value readable from eeprom
extern uint32_t *saved_interval1; //and pointer to its saved value
extern volatile uint32_t interval2;                        //use variable for mutable value readable from eeprom
extern uint32_t *saved_interval2; //and pointer to its saved value
extern volatile uint32_t interval3;                        //use variable for mutable value readable from eeprom
extern uint32_t *saved_interval3; //and pointer to its saved value
extern volatile uint32_t intervalBuzzer; // buzzer tone generation
extern uint32_t *saved_intervalBuzzer;
//-----------------------
// used gpio pins
#define Led_builtin PB5
#define LED_STATUS PD2
#define BUTTON_PLAY PD5
#define BUTTON_FF PD6
#define BUTTON_REV PD7
// #define Buzzer PC3 
//--------------------
#endif