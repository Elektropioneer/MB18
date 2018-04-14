#include <Arduino.h>
#include "actuator.h"
#include "cubes.h"

int combination_current_number = 1;
int combination_cube_number = 1;

void cube_yellow(uint8_t pos) {
	if(pos == 1 || pos == 2) {
		ax_move_speed(10, yellow10, 600);
		delay(50);
		ax_move_speed(4, yellow4, 600);
		delay(50);
	} else if(pos == 3) {

	}
}

void cube_green(uint8_t pos) {
	if(pos == 1 || pos == 2) {
		ax_move_speed(10, green10, 600);
		delay(50);
		ax_move_speed(4, green4, 600);
		delay(50);
	} else if(pos == 3) {

	}
}

void cube_black(uint8_t pos) {

	if(pos == 1 || pos == 2) {
		ax_move_speed(10, black10, 600);
		delay(50);
		ax_move_speed(4, black4,600);
		delay(50);
	} else if(pos == 3) {

	}
}

void cube_orange(uint8_t pos) {
	if(pos == 1 || pos == 2) {
		ax_move_speed(10, orange10, 600);
		delay(50);
		ax_move_speed(4, orange4, 600);
		delay(50);
	} else if(pos == 3) {

	}
}

void cube_blue(uint8_t pos) {

	if(pos == 1 || pos == 2) {
		ax_move_speed(10, blue10, 600);
		delay(50);
		ax_move_speed(4, blue4, 600);
		delay(50);
	} else if(pos == 3) {

	}

}

void cube_left_in() {
	ax_move_speed(4, leftin4, 600);
	delay(1000);
	ax_move_speed(10, leftin10, 200);
	delay(5);
}

void cube_left_out() {
	ax_move_speed(4, leftout4, 600);
	delay(1000);
	ax_move_speed(10, leftout10, 200);
	delay(5);
}

void cube_right_in() {
	ax_move_speed(4, rightin4, 600);
	delay(1000);
	ax_move_speed(10, rightin10, 200);
	delay(5);
}

void cube_right_out() {
	ax_move_speed(4, rightout4, 600);
	delay(1000);
	ax_move_speed(10, rightout10, 200);
	delay(5);
}

void setup_color_comb() {
	pinMode(comb_pin_orange, INPUT);
	pinMode(comb_pin_black, INPUT);
	pinMode(comb_pin_green, INPUT);
	pinMode(comb_pin_yellow, INPUT);
	pinMode(comb_pin_blue, INPUT);

}

static uint8_t get_combination() {

	uint8_t orange, black, green, yellow, blue;

	orange = digitalRead(comb_pin_orange);
	black  = digitalRead(comb_pin_black);
	green  = digitalRead(comb_pin_green);
	yellow = digitalRead(comb_pin_yellow);
	blue   = digitalRead(comb_pin_blue);

	// EIN (first combination)
	if(orange == 1 && black == 1 && green == 1) { return 0; }
	// CU (second combination)
	else if(yellow == 1 && black == 1 && blue == 1) { return 1; }
	// CVEI (third combination)
	else if(blue == 1 && green == 1 && orange == 1) { return 2; }
	// FIER (fourth combination)
	else if(yellow == 1 && green == 1 && black == 1) { return 3; }
	// FEM (fifth combination)
	else if(black == 1 && yellow == 1 && orange == 1) { return 4; }
	// SEX (sixth combination)
	else if(green == 1 && yellow == 1 && blue == 1) { return 5; }
	// SU (seventh combination)
	else if(blue == 1 && orange == 1 && black == 1) { return 6; }
	//ORE (eight combination)
	else if(green == 1 && orange == 1 && yellow == 1) { return 7; }
	//NI (nith combination)
	else if(black == 1 && blue == 1 && green == 1) { return 8; }
	//CI (tenth combination)
	else if(orange == 1 && blue == 1 && yellow == 1) { return 9; }
	// not valid combination
	else { return 15; }
}

uint8_t comb_num = 1;									// current pile
uint8_t comb_l_i = 0, comb_l_o = 0;		// current num of cubes in dispenser left
uint8_t comb_r_i = 1, comb_r_o = 1;	  // currnet num of cubes in dispenser right (in the beginnning 1+1)

