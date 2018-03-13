#include <Arduino.h>
#include <HardwareSerial.h>

#include "system.h"
#include "timer.h"
#include "servo.h"
#include "odometry.h"
#include "detection.h"

uint8_t execute_via_pi = 0;

void pi_com_setup() {
	Serial1.begin(9600);
}


void system_init() {

  	timer_setup();

  	odometry_setup();
  	servo_setup();
  	detection_setup();
	
	pi_com_setup();

	pinMode(PC13, OUTPUT);
}
void wait_for_rpi() {
	while(!execute_via_pi) {
		read_pi();
		digitalWrite(PC13, !digitalRead(PC13));
		delay(50);
	}

	digitalWrite(PC13, LOW);

}

static void pi_write_array(char (*data)[8]) {
	for(size_t i=0; i<8; i++) {
		Serial1.write((*data)[i]);
	}
}

static void pi_read_array(char (*data)[8]) {
	
	for(size_t i=0; i<8; i++) {
		(*data)[i] = Serial1.read();
	}

	
}

void read_pi() {
	char recv[8];
	
	if(Serial1.available() >= 8) {
		pi_read_array(&recv);
		delay(1);
		
		// switching
		switch(recv[0]) {
			case 's':
				if(recv[1] == 'e') {
					execute_via_pi = 1;	
				}
		}




		pi_write_array(&recv);
	}
}
