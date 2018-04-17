#include <Arduino.h>
#include "actuator.h"

#define yellow10 330
#define yellow4  255

#define green10  515
#define green4   473

#define black10  317
#define black4   156

#define orange10 180
#define orange4  155

#define blue10   451
#define blue4    504

#define leftin10   618
#define leftin4    158
#define leftout10  525
#define leftout4   164

#define rightin10  412
#define rightin4   859
#define rightout10 515
#define rightout4  857

void cube_yellow(uint8_t pos);
void cube_green(uint8_t pos);
void cube_black(uint8_t pos);
void cube_orange(uint8_t pos);
void cube_blue(uint8_t pos);

void cube_right_in();
void cube_right_out();
void cube_left_in();
void cube_left_out();

#define comb_pin_orange PA0
#define comb_pin_black  PA1
#define comb_pin_green  PA4
#define comb_pin_yellow PA5
#define comb_pin_blue   PB5

#define ORANGE 1
#define BLACK 2
#define GREEN 3
#define YELLOW 4
#define BLUE 5

#define L_I 1
#define L_O 2
#define R_I 3
#define R_O 4

void setup_color_comb();
uint8_t arm_automatic();
