#ifndef INC_TASK_UPDATE_CLOCK_H_
#define INC_TASK_UPDATE_CLOCK_H_

#include "stm32f1xx_hal.h"

typedef struct{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} analogTimer;

extern analogTimer analogClock;

void clockInit(uint8_t hour, uint8_t minute, uint8_t second);
void updateClock();

#endif /* INC_TASK_UPDATE_CLOCK_H_ */
