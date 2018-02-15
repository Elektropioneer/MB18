#include <Arduino.h>
#include <HardwareSerial.h>
#include "servo.h"
#include "system.h"

//https://github.com/wifixcort/serial_event_interrupt/blob/master/serial_interrupt.ino

int x = 1000;

void setup() {
	
	wait_for_rpi();
	
	// system_init();
	pinMode(PC13, OUTPUT);

}

void loop() {
	digitalWrite(PC13, HIGH);
	delay(1000);
	digitalWrite(PC13, LOW);
	delay(1000);
}
