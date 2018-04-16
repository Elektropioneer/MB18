#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include "system.h"
#include "odometry.h"
#include "detection.h"
#include "actuator.h"
#include "cubes.h"
#include "servo.h"
#include "timer.h"
#include "positions.h"
#include "display.h"

void setup() {

	system_init();
	pinMode(PC13, OUTPUT);

}

void loop() {
	/*if(get_side() == SIDE_ORANGE) { // CONNECTED TO 5V
			digitalWrite(PC13, !digitalRead(PC13));
			delay(100);
	} else {												// CONNECTED TO GND

			digitalWrite(PC13, !digitalRead(PC13));
			delay(1500);
	}*/
}
