
// LICENSE INFORMATION


#include <AccelStepper.h>

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

// this needs to be set correctly/tested
#define stepsPerRev_dial (200*8) // 1/8 microstepping
#define stepsPerRev_handle (200*1) // no microstepping (higher torque)

// Construct the Stepper Controllers
AccelStepper dialStepper(AccelStepper::DRIVER, PIN_DIAL_STEP, PIN_DIAL_DIR);
AccelStepper handleStepper(AccelStepper::DRIVER, PIN_HANDLE_STEP, PIN_HANDLE_DIR);

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
	dialStepper.setMaxSpeed(stepsPerRev_dial*3); // in steps/second, set to 3 rev/second
	dialStepper.setAcceleration(100.0);
	dialStepper.setSpeed(dialStepper.maxSpeed() - 1);

	handleStepper.setMaxSpeed(200.0);
	handleStepper.setAcceleration(100.0);
	handleStepper.setSpeed(handleStepper.maxSpeed() - 1);
}


void doHardwareTest() {
	Serial.println("Hardware test beginning.");

	// Test that motor enable works, motors receiving power
	Serial.println("Motors being enabled. Ensure they lock. Waiting 2 seconds.");
	setStepperEnable(true);
	delay(2000);
	Serial.println();
	
	// Test that the dial driver works
	Serial.println("The dial will spin two full circles clockwise, wait a second, then spin back.");
	dialStepper.runToNewPosition(stepsPerRev_dial * 2);
	Serial.println("\t2 circles done.");
	delay(1000);
	dialStepper.runToNewPosition(0);
	Serial.println("\tSpin back done.");
	delay(1000);
	Serial.println();

	// Test that the input switch works
	Serial.println("The input switch will be tested 10 times in 10 seconds. Try triggering it and seeing results.");
	for (int i = 0; i < 10; i++) {
		if (checkSafeOpenHandle()) {
			Serial.print("Open | ");
		}
		else {
			Serial.print("Closed | ");
		}
	}
	Serial.println("\n");

	// Test that the safe opening mechanism (handle) works
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
		Serial.print("\tHandle Open Attempt took "); Serial.print(millis()-startTime); Serial.println("ms");
	}
	Serial.println();
}

/**
Instructs the user to set the dial stepper to a known state, and to set the handle tension. Waits for the switch to trigger to begin.
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
Checks if the safe can be unlocked right now. Spins the handle for a while, and then rests if no success.
This function intentionally skips steps in an effort to pull hard on the handle.
@return True if the safe can be unlocked right now, false if not
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
Reads the safe open switch. 
@return true if it is triggered (safe open), false if not triggered (safe still closed)
*/
bool readSafeOpen() {
	// digitalRead: true = untriggered = safe closed
	return (! digitalRead(PIN_OPEN_SENSOR));
}



/**
Sets the stepper motors' enable to ON or OFF, deciding whether to provide power to the steppers.
@param state true to turn on, false to turn off
*/
void setStepperEnable(bool state) {
	digitalWrite(PIN_STEPPER_ENABLE, state);
}






void loop() {
	// This part should never be reached.
	Serial.println("Reached loop part, weird.");
	delay(1000);
}