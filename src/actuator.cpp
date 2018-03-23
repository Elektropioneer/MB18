#include <Arduino.h>
#include "actuator.h"

PacketSerial actuator_pckt;


uint8_t relay_data;
int16_t motor_data;

void onPacketActuatorReceived(const uint8_t* buffer, size_t size)
{
     	switch(buffer[0]) {
		case 'r':
			relay_data = buffer[1];
			break;
		case 'm':
			motor_data = (buffer[1] << 8) | buffer[2];
			break;
	}	     
}

void actuator_setup() {
	Serial2.begin(9600);
	actuator_pckt.setStream(&Serial2);
	actuator_pckt.setPacketHandler(&onPacketActuatorReceived);
}

void actuator_send_buffer(uint8_t* data) { 
	actuator_pckt.send(data, sizeof(data)/sizeof(data)[0]);
}

void actuator_relay_setup(uint8_t module) {
	uint8_t packet[3] = {'s', 'r', module};
	actuator_send_buffer(packet);
}

void actuator_relay_switch(uint8_t module) {
	uint8_t packet[3] = {'c', 'r', module};
	actuator_send_buffer(packet);
}

void actuator_motor_setup(int16_t achieve) {
	uint8_t packet[4] = {'s', 'm', achieve >> 8, achieve & 0xFF};
	actuator_send_buffer(packet);
}

void actuator_motor_set(int16_t achieve) {
	uint8_t packet[4] = {'c', 'm', achieve >> 8, achieve & 0xFF};
	actuator_send_buffer(packet);
}

