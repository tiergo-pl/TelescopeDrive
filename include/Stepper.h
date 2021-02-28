#ifndef _Stepper_h_
#define _Stepper_h_

#include <util/twi.h>
#include "globals.h"


void stepperInit();
void stepperClr();
void stepHalfDown();
void stepHalfUp();

#endif // !_Stepper_h_