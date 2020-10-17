
#ifndef PINS_PROJECT_H
#define PINS_PROJECT_H

#include "main.h"


// ********** Pin Definitions **********
// Dial -> X Axis on GRBL Board
#define PIN_DIAL_STEP 2
#define PIN_DIAL_DIR  5

// Handle -> Y Axis on GRBL Board
#define PIN_HANDLE_STEP 3
#define PIN_HANDLE_DIR  6

// Handle Open Sensor -> X Axis Limit Switch on GRBL Board
#define PIN_OPEN_SENSOR 9

// Other Pins
#define PIN_STEPPER_ENABLE 8

// Stepper/Driver Configuration
#define stepsPerRev_dial (200*8) // 1/8 microstepping
#define stepsPerRev_handle (200*8) // 1/8 microstepping (use no microstepping for higher torque)
#define maxStepsPerSec_dial (stepsPerRev_dial * 0.25)

// CW and CCW Direction Constants (feed into dir arguments) -> For Dial Only
#define CW  0
#define CCW 1


/*
 * Original pins from the SF project.
 */
//Pin definitions
const byte encoderA = 2;
const byte encoderB = 3;
const byte photo = 5;
const byte motorPWM = 6;
const byte button = 7;
const byte motorReset = 8;
const byte servo = 9;
const byte motorDIR = 10;
const byte buzzer = 11;
const byte LED = 13;

const byte currentSense = A0;
const byte servoPositionButton = A1;
const byte displayLatch = A2;
const byte displayClock = A3;
const byte displayData = A4;


#endif
