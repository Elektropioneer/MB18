#include <Arduino.h>
#include <HardwareSerial.h>
#include "system.h"

char test[8];

char snd[8] = {1,2,3,4,5,6,7,8};
void setup() {
	system_init();
	
	wait_for_rpi();
}

void loop() {
	
	read_pi();


}
