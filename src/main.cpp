#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include "system.h"
#include "odometry.h"
#include "detection.h"
#include "actuator.h"
#include "servo.h"
#include "timer.h"
#include "positions.h"
#include "display.h"

// branch mali

void setup() {

	system_init();
	delay(500);
	//wait_for_jumper();

}

int table_num = 1;
//int table_num = 2;

void loop() {
/*Serial2.println(pi_combination_read());
	delay(1000);
*/
/*
	if(get_side() == SIDE_ORANGE) { // CONNECTED TO 5V
			if(table_num == 1) {
				while(1) { orangeside_firsttable(); }
			} else if(table_num == 2) {
				while(1) { orangeside_secondtable();}
			}
	} else {												// CONNECTED TO GND
		if(table_num == 1) {
			while(1) { greenside_firsttable();    }
		} else if(table_num == 2) {
			while(1) { greenside_secondtable();   }
		}
	}
delay(10);
*/

actuator_relay_switch(5);
delay(1000);
actuator_relay_switch(5);
delay(1000);
actuator_relay_switch(6);
delay(1000);
actuator_relay_switch(6);
delay(1000);
}
