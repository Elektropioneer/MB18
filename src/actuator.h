#include <Arduino.h>
#include <PacketSerial.h>



void actuator_setup();
void actuator_send_buffer(uint8_t* data);

void actuator_relay_setup(uint8_t module);
void actuator_relay_switch(uint8_t module);


void actuator_motor_setup(int16_t achieve);
void actuator_motor_set(int16_t achieve);




