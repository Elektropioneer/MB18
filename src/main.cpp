#include <Arduino.h>
#include <HardwareSerial.h>
#include "system.h"
#include "odometry.h"
#include "detection.h"
#include "actuator.h"

extern uint8_t relay_data;

void setup() {
	
	system_init();
	pinMode(PC13, OUTPUT);
	
	wait_for_rpi();

	actuator_relay_setup(6);

}

void loop() {
	actuator_relay_switch(6);
	actuator_relay_status(6);
	digitalWrite(PC13, relay_data);
	delay(500);

}
