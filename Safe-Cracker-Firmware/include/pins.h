
#ifndef PINS_PROJECT_H
#define PINS_PROJECT_H

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
#define maxStepsPerSec_dial (stepsPerRev_dial * 2) // sets the speed for the dial (multiplier is the RPM, basically)

// CW and CCW Direction Constants (feed into dir arguments) -> For Dial Only
#define CW  -1
#define CCW  1


#define NUM_DIGITS 100
const uint16_t stepsPerDigit = stepsPerRev_dial / NUM_DIGITS; // 16 steps per digit


#endif
