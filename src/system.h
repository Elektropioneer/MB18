#include <Arduino.h>

#define PIN_JUMPER PB13
#define PIN_SIDE   PB14

#define SIDE_ORANGE 1
#define SIDE_GREEN  0

void system_init();
void wait_for_rpi();
void read_pi();
void wait_for_jumper();
uint8_t get_side();

#define BIG_ROBOT
