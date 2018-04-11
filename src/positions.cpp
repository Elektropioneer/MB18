#include <Arduino.h>
#include "positions.h"
#include "odometry.h"
/*
struct goto_fields
{
	struct odometry_position position;
	uint8_t speed;
	uint8_t direction;
	uint8_t	(*callback)(uint32_t start_time);
	uint8_t (*callback_end)();
};

const struct goto_fields green_tacticone[] = {
	{{100, 100}, 50, FORWARD, NULL, NULL}			// position 1
};

const struct goto_fields orange_tacticone[] = {
	{{100, 100}, 50, FORWARD, NULL, NULL}			// position 1
};

// setup if collision so the return value
static void robot_movetoposition_green_tacticone(uint8_t num) {
	odometry_goto(green_tacticone[num].position.x,
								green_tacticone[num].position.y,
								0, // not sending this one
								green_tacticone[num].speed,
								green_tacticone[num].direction,
								green_tacticone[num].callback);
	green_tacticone[num].callback_end();
}


static void robot_movetoposition_orange_tacticone(uint8_t num) {
	odometry_goto(orange_tacticone[num].position.x,
								orange_tacticone[num].position.y,
								0, // not sending this one
								orange_tacticone[num].speed,
								orange_tacticone[num].direction,
								orange_tacticone[num].callback);
	orange_tacticone[num].callback_end();
}


void greenside() {
	for(int i=0; i<sizeof(sizeof(green_tacticone)/sizeof(green_tacticone)[0]);i++) {
		robot_movetoposition_green_tacticone(i);
	}
}

void orangeside() {
	for(int i=0; i<sizeof(sizeof(orange_tacticone)/sizeof(orange_tacticone)[0]);i++) {
		robot_movetoposition_orange_tacticone(i);
	}
}
*/
