#include <Arduino.h>
#include "actuator.h"
#include "cubes.h"

void cube_yellow() {
	ax_move_speed(10, yellow10, 600);
	delay(50);
	ax_move_speed(4, yellow4, 600);
	delay(50);
}

void cube_green() {
	ax_move_speed(10, green10, 600);
	delay(50);
	ax_move_speed(4, green4, 600);
	delay(50);
}

void cube_black() {
	ax_move_speed(10, black10, 600);
	delay(50);
	ax_move_speed(4, black4,600);
	delay(50);
}

void cube_orange() {
	ax_move_speed(10, orange10, 600);
	delay(50);
	ax_move_speed(4, orange4, 600);
	delay(50);

}

void cube_blue() {
	ax_move_speed(10, blue10, 600);
	delay(50);
	ax_move_speed(4, blue4, 600);
	delay(50);
}

void cube_left_in() {
	ax_move_speed(4, leftin4, 600);
	delay(1000);
	ax_move_speed(10, leftin10, 200);
	delay(5);
}
