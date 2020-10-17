
#ifndef CONTROL_PROJECT_H
#define CONTROL_PROJECT_H

#include "main.h"

int gotoStep(int stepGoal, boolean addAFullRotation);
int stepsRequired(int currentSteps, int goal);
int setDial(int dialValue, boolean extraSpin);
void findFlag();
void resetDiscsWithCurrentCombo(boolean pause);
int convertDialToEncoder(int dialValue);
int convertEncoderToDial(int encoderValue);
void resetDial();
boolean tryHandle();
void setMotorSpeed(int speedValue);
int readMotorCurrent();
void turnCW();
void turnCCW();
void enableMotor();
void disableMotor();
void countA();
void countB();
boolean flagDetected();
void announceSuccess();
int lookupIndentValues(int indentNumber);
void messagePause(char* message);
void checkForUserPause();
int getNextIndent(int currentDialPosition);
int averageAnalogRead(byte pinToRead);

#endif