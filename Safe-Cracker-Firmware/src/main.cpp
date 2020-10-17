


#include "main.h"


// Construct the Stepper Controllers
AccelStepper dialStepper(AccelStepper::DRIVER, PIN_DIAL_STEP, PIN_DIAL_DIR);
AccelStepper handleStepper(AccelStepper::DRIVER, PIN_HANDLE_STEP, PIN_HANDLE_DIR);

int currentPosDigit = 0;


void setup() {
	// Begin serial communication
	Serial.begin(115200);
	Serial.println("***** Safe-Cracker Starting *****");

	// Set the stepper config, pinmodes
	setupSteppers();

	// Test functionality of each system component/control function
	doHardwareTest();

	// Instruct the user to set the safe to a known state
	doSetupInstructions();
}

/**
Setup the stepper motor configuration and pin modes. These values may need tuning.
*/
void setupSteppers() {
	// Set Pin Modes
	pinMode(PIN_DIAL_STEP, OUTPUT);
	pinMode(PIN_DIAL_DIR, OUTPUT);
	pinMode(PIN_HANDLE_STEP, OUTPUT);
	pinMode(PIN_HANDLE_DIR, OUTPUT);
	pinMode(PIN_STEPPER_ENABLE, OUTPUT);
	pinMode(PIN_OPEN_SENSOR, INPUT_PULLUP);

	// Set stepper settings
	dialStepper.setMaxSpeed(maxStepsPerSec_dial); // in steps/second, set to 3 rev/second
	dialStepper.setAcceleration(maxStepsPerSec_dial*4);
	dialStepper.setSpeed(dialStepper.maxSpeed() - 1);

	handleStepper.setMaxSpeed(stepsPerRev_handle * 0.5);
	handleStepper.setAcceleration(1000.0);
	handleStepper.setSpeed(handleStepper.maxSpeed() - 1);
}


void doHardwareTest() {
	bool enableTest_spinToDigit = true;
	bool enableTest_spinFullCircles = true;
	bool enableTest_printInputSwitch = true;
	bool enableTest_testHandle = false;

	Serial.println("Hardware test beginning.");

	// Test that motor enable works, motors receiving power
	Serial.println("Motors being disabled (3s) then enabled (2s). Ensure they lock.");
	setStepperEnable(false);
	delay(3000);
	setStepperEnable(true);
	delay(2000);
	Serial.println();

	
	// Test that the dial driver works
	if (enableTest_spinFullCircles) {
		Serial.println("The dial will spin a full circle clockwise, wait a second, then spin back CCW.");
		for (int i = 0; i < 1; i++) { // change to i < 2 to do twice
			//dialStepper.runToNewPosition(stepsPerRev_dial * 2); // original, use absolute position
			dialStepper.move(CW * stepsPerRev_dial);
			runStepperUntilDone(dialStepper);

			Serial.println("\t2 circles CW done.");
			delay(1000);
			
			//dialStepper.runToNewPosition(0); // original, use absolute position
			dialStepper.move(CCW * stepsPerRev_dial);
			runStepperUntilDone(dialStepper);

			Serial.println("\tSpin back CCW done.");
			delay(1000);
			Serial.println();
		}
	}


	// Test that the dial spinToDigit function works
	if (enableTest_spinToDigit) {
		Serial.println("Spinning to each digit, CW in 10s.");
		for (int digit = 10; digit < 50; digit += 10) {
			Serial.print("Spin to "); Serial.print(digit); Serial.print("CCW (short way) ...");
			spinToDigit(0, digit, CCW);
			Serial.println("Done.");

			delay(2000);
		}

		Serial.println("Spinning to each digit, CW in 10s.");
		for (int digit = 10; digit < 50; digit += 10) {
			Serial.print("Spin to "); Serial.print(digit); Serial.print("CW (long way) ...");
			spinToDigit(0, digit, CW);
			Serial.println("Done.");

			delay(2000);
		}
	}
	
	


	// Test that the input switch works
	if (enableTest_printInputSwitch) {
		Serial.println("The input switch will be tested 10 times in 10 seconds. Try triggering it and seeing results.");
		for (int i = 0; i < 10; i++) {
			if (readSafeOpen()) {
				Serial.print("Safe Unlocked | ");
			}
			else {
				Serial.print("Safe Locked | ");
			}
			delay(1000);
		}
		Serial.println("\n");
	}

	// Test that the safe opening mechanism (handle) works
	if (enableTest_testHandle) {
		Serial.println("The handle opener will now be tested 3 times.");
		Serial.println("Let it fail once, then pretend it opened and trigger the switch once.");
		for (int i = 0; i < 3; i++) {
			long startTime = millis();
			if (checkSafeOpenHandle()) {
				Serial.println("\tSafe handle open. Safe unlocked.");
			}
			else {
				Serial.println("\tSafe handle not opened. Safe still locked.");
			}
			Serial.print("\tHandle Open Attempt took "); Serial.print(millis()-startTime); Serial.println("ms, waiting 3s now.");
			delay(3000);
		}
		Serial.println();
	}


}

