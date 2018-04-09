#include <Arduino.h>
#include "actuator.h"
#include "detection.h"


PacketSerial actuator_pckt;

uint8_t relay_data;
int16_t motor_data;
uint8_t ax_data;


void onPacketActuatorReceived(const uint8_t* buffer, size_t size)
{
	if(size >= 2) {
     		if(buffer[0] == 'r') {
			relay_data = buffer[1];
		} else if(buffer[1] == 'm') {
		//do with motor_data	
		} 

		// AX
		if(buffer[0] == 'x') {
			switch(buffer[1]) {
				case 'M':
					ax_data = buffer[2];			
					break;
			}	
		}
			
	}
}

void actuator_serial_update() {
	actuator_pckt.update();
}

void actuator_setup() {
	Serial2.begin(9600);
	actuator_pckt.setStream(&Serial2);
	actuator_pckt.setPacketHandler(&onPacketActuatorReceived);
}

void actuator_send_buffer(uint8_t* data) { 
	actuator_pckt.send(data, sizeof(data)/sizeof(data)[0]);
}

void act_ax() {
	
	// 300 255
	// x    y
	// 300 * y = x * 255
	// y = (x*255) / 300
	
	int angle = 150;
	uint8_t dec;
	dec = (uint8_t)((angle*255) / 300);



	uint8_t pkt[4] ={'x','m', 4, 127};

	actuator_send_buffer(pkt);
}



void actuator_relay_setup(uint8_t module) {
	uint8_t packet[4] = {'a','s', 'r', module};
	actuator_send_buffer(packet);
}

void actuator_relay_switch(uint8_t module) {
	uint8_t packet[4] = {'a','c', 'r', module};
	actuator_send_buffer(packet);
}

uint8_t actuator_relay_status(uint8_t module) {
	uint8_t packet[4] = {'a','S', 'r', module};
	actuator_send_buffer(packet);
	delay(50);
	return relay_data;
}


void actuator_motor_setup(int16_t achieve) {
	uint8_t uachieve = achieve >> 8;
	uint8_t lachieve = achieve & 0xFF;
	uint8_t packet[5] = {'a','s', 'm', uachieve, lachieve};
	actuator_send_buffer(packet);
}

void actuator_motor_set(int16_t achieve) {
	uint8_t uachieve = achieve >> 8;
	uint8_t lachieve = achieve & 0xFF;
	uint8_t packet[5] = {'a','c', 'm', uachieve, lachieve};
	actuator_send_buffer(packet);
}




void actuator_stepper_setup(uint8_t rpm, uint8_t module) {
	uint8_t packet[5] = {'a','s', 's', rpm, module};
	actuator_send_buffer(packet);
}

void actuator_stepper_angle(int16_t angle, uint8_t module) {
	uint8_t uangle = angle >> 8;
	uint8_t langle = angle & 0xFF;
	uint8_t packet[6] = {'a','c', 's', 'a', uangle, langle};
	actuator_send_buffer(packet);
}

void actuator_stepper_rpm(uint8_t rpm, uint8_t module) {
	uint8_t packet[6] = {'a','c', 's', 'r', rpm, module};
	actuator_send_buffer(packet);
}


// TASTERI
void switch_setup() {
	pinMode(switch_upper_pin, INPUT);
	pinMode(switch_center_pin, INPUT);
	pinMode(switch_bottom_pin, INPUT);
}

uint8_t switch_upper() {
	if(digitalRead(switch_upper_pin)) {
		return NOT_DETECTED;
	} else {
		return DETECTED;
	}
}

uint8_t switch_center() {
	if(digitalRead(switch_center_pin)) {
		return NOT_DETECTED;
	} else {
		return DETECTED;
	}
}

uint8_t switch_bottom() {
	if(digitalRead(switch_bottom_pin)) {
		return NOT_DETECTED;
	} else  {
		return DETECTED;
	}
}


void ax_move(uint8_t id, int angle) {
	uint8_t pkt[4] ={'x','m', id, (uint8_t)(angle / 4.015)};

	actuator_send_buffer(pkt);
}

void ax_move_speed(uint8_t id, int angle, int speed) {
	uint8_t pkt[5] = {'x', 's', id, (uint8_t)(angle / 4.015), (uint8_t)(speed / 4.015)};
	
	actuator_send_buffer(pkt);
}


static void lift_up(uint8_t speed) {
	uint8_t pckt[4] = {'a', 'c', 'u', speed};
	actuator_send_buffer(pckt);
}

static void lift_down(uint8_t speed) {
	uint8_t pckt[4] = {'a', 'c', 'd', speed};
	actuator_send_buffer(pckt);
}

static void lift_stop() {
	uint8_t pckt[3] = {'a', 'c', 'S'};
	actuator_send_buffer(pckt);
}

void lift_upper() {
	


	lift_up(100);

	while(1) {
		if(switch_upper() == DETECTED) {
			lift_stop();
			break;
		}	
	}	
	
	//digitalWrite(PC13, HIGH);
}

void lift_center() {
	if(switch_upper() == DETECTED) {
		lift_down(100);
	} else if(switch_bottom() == DETECTED) {
		lift_up(100);
	}


	while(1) {
		if(switch_center() == DETECTED) {
			lift_stop();
			break;
		}
	}
}

void lift_bottom() {
	lift_down(100);

	while(1) {
		if(switch_bottom() == DETECTED) {
			delay(50);
			lift_stop();
			break;
		}
	}
}

void pump_setup() {
	actuator_relay_setup(6);
}
void pump_switch() {
	actuator_relay_switch(6);
}
