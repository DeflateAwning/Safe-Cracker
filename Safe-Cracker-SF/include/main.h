
#ifndef MAIN_PROJECT_H
#define MAIN_PROJECT_H

#include <Arduino.h>

#include <Servo.h>

#include "pins.h"
#include "display.h"
#include "cracking.h"
#include "controls.h"


// testing.cpp function prototypes
void testServo();
void testHandleButton(void);
void positionTesting();

// measuring.cpp function prototypes
void measureDiscC(int numberOfTests);
void measureIndent(int &indentLocation, int &indentWidth, int &indentDepth);

#endif
