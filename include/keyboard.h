#ifndef _keyboard_h_
#define _keyboard_h_
#include <util/twi.h>
#include "globals.h"

void keyboardInit();

uint8_t readKeys(uint8_t previousKeysState, uint8_t &keyHoldCtr);

#endif // !_keyboard_h_