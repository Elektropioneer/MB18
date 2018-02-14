#include <Arduino.h>
#include "system.h"
#include "timer.h"
#include "servo.h"
#include "odometry.h"
#include "detection.h"

void system_init() {

  timer_setup();

  odometry_setup();
  servo_setup();
  detection_setup();

}
