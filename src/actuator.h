#include <Arduino.h>
#include <PacketSerial.h>

void actuator_setup();
void actuator_send_buffer(uint8_t* data);
void actuator_serial_update();

void stepper_2_setup();
void stepper_2_one();
void stepper_2_two();

void actuator_relay_setup(uint8_t module);
void actuator_relay_switch(uint8_t module);
uint8_t  actuator_relay_status(uint8_t module);

void franken_setup();
void franken_up(uint8_t speed);
void franken_stop();
void franken_down(uint8_t speed);
/*
void pump_setup();
void pump_switch();

#define switch_upper_pin PB9
#define switch_center_pin PB8
#define switch_bottom_pin PB15
void actuator_motor_setup(int16_t achieve);
void actuator_motor_set(int16_t achieve);

void actuator_stepper_setup(uint8_t rpm, uint8_t module);
void actuator_stepper_angle(int16_t angle, uint8_t module);
void actuator_stepper_rpm(uint8_t rpm, uint8_t module);

void switch_setup();
uint8_t switch_upper();
uint8_t switch_center();
uint8_t switch_bottom();

void ax_move(uint8_t id, int angle);
void ax_move_speed(uint8_t id, int angle, int speed);
*/
