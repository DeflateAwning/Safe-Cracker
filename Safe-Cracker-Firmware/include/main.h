
#ifndef MAIN_PROJECT_H
#define MAIN_PROJECT_H

#include <Arduino.h>

#include <AccelStepper.h>


#include "pins.h"



void setupSteppers();
void doHardwareTest();
void doSetupInstructions();
bool checkSafeOpenHandle();
bool readSafeOpen();
void setStepperEnable(bool state);
void dial_turnToPosition(int targetDigit, int dir);


#endif
