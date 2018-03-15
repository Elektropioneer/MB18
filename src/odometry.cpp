#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdio.h>

#include "odometry.h"
#include "timer.h"

/*
 *  Structure to keep data of the position of the robot
 */
struct odometry_position position=
{
	.x     = 0,							// x coordinate
	.y     = 0,							// y coordinate
	.angle = 0,							// angle (in degrees 0-360)
	.state = IDLE,					// state
  .current_speed = 0			// the current speed (the speed it will try to reach (dependent on distance given))
};

/*
 *	Function: 	 static void odometry_send_command_print(unsigned char val)
 *  Description: sends an unsigned char to odometry board via serial
 *  Parameter:   unsigned char val - the value we will send
 */
static void odometry_send_command_print(char val) { Serial.print(val); }
static void odometry_send_8bit(char val) { Serial.print(val); }

/*
 *	Function: 	 static int odometry_get_command(void)
 *  Description: read a value from odometry board (returns an integer)
 */
static int odometry_get_command(void) { return Serial.read(); }

/*
 *	Function: 	 static void odometry_send_16bit(int16_t val)
 *  Parameter:   int16_t val - the 16bit value we will send
 *  Description: it sends 16bit value to odometry (chopping it to 2x8bit)
 */
static void odometry_send_16bit(int16_t val) {
	Serial.write((unsigned char)(val >> 8));
	Serial.write((unsigned char)(val & 0xFF));
}

/*
 *	Function: 	 void setup_odometry()
 *  Description: sets up the serial communication and sets it to 57600 baud
 */
void odometry_setup() {
  Serial.begin(57600);
}

static uint8_t odometry_wait_until_done(uint8_t (*callback)(uint32_t start_time)) {
	long long time = timer_get_sys_time();
	do
	{
		odometry_update_status();
		if(callback != NULL)
		{
			if(callback(time) == 1)
				return ODOMETRY_FAIL;
		}
	} while(position.state == MOVING || position.state == ROTATING);

	return ODOMETRY_SUCCESS;
}

/*
 *	Function: 	 void odometry_set_position(int16_t x, int16_t y, int16_t angle)
 *  Description: updates the position of the robot (force update)
 */
void odometry_set_position(int16_t x, int16_t y, int16_t angle) {

	// sending the command status
	odometry_send_command_print(odometry_command_set_position);

	odometry_send_16bit(x);
	odometry_send_16bit(y);
	odometry_send_16bit(angle);

}

/*
 *	Function: 	 void odometry_update_status(void)
 *  Description: updates the position struct with new data
 */
void odometry_update_status(void) {

	// sending the command status
  odometry_send_command_print(odometry_command_update_status);

  //Serial1.write(odometry_get_command()); //write because it converts it to ASCII...
  position.state = odometry_get_command();

  //Serial1.print((odometry_get_command() << 8) | odometry_get_command(), DEC);
  position.x = (odometry_get_command() << 8) | odometry_get_command();

  //Serial1.print((odometry_get_command() << 8) | odometry_get_command(), DEC);
  position.y = (odometry_get_command() << 8) | odometry_get_command();

  //Serial1.print((odometry_get_command() << 8) | odometry_get_command(), DEC);
  position.angle = (odometry_get_command() << 8) | odometry_get_command();

  //Serial1.print(odometry_get_command(), DEC);
  position.current_speed = odometry_get_command();

}

/*
 *	Function: 	 void odometry_set_speed(uint8_t speed)
 *  Description: updates the speed (by speed we mean the speed it will try to go with - it is dependent on the distance)
 *  Parameter:   uint8_t speed - the speed value
 */
void odometry_set_speed(uint8_t speed) {

	// sending the command status
	odometry_send_command_print(odometry_command_set_speed);

	// if its the same as last set, just skip all
	if(speed == position.current_speed) {
		return;
	}

	// send the speed
	odometry_send_8bit(speed);

	// update the status (we could have just the the position.current_speed, but its more assuring like this)
	odometry_update_status();

}

/*
 *	Function: 	 uint8_t odometry_move_forward(int16_t distance, uint8_t direction, uint8_t (*callback)(uint32_t start_time))
 *  Description: move the robot forward/backward at a determined distance
 *  Parameter:   int16_t distance - the distance in mm
 * 							 uint8_t direction - FORWARD/BACKWARD
 */
uint8_t odometry_move_forward(int16_t distance, uint8_t direction, uint8_t (*callback)(uint32_t start_time)) {

	// sending the command status
	odometry_send_command_print(odometry_command_move_forward);

	odometry_send_16bit(distance);
	odometry_send_8bit(direction);

	return odometry_wait_until_done(callback);
}

/*
 *	Function: 	 uint8_t odometry_rotate_for(uint16_t angle, uint8_t (*callback)(uint32_t start_time))
 *  Description: rotate the robot for a certain degree
 *  Parameter:   int16_t angle - the angle we will rotate it for
 */
uint8_t odometry_rotate_for(uint16_t angle, uint8_t (*callback)(uint32_t start_time)) {

	// sending the command status
	odometry_send_command_print(odometry_command_rotate_for);

	odometry_send_16bit(angle);

	return odometry_wait_until_done(callback);

}

/*
 *	Function: 	 uint8_t odometry_set_angle(uint16_t angle, uint8_t (*callback)(uint32_t start_time))
 *  Description: rotate the robot to a certain degree
 *  Parameter:   int16_t angle - the angle it will rotate to
 */
uint8_t odometry_set_angle(uint16_t angle, uint8_t (*callback)(uint32_t start_time)) {

	// sending the command status
	odometry_send_command_print(odometry_command_set_angle);

	odometry_send_16bit(angle);

	return odometry_wait_until_done(callback);
}

/*
 *	Function: 	 uint8_t odometry_goto(uint16_t x, uint16_t y, uint16_t angle, uint8_t speed, uint8_t direction, uint8_t (*callback)(uint32_t start_time))
 *  Description: sends the robot into a specific coordinate in a direction at a defined speed
 *  Parameter:   self explanatory
 */
uint8_t odometry_goto(uint16_t x, uint16_t y, uint16_t angle, uint8_t speed, uint8_t direction, uint8_t (*callback)(uint32_t start_time)) {

	// sending the command status
	odometry_send_command_print(odometry_command_goto);

	odometry_send_16bit(x);
	odometry_send_16bit(y);
	odometry_send_16bit(angle);

	odometry_send_8bit(speed);
	odometry_send_8bit(direction);

	return odometry_wait_until_done(callback);
}

/*
 *	Function: 	 uint8_t odometry_stop(uint8_t (*callback)(uint32_t start_time))
 *  Description: stop the robot
 */
uint8_t odometry_stop(uint8_t (*callback)(uint32_t start_time)) {

	/*
	TODO: add multiple version (ABS or without) nad with parameters (speed dependent)
	*/

	// sending the command status
	odometry_send_command_print(odometry_command_stop);

	return odometry_wait_until_done(callback);
}

/*
 *	Function: 	 void odometry_end_match(void)
 *  Description: blocking all wheels, stopping, turning off pwm and staying in while(1)
 */
void odometry_end_match(void) {

	// sending the command status
	odometry_send_command_print(odometry_command_end_match);

}

/*
 *  Description: return all data found in the struct
 */
int16_t odometry_get_x(void) { return position.x; }
int16_t odometry_get_y(void) { return position.y; }
int16_t odometry_get_angle(void) { return position.angle; }
int8_t odometry_get_state(void) { return position.state; }
int8_t odometry_get_current_speed(void) { return position.current_speed; }
