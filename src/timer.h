#include <Arduino.h>
#include <HardwareTimer.h>

extern long long sys_time;
void timer_setup(void);
void timer_reset(void);
long long  timer_get_sys_time();
