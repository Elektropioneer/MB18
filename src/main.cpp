#include <Arduino.h>
#include <HardwareSerial.h>
#include "servo.h"
#include "system.h"

//https://github.com/wifixcort/serial_event_interrupt/blob/master/serial_interrupt.ino

int x = 1000;

int nums[8] = {
	1,2,3,4,5,6,7,8
};

void send_data() {
	for(int i=0; i<8; i++) {
		Serial2.print(nums[i]);
	}
}

void setup() {
	
	pinMode(PC13, OUTPUT);
	
	system_init();

	wait_for_rpi();
	

	
}
void loop() {
	send_data();
	delay(500);
	
}
