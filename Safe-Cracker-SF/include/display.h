
#ifndef DISPLAY_PROJECT_H
#define DISPLAY_PROJECT_H


void clearDisplay();
void showNumber(long number);
void showTime(long milliseconds);
void showCombination(byte discA, byte discB, byte discC);
void postNumber(byte number, boolean decimal, boolean inverted);

#endif