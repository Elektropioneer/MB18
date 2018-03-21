#include <Arduino.h>
#include <HardwareSerial.h>
#include "system.h"
#include "odometry.h"
#include "detection.h"

void setup() {
	
	system_init();
	pinMode(PC13, OUTPUT);
	
	wait_for_rpi();
}

void loop() {
	digitalWrite(PC13, detection_get_pin(CS_BC_PIN));
	delay(100);
}
