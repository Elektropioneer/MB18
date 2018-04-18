#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "display.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS_SCORE,16,2);

//Making custom characters, 8 of them is maximum, so we made it so every number can be made with combination of these 8 parts
byte bar1[8] =
{
        B11110,
        B11110,
        B11110,
        B11110,			// 1's will be shown on the lcd, 0's aren't on
        B11110,
        B11110,
        B11110,
        B11110
};
byte bar2[8] =
{
        B01111,
        B01111,
        B01111,
        B01111,			// 1's will be shown on the lcd, 0's aren't on
        B01111,
        B01111,
        B01111,
        B01111
};
byte bar3[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,			// 1's will be shown on the lcd, 0's aren't on
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar4[8] =
{
        B11110,
        B11110,
        B00000,
        B00000,			// 1's will be shown on the lcd, 0's aren't on
        B00000,
        B00000,
        B11110,
        B11110
};
byte bar5[8] =
{
        B01111,
        B01111,
        B00000,
        B00000,			// 1's will be shown on the lcd, 0's aren't on
        B00000,
        B00000,
        B01111,
        B01111
};
byte bar6[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,			// 1's will be shown on the lcd, 0's aren't on
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar7[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,			// 1's will be shown on the lcd, 0's aren't on
        B00000,
        B00000,
        B01111,
        B01111
};
byte bar8[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,			// 1's will be shown on the lcd, 0's aren't on
        B00000,
        B00000,
        B00000,
        B00000
};


static void custom0(int col)
{ // Uses segments to build numbers/letters, in this case numbers from 0 to 9
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

static void custom1(int col)
{
  lcd.setCursor(col,0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col,1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

static void custom2(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

static void custom3(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

static void custom4(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

static void custom5(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

static void custom6(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

static void custom7(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

static void custom8(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

static void custom9(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

static void printNumber(int value, int col) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  }
}


static void display_number(int first, int second, int third) {
  printNumber(first, 4);		  //Printing digit x, starting on col 7
  printNumber(second, 7);		  //Printing digit y, starting on col 10
  printNumber(third, 10);    		  //Printing digit z, starting on col 13
}

void display_setup() {
  lcd.init();
  lcd.backlight();

  //Creating characters for numbers
  lcd.createChar(1,bar1);
  lcd.createChar(2,bar2);
  lcd.createChar(3,bar3);
  lcd.createChar(4,bar4);
  lcd.createChar(5,bar5);
  lcd.createChar(6,bar6);
  lcd.createChar(7,bar7);
  lcd.createChar(8,bar8);

  /*// Using segments to make letter E
  lcd.setCursor(0, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(3);
  lcd.setCursor(0, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);

  // Using segments to make letter P
  lcd.setCursor(3, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(3,1);
  lcd.write(2);*/

  display_number(0,0,0);
}

// the current score
int current_score = 0;


void display_score_increment(uint8_t score) {
  current_score += score;                           // incrementing the score

  uint8_t first, second, third;                     // vars for the display

  first = current_score / 100;                      // get the firt digit example: 385 -> 3
  second = (current_score / 10) % 10;               // get the second digit example: 385 -> 8
  third = current_score % 10;                       // get the third digit example: 385 -> 5

  // display it
  display_number(first, second, third);
}
