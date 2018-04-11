#include <Arduino.h>
#include <HardwareSerial.h>
#include "system.h"
#include "odometry.h"
#include "detection.h"
#include "actuator.h"
#include "cubes.h"
#include "servo.h"
#include "timer.h"
#include "positions.h"
/*
uint8_t check() {
	if(detection_back() == DETECTED) {
		Serial1.print("Detecting...");
		return 1;
	} else {
		Serial1.print("Not detecting...\n");
		return 0;
	}
}*/

void setup() {

	system_init();
	pinMode(PC13, OUTPUT);

	/*
	pump_setup();
	//left_servo_single_pull()
	delay(1000);
	lift_center();
	delay(500);
	cube_yellow();
	delay(500);
	pump_switch();
	delay(50);
	lift_bottom();
	delay(1000);
	lift_center();
	delay(500);
	cube_left_in();
	delay(500);
	pump_switch();
	delay(500);
	//left_servo_single();
	delay(2000);

	cube_blue();
	delay(1000);
	pump_switch();
	delay(50);
	lift_bottom();
	delay(1000);
	lift_upper();
	delay(500);
	cube_left_in();
	delay(2000);
	pump_switch();
	//left_servo_single_pull();
	delay(500);
	//left_servo_single();
*/

	/*odometry_goto(100, 0, 20, 1, NULL);

	odometry_goto(0, 0, 20, 0, NULL);*/
	greenside();

}


void loop() {
}
