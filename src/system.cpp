#include <Arduino.h>
#include <HardwareSerial.h>

#include "system.h"
#include "timer.h"
#include "servo.h"
#include "odometry.h"
#include "detection.h"
#include "actuator.h"
#include "display.h"

uint8_t execute_via_pi = 0;				// status for execute via pi (not used anymore)
uint8_t execute_via_jumper = 0;	  // status for execute via jumper

uint8_t check_camera = 1;
uint8_t camera_combination = 0;

void set_checkcamera(uint8_t status) {
	check_camera = status;
}

uint8_t get_camera_combination() {
	return camera_combination;
}

// recv trigure for the pi
static void recv_trig() { read_pi(); }

// when the jumper calls the interrupt it changes to execute via jumper
void jumper_trig() { execute_via_jumper = 1; }

void pi_com_setup() {
	Serial1.begin(115200);

/*	pinMode(PB12, INPUT);
	attachInterrupt(PB12, &recv_trig, RISING);
*/
}


// setup the jumper and the side pins
static void setup_jump_side() {
	pinMode(PIN_JUMPER, INPUT);
	pinMode(PIN_SIDE, INPUT);

	// attaching interrupt function
	//attachInterrupt(PIN_JUMPER, &jumper_trig, CHANGE);
}

void system_init() {

  timer_setup();				// timer
	delay(100);
	pi_com_setup();				// pi com
	delay(100);
  odometry_setup();			// odometry
	delay(100);
	detection_setup();		// detection
	delay(100);
	actuator_setup();			// actuator
	delay(100);
	setup_jump_side();		// jumper and side
	delay(100);
	display_setup();
	delay(100);         // display
  franken_setup();
	delay(100);

	pinMode(PC13, OUTPUT);
}

// while execute via pi is not set
void wait_for_rpi() { while(!execute_via_pi) {delay(10); } }

// while execute_via_jumper is not sets
void wait_for_jumper() { while(!execute_via_jumper) {delay(5);} }

// read the side switch and returns the side
uint8_t get_side() {
	if(digitalRead(PIN_SIDE)) {
		return SIDE_GREEN;
	} else {
		return SIDE_ORANGE;
	}
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
	Serial1.print('c');
	delay(50);
	while(Serial1.available() == 0);
	Serial2.write(Serial1.read());
}

char pi_combination_read() {
	Serial1.print('c');
	delay(50);
	while(Serial1.available() == 0);
	return Serial1.read();
}
