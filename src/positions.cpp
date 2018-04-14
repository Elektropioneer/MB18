#include <Arduino.h>
#include "positions.h"
#include "odometry.h"
#include "detection.h"

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

const struct odometry_position green_starting  = {0, 0, 180};
const struct odometry_position orange_starting = {0, 0, 180};
const struct goto_fields green_tacticone[] = {
	{{300, 0}, 50, FORWARD, front, NULL}
};

const struct goto_fields orange_tacticone[] = {
	{{300, 0}, 50, FORWARD, front, NULL}			// position 1
};

// setup if collision so the return value
static uint8_t robot_movetoposition_green_tacticone(uint8_t num) {
	return odometry_goto(green_tacticone[num].position.x,
								green_tacticone[num].position.y,
								green_tacticone[num].speed,
								green_tacticone[num].direction,
								green_tacticone[num].callback);

}


static uint8_t robot_movetoposition_orange_tacticone(uint8_t num) {
	return odometry_goto(orange_tacticone[num].position.x,
								orange_tacticone[num].position.y,
								orange_tacticone[num].speed,
								orange_tacticone[num].direction,
								orange_tacticone[num].callback);

}

uint8_t status, active_state;
int g_current, g_next = 0;
int o_current, o_next = 0;

void greenside() {

	active_state = TACTIC_ONE;

	odometry_set_position(green_starting.x, green_starting.y, green_starting.angle);

	delay(200);

	while(1) {

		switch(active_state) {
			case COLLISION:

				delay(200);

				while(green_tacticone[g_current].callback() == 1)
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
				for(g_current=g_next; g_current < int((sizeof(green_tacticone)/sizeof(green_tacticone)[0])); g_current++) {


					Serial1.println("Going to: ");
					Serial1.print(g_current);

					status = robot_movetoposition_green_tacticone(g_current);

					if(status == ODOMETRY_FAIL) {
						active_state = COLLISION;
						break;
					}

					if(green_tacticone[g_current].callback_end != NULL)
						green_tacticone[g_current].callback_end();

					if(g_current == (sizeof(green_tacticone)/sizeof(green_tacticone)[0]) - 1) {
						odometry_end_match();
						while(1);
					}

				}
				break;
		}
	}
}

void orangeside() {

	active_state = TACTIC_ONE;

	odometry_set_position(orange_starting.x, orange_starting.y, orange_starting.angle);

	delay(200);

	while(1) {

		switch(active_state) {
			case COLLISION:
				delay(200);

				while(orange_tacticone[o_current].callback() == 1)
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
				for(o_current=o_next; o_current < int((sizeof(orange_tacticone)/sizeof(orange_tacticone)[0])); o_current++) {


					Serial1.println("Going to: ");
					Serial1.print(o_current);

					status = robot_movetoposition_orange_tacticone(o_current);

					if(status == ODOMETRY_FAIL) {
						active_state = COLLISION;
						break;
					}

					if(orange_tacticone[o_current].callback_end != NULL)
						orange_tacticone[o_current].callback_end();

					if(o_current == (sizeof(orange_tacticone)/sizeof(orange_tacticone)[0]) - 1) {
						odometry_end_match();
						while(1);
					}

				}
				break;
		}
	}
}