static void move_arm_by_color(uint8_t comb) {
	switch(comb) {
		case YELLOW:
			cube_yellow(comb_num);
			break;
		case GREEN:
			cube_green(comb_num);
			break;
		case BLACK:
			cube_black(comb_num);
			break;
		case ORANGE:
			cube_orange(comb_num);
			break;
		case BLUE:
			cube_blue(comb_num);
			break;
	}
}

static void move_arm_dispenser(uint8_t position) {
	switch(position) {
		case L_I:
			cube_left_in();
			break;
		case L_O:
			cube_left_out();
			break;
		case R_I:
			cube_right_in();
			break;
		case R_O:
			cube_right_out();
			break;
	}
}

static uint8_t comb_colors[10][5] = {
	// 1       2      3        X1    X2
	{ORANGE, BLACK, GREEN,  YELLOW, BLUE}, 			    // 1
	{YELLOW, BLACK, BLUE,   GREEN,  ORANGE},				// 2
	{BLUE, GREEN, ORANGE,   YELLOW, BLACK},				  // 3
	{YELLOW, GREEN, BLACK,  ORANGE, BLUE},				  // 4
	{BLACK, YELLOW, ORANGE, BLUE, GREEN},			      // 5
	{GREEN, YELLOW, BLUE,   BLACK, ORANGE},				  // 6
	{BLUE, ORANGE, BLACK,   YELLOW, GREEN},			    // 7
	{GREEN, ORANGE, YELLOW, BLUE, BLACK},			      // 8
	{BLACK, BLUE, GREEN,    ORANGE, YELLOW}, 				// 9
	{ORANGE, BLUE, YELLOW,  BLACK, GREEN}				    // 10
	/////////////////////////////////////////////////////
};

static void arm_main_movement(uint8_t cube, uint8_t leave_position, uint8_t current_num_in) {
	/*
		1) pump switch (ON)
		2) move to cube (parameter)
		3) lift DOWN
		4) lift CENTER -> cube already in 0 or 1
					  UP     -> cube already 2
		5) put inside (parameter)
		6) pump switch (OFF)
	*/

	pump_switch();
	move_arm_by_color(cube);
	delay(300);
	lift_bottom();
	delay(800);

	if(current_num_in < 2) {
		// we can stack one more
		lift_center();	
	} else {
		// we can stack just one more
		lift_upper();
	}

	move_arm_dispenser(leave_position);
	pump_switch();
	delay(500);

}

void arm_automatic() {

	/* THEORY
		1) get the combination (valid,valid,valid,notvalid,notvalid)
		 - the valid ones go to the left in and out
		 - the not valid ones go to the right in and out
		2) for loop throug all of them
		3) first three
		4) check if l_in has room
			- if yes put there
			- if not then put in l_o
		5) last two
		6) check if r_in has room
			- if yes put there
			- if not then put in r_o

	*/


	uint8_t combination = get_combination();
	uint8_t leave_position, current_num_in;

	for(int i=0; i<5; i++) {
		// first three
		if(i < 3) {
			// we have room in the left in
			if(comb_l_i < 3) {
				leave_position= L_I;	// leave position LEFT IN
				current_num_in = comb_l_i;
				comb_l_i++;						// increment
			}
			//we have no more room in the left in, moving to out
			else {
				leave_position = L_O; // leave position LEFT OUT
				current_num_in = comb_l_o;
				comb_l_o++;
			}
		}
		// last two
		else {
			// we have room in the right in
			if(comb_r_i < 3) {
				leave_position = R_I; // leave position RIGHT IN
				current_num_in = comb_r_i;
				comb_r_i++;
			}
			// we have no more room in the right in, moving out
			else {
				leave_position = R_O; // leave position RIGHT OUT
				current_num_in = comb_r_o;
				comb_r_o++;
			}

		}
		arm_main_movement(comb_colors[combination][i], leave_position, current_num_in);
	}

	comb_num++; // incrementing to next pile

}
