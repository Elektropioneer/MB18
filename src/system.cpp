#include <Arduino.h>
#include <HardwareSerial.h>

#include "system.h"
#include "timer.h"
#include "servo.h"
#include "odometry.h"
#include "detection.h"
#include "actuator.h"
#include "cubes.h"

uint8_t execute_via_pi = 0;

void recv_trig() {
	read_pi();
}

void pi_com_setup() {
	Serial1.begin(115200);

	//pinMode(PB12, INPUT);
	//attachInterrupt(PB12, &recv_trig, RISING);

}


void system_init() {

  timer_setup();
	delay(100);
	pi_com_setup();
	delay(100);
  odometry_setup();
	delay(100);
	detection_setup();
	delay(100);
	actuator_setup();
	delay(100);
	switch_setup();
	delay(100);
	setup_color_comb();
	/*servo_setup();
	delay(100);

	servo_three_a7(0); //right
	delay(5);
	servo_four_a6(0); // left
*/
	pinMode(PC13, OUTPUT);
}

void wait_for_rpi() {
	while(!execute_via_pi) {
		delay(10);
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
	/*char recv[8];

	if(Serial1.available() >= 8) {
		pi_read_array(&recv);

		switch(recv[0]) {
			case 's':
				if(recv[1] == 'e')
					execute_via_pi = 1;

				pi_write_array(&recv);
				break;
			case 'p':
				pi_write_array(&recv);
				break;
			case 'o':
				if(recv[1] == 'h') {
					char snd[8] = {0,0,0,0,0,0,0,0};
					snd[0] = odometry_ping();
					pi_write_array(&snd);
				} else if(recv[1] == 'd') { // default info

					char snd[8];

					odometry_update_status();

					snd[0] = odometry_get_x() >> 8;
					snd[1] = odometry_get_x() & 0xFF;
					snd[2] = odometry_get_y() >> 8;
					snd[3] = odometry_get_y() & 0xFF;
					snd[4] = odometry_get_angle() >> 8;
					snd[5] = odometry_get_angle() & 0xFF;
					snd[6] = odometry_get_state();
					snd[7] = odometry_get_current_speed();

					pi_write_array(&snd);

				} else if(recv[1] == 'a') {

					odometry_end_match();

					pi_write_array(&recv);
				}
				break;

		}


	}*/
}
