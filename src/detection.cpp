#include <Arduino.h>
#include "detection.h"
#include "odometry.h"
#include "system.h"

uint8_t cs_pins_big[6] = {
    CS_FL_PIN, CS_FR_PIN,
    CS_BL_PIN, CS_BR_PIN,
    CS_FC_PIN, CS_BC_PIN
};
uint8_t cs_pins_small[4] = {
    CS_FL_PIN, CS_FR_PIN,
    CS_BL_PIN, CS_BR_PIN
};

/* helper functions for detection pin setup and reading */
void detection_setup_pin(uint8_t pin)  { pinMode(pin, INPUT);     }
uint8_t detection_get_pin(uint8_t pin) { return digitalRead(pin); }

/*
 * Function:    void detection_setup()
 * Description: sets up the pins dependent on what robot we are using and the pins
 */
void detection_setup() {

  #ifdef BIG_ROBOT
    for(int i=0; i<6; i++) { detection_get_pin(cs_pins_big[i]);   }
  #else
    for(int i=0; i<4; i++) { detection_get_pin(cs_pins_small[i]); }
  #endif

}

/* Checking FRONT LEFT sensors */
uint8_t detection_fl() {
  if(detection_get_pin(CS_FL_PIN) == CS_FL_DETECTED) {
    Serial1.print("Detected FL\n");
    return DETECTED;
  }

  return NOT_DETECTED;
}

/* Checking FRONT RIGHT sensors */
uint8_t detection_fr() {
  if(detection_get_pin(CS_FR_PIN) == CS_FR_DETECTED) {
    Serial1.print("Detected FR");
    return DETECTED;
  }

  return NOT_DETECTED;
}

/* Checking FRONT CENTER sensors */
uint8_t detection_fc() {
  if(detection_get_pin(CS_FC_PIN) == CS_FC_DETECTED) {
    Serial1.print("Detected FC");
    return DETECTED;
  }

  return NOT_DETECTED;
}

/* Checking BACK LEFT sensors */
uint8_t detection_bl() {
  if(detection_get_pin(CS_BL_PIN) == CS_BL_DETECTED) {
    Serial1.print("Detected BL");
    return DETECTED;
  }

  return NOT_DETECTED;
}

/* Checking BACK RIGHT sensors */
uint8_t detection_br() {
  if(detection_get_pin(CS_BR_PIN) == CS_BR_DETECTED) {
    Serial1.print("Detected BR");
    return DETECTED;
  }

  return NOT_DETECTED;
}

/* Checking BACK CENTER sensors */
uint8_t detection_bc() {
  if(detection_get_pin(CS_BC_PIN) != CS_BC_DETECTED) {
    Serial1.print("Detected BC");
    return DETECTED;
  }

  return NOT_DETECTED;
}

/* Checking ALL FRONT sensors */
uint8_t detection_front() {
    #ifdef BIG_ROBOT
      if(detection_fl() == DETECTED ||
         detection_fr() == DETECTED/* ||
       detection_fc()   != DETECTED*/) {
           return DETECTED;
         }

      return NOT_DETECTED;
    #else
      if(detection_fl() == DETECTED ||
         detection_fr() == DETECTED) {
           return DETECTED;
         }

      return NOT_DETECTED;
    #endif
}

/* Checking ALL BACK sensors */
uint8_t detection_back() {
    #ifdef BIG_ROBOT
      if(detection_bl() == DETECTED ||
         detection_br() == DETECTED ||
         detection_bc() == DETECTED) {
           return DETECTED;
         }

      return NOT_DETECTED;
    #else
      if(detection_bl() == DETECTED ||
         detection_br() == DETECTED) {
           return DETECTED;
         }

      return NOT_DETECTED;
    #endif
}
