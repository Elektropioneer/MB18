#include <Arduino.h>
#include "positions.h"
#include "odometry.h"
#include "detection.h"
#include "actuator.h"

struct goto_fields
{
	struct odometry_position position;
	uint8_t speed;
	uint8_t direction;
	uint8_t	(*callback)();
	uint8_t (*callback_end)();
};

uint8_t wait() {
	delay(200);
	return 0;
}

static uint8_t front() {
	if(detection_front() == DETECTED) {
		odometry_stop(HARD_STOP);
		return 1;
	} else {
		return 0;
	}
}

static uint8_t back() {
	if(detection_back() == DETECTED) {
		odometry_stop(HARD_STOP);
		return 1;
	} else {
		return 0;
	}
}


/******************************************************************
														FIRST TABLE
*******************************************************************/

const struct odometry_position green_starting_first  = {0, 0, 180};
const struct odometry_position orange_starting_first = {0, 0, 180};

const struct goto_fields green_tacticone_first[] = {
	{{300, 0}, 50, FORWARD, front, NULL}
};

const struct goto_fields orange_tacticone_first[] = {
	{{300, 0}, 50, FORWARD, front, NULL}
};

/*******************************************************************
														SECOND TABLE
*******************************************************************/

const struct odometry_position green_starting_second  = {0, 0, 180};
const struct odometry_position orange_starting_second = {0, 0, 180};

const struct goto_fields green_tacticone_second[] = {
	{{300, 0}, 50, FORWARD, front, NULL}
};

const struct goto_fields orange_tacticone_second[] = {
	{{300, 0}, 50, FORWARD, front, NULL}
};

/*******************************************************************/

static uint8_t robot_movetoposition_green_tacticone_first(uint8_t num) {
	return odometry_goto(green_tacticone_first[num].position.x,
								green_tacticone_first[num].position.y,
								green_tacticone_first[num].speed,
								green_tacticone_first[num].direction,
								green_tacticone_first[num].callback);

}

static uint8_t robot_movetoposition_green_tacticone_second(uint8_t num) {
	return odometry_goto(green_tacticone_second[num].position.x,
								green_tacticone_second[num].position.y,
								green_tacticone_second[num].speed,
								green_tacticone_second[num].direction,
								green_tacticone_second[num].callback);

}


static uint8_t robot_movetoposition_orange_tacticone_first(uint8_t num) {
	return odometry_goto(orange_tacticone_first[num].position.x,
								orange_tacticone_first[num].position.y,
								orange_tacticone_first[num].speed,
								orange_tacticone_first[num].direction,
								orange_tacticone_first[num].callback);

}

static uint8_t robot_movetoposition_orange_tacticone_second(uint8_t num) {
	return odometry_goto(orange_tacticone_second[num].position.x,
								orange_tacticone_second[num].position.y,
								orange_tacticone_second[num].speed,
								orange_tacticone_second[num].direction,
								orange_tacticone_second[num].callback);

}

uint8_t status, active_state;
int g_current, g_next = 0;
int o_current, o_next = 0;

void greenside_firsttable() {

	active_state = TACTIC_ONE;

	odometry_set_position(green_starting_first.x, green_starting_first.y, green_starting_first.angle);

	delay(200);

	while(1) {

		switch(active_state) {
			case COLLISION:

				delay(200);

				while(green_tacticone_first[g_current].callback() == 1)
					delay(10);

				active_state = TACTIC_ONE;
				g_next = g_current;

				delay(1000);

				break;

		 /* case STUCK:
				delay(1000);
				active_state = TACTIC_ONE;
				g_next = g_current;
				break;*/

			case TACTIC_ONE:
				for(g_current=g_next; g_current < int((sizeof(green_tacticone_first)/sizeof(green_tacticone_first)[0])); g_current++) {


					/*Serial1.println("Going to: ");
					Serial1.print(g_current);*/

					status = robot_movetoposition_green_tacticone_first(g_current);

					if(status == ODOMETRY_FAIL) {
						active_state = COLLISION;
						break;
					}

					if(green_tacticone_first[g_current].callback_end != NULL)
						green_tacticone_first[g_current].callback_end();

					if(g_current == (sizeof(green_tacticone_first)/sizeof(green_tacticone_first)[0]) - 1) {
						odometry_end_match();
						while(1);
					}

				}
				break;
		}
	}
}

