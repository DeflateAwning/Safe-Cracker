
#ifndef MAIN_PROJECT_H
#define MAIN_PROJECT_H

#include <Arduino.h>

#include <AccelStepper.h>


#include "pins.h"



void setupSteppers();
void doHardwareTest();
void doSetupInstructions();
void doCracking();

bool checkSafeOpenHandle();
bool readSafeOpen();
void setStepperEnable(bool state);
void dial_turnToPosition(int targetDigit, int dir);
void spinToDigit(int fullSpinCount, int spinToDigit, int dir);
void spinToDigit(int fullSpinCount, int targetDigit, int dir, bool debugOutput);

String getDirString(int dir);

void runStepperUntilDone(AccelStepper targetStepperMotor);

#endif
