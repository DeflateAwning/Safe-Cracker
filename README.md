# Safe-Cracker
On a whim, I bought a Sentry Safe on Kijiji for cheap, without the combination. This system uses stepper motors to crack it.

## Acknowledgement
* This project is heavily based off the [sparkfunX project](https://github.com/sparkfunX/Safe_Cracker). Many of the 3D printed components are nearly a direct copy.
	* Licensing Information of the sparkfunX project: https://github.com/sparkfunX/Safe_Cracker/blob/master/LICENSE.md (MIT License)
* A 2040 Extrusion Angle Bracket was used from [Thingiverse.com](https://www.thingiverse.com/thing:3610780), user [jackw01](https://jackw01.github.io).
* A 2040 NEMA17 stepper motor mount was used from [Thingiverse.com](https://www.thingiverse.com/thing:3060289/files), user [grizzly3d](https://www.thingiverse.com/grizzly3d/about)
* Arduino [AccelStepper library](https://www.airspayce.com/mikem/arduino/AccelStepper/index.html).

## Disclaimer
* This project was built to crack open an **empty** safe that was sold to me for cheap, because the owner forgot the combination.
* As per the MIT License, I accept no responsibility for your use/adaptation of this project. Please act morally.

## 3D Printed Components
There are 3 printed components:

### Handle (SafeHandleGrip.stl)
* **Source:** Sparkfun Repository
* **Measured Dimensions:** 38mm x 118.5mm
* Dimensions match the file, using as is for now.

### Handle Pulley (NautilusPulley.stl)
* **Source:** Sparkfun Repository

### Dial (DialGrip.stl)
* **Source:** Personal OpenSCAD Design
* OD of Dial on Safe: \~79mm
* Has 12 notches around the outside
* Designed my own grip for it, supporting M5 bolts

### 2040 Aluminum Extrusion Mounts/Brackets
* Several 90-degree brackets for joining the extrusions together
	* **Source:** Thingiverse.com, see Acknowledgement
* Two motor mounts for mounting the NEMA17 steppers to the extrusions.
	* **Source:** Thingiverse.com, see Acknowledgement

## Electronics
### Devices Used
* The electronics of this system employ the [GRBL CNC Shield v3.00](https://blog.protoneer.co.nz/arduino-cnc-shield/) for the Arduino Uno (note that the associated GRBL firmware is not used). 
* 2x NEMA17 stepper motors, and one SPDT limit switch (used in NO mode)
* A 12v ATX PSU is used for power into the GRBL CNC Shield.
* A 1602 LCD screen may be used, but may not be. To be confirmed if communication will be primarily over Serial or not.
* The system will detect when unlocking was successful by one of two methods (TBD):
	1. ~Use a current sensor on the handle stepper motor (Y Axis). Easier mechnically, more difficult in electronics/firmware.~
	2. Use a limit switch SPDT switch to detect when the handle has moved. More difficult mechanically, easier in electronics/firmware. Far less creative.

### Connections to Arduino
* X Axis -> Dial
	* Dial Step Pin: D2
	* Dial Direction Pin: D5
	* Use 1/8 microstepping
	* Stepper Enable Pin: D8 (for all axes)
* Y Axis -> Handle
	* Handle Step Pin: D3
	* Handle Direction Pin: D6
	* No Microstepping (higher torque)
* X Limit Switch -> Handle Movement Detection
	* Input Pin: D9
	* Internal Pullup Resistor Used
	* Switch used in NO (normally open) mode, connected to GND (internal pullup resistor used)

## Hardware Design
* 2020 and 2040 aluminum extrusions will be used as the main frame, not because they are good, nor because they are cheap, but rather because it is May 2020 and we're all in quarantine, and it's all I have from dismantling an old CNC laser engraver.
* Various 3D printed components will be used. See breakdown of parts in 3D Printed Components section.
* Both stepper motors are **NEMA17** steppers:
	* One is used to turn the dial.
	* The other is used to pull on the handle to test when it is unlocked.

## Firmware Design
* The firmware will be losely based off the firmware provided by the sparkfunX project. It will run on an Arduino Uno, controlling the steppers through the GRBL shield (Arduino pins described in Electronics section).
* Uses the [AccelStepper library](https://www.airspayce.com/mikem/arduino/AccelStepper/index.html) to control the two stepper motors.