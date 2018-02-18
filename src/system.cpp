#include <Arduino.h>
#include <HardwareSerial.h>

#include "system.h"
#include "timer.h"
#include "servo.h"
#include "odometry.h"
#include "detection.h"


void pi_com_setup() {
	Serial2.begin(9600);
}


void system_init() {

  	timer_setup();

  	odometry_setup();
  	servo_setup();
  	detection_setup();
	
	pi_com_setup();
}
void wait_for_rpi() {

	while(Serial2.available() == 0) {
		if(Serial2.read() == 'e') {
			break;
		}
		digitalWrite(PC13, !digitalRead(PC13));
		delay(100);
	}

}
