#include <Arduino.h>

struct odometry_position
{
	int16_t x;
	int16_t y;
	int16_t angle;
	int8_t  state;
	int8_t current_speed;
};

enum odometry_states
{
	IDLE = 'I',
	MOVING = 'M',
	ROTATING = 'R',
	STUCK = 'S',
	ERROR = 'E'
};

#define FORWARD													1
#define BACKWARD												0

#define ODOMETRY_SUCCESS								1
#define ODOMETRY_FAIL										0

#define odometry_command_set_position  'I'
#define odometry_command_update_status 'P'
#define odometry_command_set_speed		 'V'
#define odometry_command_move_forward  'D'
#define odometry_command_rotate_for    'T'
#define odometry_command_set_angle     'A'
#define odometry_command_goto					 'G'
#define odometry_command_stop					 'S'
#define odometry_command_end_match		 'K'

void odometry_setup();

void odometry_set_position(int16_t x, int16_t y, int16_t angle);
void odometry_update_status(void);
void odometry_set_speed(uint8_t speed);
uint8_t odometry_move_forward(int16_t distance, uint8_t direction, uint8_t (*callback)(uint32_t start_time));
uint8_t odometry_rotate_for(uint16_t angle, uint8_t (*callback)(uint32_t start_time));
uint8_t odometry_set_angle(uint16_t angle, uint8_t (*callback)(uint32_t start_time));
uint8_t odometry_goto(uint16_t x, uint16_t y, uint16_t angle, uint8_t speed, uint8_t direction, uint8_t (*callback)(uint32_t start_time));
uint8_t odometry_stop(uint8_t (*callback)(uint32_t start_time));
void odometry_end_match(void);
int16_t odometry_get_x(void);
int16_t odometry_get_y(void);
int16_t odometry_get_angle(void);
int8_t odometry_get_state(void);
int8_t odometry_get_current_speed(void);