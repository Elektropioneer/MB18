#include <Arduino.h>
#include "servo.h"

#define servo_lower_rate  2096
#define servo_upper_rate  8096

#define servo_first_pin   PB1
#define servo_second_pin  PB0
#define servo_third_pin   PA7
#define servo_fourth_pin  PA6

// all the pins are on timer3
HardwareTimer servo(3);

/*
 *  Function:    void servo_setup(void)
 *  Description: setup all the pins and registers
 */
void servo_setup(void) {

  // http://librambutan.readthedocs.io/en/latest/pwm.html#pwm

  pinMode(servo_first_pin,  PWM);
  pinMode(servo_second_pin, PWM);
  pinMode(servo_third_pin,  PWM);
  pinMode(servo_fourth_pin, PWM);

  // we need the frequency for the servo
  servo.setPrescaleFactor(21);
}

/*
 *  Function:    static void servo_write(uint8_t pin, uint8_t angle)
 *  Description: write to pin with a specific angle
 */
static void servo_write(uint8_t pin, uint8_t angle) { pwmWrite(pin, map(angle, 0, 180, servo_lower_rate, servo_upper_rate)); }


/*
 * Function: servo_x_x(uint8_t angle)
 * Description: write to the specific servo (helper function)
 */
void servo_one_b1(uint8_t angle)   { servo_write(servo_first_pin,  angle); }
void servo_two_b0(uint8_t angle)   { servo_write(servo_second_pin, angle); }
void servo_three_a7(uint8_t angle) { servo_write(servo_third_pin,  angle); }
void servo_four_a6(uint8_t angle) { servo_write(servo_fourth_pin, angle); }


void left_servo_single() {
	servo_four_a6(63);
}
void left_servo_single_pull() {
	servo_four_a6(58);
}

void left_servo_double() {
	servo_four_a6(13);
}
