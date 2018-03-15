#include <Arduino.h>
#include <HardwareSerial.h>
#include "system.h"
#include "odometry.h"



void setup() {
	
	//Serial.begin(57600);
	system_init();
	//odometry_end_match();
	wait_for_rpi();
	
	//Serial.begin(57600);
	//Serial.print('K');
	
	//odometry_set_speed(100);

	odometry_rotate_for(360, NULL);
}

void loop() {
	read_pi();
}
