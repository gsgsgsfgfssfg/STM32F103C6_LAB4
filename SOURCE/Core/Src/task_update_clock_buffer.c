#include "task_update_clock_buffer.h"
#include "task_update_7_seg.h"
#include "task_update_clock.h"
#include "main.h"

void updateClockBuffer(){
	myDisplay.led[0] = analogClock.hour/10;
	myDisplay.led[1] = analogClock.hour%10;
	myDisplay.led[2] = analogClock.minute/10;
	myDisplay.led[3] = analogClock.minute%10;
}
