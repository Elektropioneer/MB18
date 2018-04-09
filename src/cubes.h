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

void cube_yellow();
void cube_green();
void cube_black();
void cube_orange();
void cube_blue();

void cube_right_in();
void cube_right_out();
void cube_left_in();
void cube_left_out();
