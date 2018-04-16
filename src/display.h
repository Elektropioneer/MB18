#include <Arduino.h>

#define LCD_ADDRESS_SCORE 0x3F

void display_setup();
void display_score_increment(uint8_t score);