/**
 * Instructs the user to set the dial stepper to a known state, and to set the handle tension. Waits for the switch to trigger to begin.
 */
void doSetupInstructions() {
	// disable steppers
	setStepperEnable(false);

	Serial.println("The steppers are now disabled. Turn the dial to face to zero, and ensure the handle trigger is setup. Then, press the switch.");
	while (! readSafeOpen()) {} // wait until button is pressed
	Serial.println("Safe dial position is now set to 0.");
	delay(2000); // debounce the button, in case they're holding it

	// enable steppers
	setStepperEnable(true);
}

/**
 * Checks if the safe can be unlocked right now. Spins the handle for a while, and then rests if no success.
 * This function intentionally skips steps in an effort to pull hard on the handle.
 * @return True if the safe can be unlocked right now, false if not
 */
bool checkSafeOpenHandle() {
	// Try to spin a half circle
	handleStepper.runToNewPosition(stepsPerRev_handle/2);

	// "zero" the stepper after it skipped some steps
	handleStepper.setCurrentPosition(0);

	if (readSafeOpen()) {
		// sensor has been triggered, safe is open
		return true;
	}

	// Move back just a little (1/30 of a rev. = 12 degrees)
	handleStepper.runToNewPosition(-stepsPerRev_handle/30);

	return false;
}

/**
 * Reads the safe open switch. 
 * @return true if it is triggered (safe open), false if not triggered (safe still closed)
 */
bool readSafeOpen() {
	return (! digitalRead(PIN_OPEN_SENSOR));
}



/**
 * Sets the stepper motors' enable to ON or OFF, deciding whether to provide power to the steppers.
 * @param state true to turn on, false to turn off
 */
void setStepperEnable(bool state) {
	digitalWrite(PIN_STEPPER_ENABLE, !state);
}

/**
 * Spin to a digit, with a certain number of spins in the middle.
 * @param fullSpinCount the number of full spins to do before going to the digit
 * @param targetDigit the digit to spin to
 * @param dir CW (1) or CCW (-1) macros
 */
void spinToDigit(int fullSpinCount, int targetDigit, int dir) {
	// Original Source: https://github.com/UMDIEEE/safecracker/blob/78b7601d9ec6db11d3e32d1c54b2aad3b520fb37/software/safecracker.ino#L33
	
	/**
	 * Number of digits to move in the positive direction (CW).
	 */
	int delta;

	int numberOfDigitsToMove = targetDigit - currentPosDigit; // factored out of expression from source

	if (numberOfDigitsToMove >= 0) {
		// moving to a digit "on the right", direct path is to spin CCW

		if (dir == CCW) {
			delta = numberOfDigitsToMove * dir;
		}
		else if (dir == CW) {
			delta = (NUM_DIGITS - abs(numberOfDigitsToMove)) * dir;
		}
	}

	else {
		// moving to a digit "on the left", direct path is to spin CW
		if (dir == CW) {
			delta = numberOfDigitsToMove * dir;
		}
		else if (dir == CCW) {
			delta = (NUM_DIGITS - abs(numberOfDigitsToMove)) * dir;
		}

	}

	/*
	if (dir > 0) {
		delta = (numberOfDigitsToMove >= 0) ? numberOfDigitsToMove : numberOfDigitsToMove + NUM_DIGITS;
	}
	else {
		delta = (numberOfDigitsToMove <= 0) ? numberOfDigitsToMove : numberOfDigitsToMove - NUM_DIGITS;
	}
	*/

	//dialStepper.move(delta*stepsPerDigit + dir*fullSpinCount*NUM_DIGITS*stepsPerDigit);
	dialStepper.move(dir*fullSpinCount*stepsPerRev_dial + delta*stepsPerDigit);
	Serial.print("Moving "); Serial.print(delta); Serial.print(" digits, plus "); Serial.print(fullSpinCount); Serial.print(" full spins...");
	
	runStepperUntilDone(dialStepper);

	Serial.print("Moved to digit "); Serial.print(targetDigit); Serial.print(".");
	Serial.println();

	// Store the current digit
	currentPosDigit = targetDigit;
}

/**
 * Runs the stepper motor until at the desired position. Use after calling @code{stepperMotor.move(newPosition)}, for example.
 */
void runStepperUntilDone(AccelStepper targetStepperMotor) {
	while(targetStepperMotor.distanceToGo() != 0) {
		targetStepperMotor.run();
	}
}

/**
 * Turns the dial to a specific position (a certain number), out of 100 possible numbers.
 * Updates currentPosDigit global.
 * @param dir CW or CCW macro constant
*/
void dial_turnToPosition(int targetDigit, int dir) {
	//int numOfDigitsToMove = targetDigit - currentPosDigit;



}





void loop() {
	// This part should never be reached.
	Serial.println("Reached loop part, weird.");
	delay(1000);
}
