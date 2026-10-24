#include "task_update_clock.h"
#include "main.h"

analogTimer analogClock={0,0,0};

void clockInit(uint8_t hour, uint8_t minute, uint8_t second){
	analogClock.hour = hour;
	analogClock.minute = minute;
	analogClock.second = second;
}

void updateClock(){
	analogClock.second++;
	if (analogClock.second >= 60) {
		analogClock.second = 0;
		analogClock.minute++;
	}
	if(analogClock.minute >= 60) {
		analogClock.minute = 0;
		analogClock.hour++;
	}
	if(analogClock.hour >= 24){
		analogClock.hour = 0;
	}
}
