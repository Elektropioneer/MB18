#include "timer.h"
#include "system.h"
#include "odometry.h"

/*
 * Great help from: http://librambutan.readthedocs.io/en/latest/lang/api/hardwaretimer.html
 */

#define ONE_SECOND_RATE 1000 // 1000hz -> 1000ms -> 1 second
#define TIMER_END 90000

long long sys_time = 0;       // this is where we log the current sys_time
HardwareTimer sys_timer(1);   // we are initing the timer


static void sys_time_updater(void) {

  if(sys_time >= TIMER_END) {
    // do something
  }

  if((sys_time % 1) == 0) {
    // every 1ms
    read_pi();
  }


  sys_time++;
}

void timer_setup(void) {

  // pausing while setting it up
  sys_timer.pause();

  // we are setting the period
  sys_timer.setPeriod(ONE_SECOND_RATE);

  // set up an interrupt on channel 1
  sys_timer.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
  sys_timer.setCompare(TIMER_CH1, 1);  // Interrupt 1 count after each update
  sys_timer.attachInterrupt(1, sys_time_updater);

  // resetting the sys_time counter and resetting and starting the timer
  timer_reset();
}

void timer_reset(void) {
  sys_time = 0;

  // refresh the timer's count, prescale, and overflow
  sys_timer.refresh();

  // start the timer counting
  sys_timer.resume();
}

long long timer_get_sys_time() { return sys_time; }