void orangeside_firsttable() {

	active_state = TACTIC_ONE;

	odometry_set_position(orange_starting_first.x, orange_starting_first.y, orange_starting_first.angle);

	delay(200);

	while(1) {

		switch(active_state) {
			case COLLISION:
				delay(200);

				while(orange_tacticone_first[o_current].callback() == 1)
					delay(10);

				active_state = TACTIC_ONE;
				o_next = o_current;

				delay(1000);

				break;

		 /* case STUCK:
				delay(1000);
				active_state = TACTIC_ONE;
				g_next = g_current;
				break;*/

			case TACTIC_ONE:
				for(o_current=o_next; o_current < int((sizeof(orange_tacticone_first)/sizeof(orange_tacticone_first)[0])); o_current++) {


					/*Serial1.println("Going to: ");
					Serial1.print(o_current);*/

					status = robot_movetoposition_orange_tacticone_first(o_current);

					if(status == ODOMETRY_FAIL) {
						active_state = COLLISION;
						break;
					}

					if(orange_tacticone_first[o_current].callback_end != NULL)
						orange_tacticone_first[o_current].callback_end();

					if(o_current == (sizeof(orange_tacticone_first)/sizeof(orange_tacticone_first)[0]) - 1) {
						odometry_end_match();
						while(1);
					}

				}
				break;
		}
	}
}

void greenside_secondtable() {

	active_state = TACTIC_ONE;

	odometry_set_position(green_starting_second.x, green_starting_second.y, green_starting_second.angle);

	delay(200);

	while(1) {

		switch(active_state) {
			case COLLISION:

				delay(200);

				while(green_tacticone_second[g_current].callback() == 1)
					delay(10);

				active_state = TACTIC_ONE;
				g_next = g_current;

				delay(1000);

				break;

		 /* case STUCK:
				delay(1000);
				active_state = TACTIC_ONE;
				g_next = g_current;
				break;*/

			case TACTIC_ONE:
				for(g_current=g_next; g_current < int((sizeof(green_tacticone_second)/sizeof(green_tacticone_second)[0])); g_current++) {


					/*Serial1.println("Going to: ");
					Serial1.print(g_current);*/

					status = robot_movetoposition_green_tacticone_second(g_current);

					if(status == ODOMETRY_FAIL) {
						active_state = COLLISION;
						break;
					}

					if(green_tacticone_second[g_current].callback_end != NULL)
						green_tacticone_second[g_current].callback_end();

					if(g_current == (sizeof(green_tacticone_second)/sizeof(green_tacticone_second)[0]) - 1) {
						odometry_end_match();
						while(1);
					}

				}
				break;
		}
	}
}

void orangeside_secondtable() {

	active_state = TACTIC_ONE;

	odometry_set_position(orange_starting_second.x, orange_starting_second.y, orange_starting_second.angle);

	delay(200);

	while(1) {

		switch(active_state) {
			case COLLISION:
				delay(200);

				while(orange_tacticone_second[o_current].callback() == 1)
					delay(10);

				active_state = TACTIC_ONE;
				o_next = o_current;

				delay(1000);

				break;

		 /* case STUCK:
				delay(1000);
				active_state = TACTIC_ONE;
				g_next = g_current;
				break;*/

			case TACTIC_ONE:
				for(o_current=o_next; o_current < int((sizeof(orange_tacticone_second)/sizeof(orange_tacticone_second)[0])); o_current++) {


					/*Serial1.println("Going to: ");
					Serial1.print(o_current);*/

					status = robot_movetoposition_orange_tacticone_second(o_current);

					if(status == ODOMETRY_FAIL) {
						active_state = COLLISION;
						break;
					}

					if(orange_tacticone_second[o_current].callback_end != NULL)
						orange_tacticone_second[o_current].callback_end();

					if(o_current == (sizeof(orange_tacticone_second)/sizeof(orange_tacticone_second)[0]) - 1) {
						odometry_end_match();
						while(1);
					}

				}
				break;
		}
	}
}
