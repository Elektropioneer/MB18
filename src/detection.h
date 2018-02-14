#include <Arduino.h>
#include "system.h"

void detection_setup_pin(uint8_t pin);
uint8_t detection_get_pin(uint8_t pin);

#define DETECTED     1
#define NOT_DETECTED 0

#define CS_FL_PIN 0
  #define CS_FL_DETECTED 1
#define CS_FC_PIN 0
  #define CS_FC_DETECTED 1
#define CS_FR_PIN 0
  #define CS_FR_DETECTED 1

#define CS_BL_PIN 0
  #define CS_BL_DETECTED 1
#define CS_BC_PIN 0
  #define CS_BC_DETECTED 1
#define CS_BR_PIN 0
  #define CS_BR_DETECTED 1

void detection_setup();

uint8_t detection_fl(); uint8_t detection_fr(); uint8_t detection_fc();
uint8_t detection_bl(); uint8_t detection_br(); uint8_t detection_bc();
uint8_t detection_front(); uint8_t detection_back();
