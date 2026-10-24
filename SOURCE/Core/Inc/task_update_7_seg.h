#ifndef INC_TASK_UPDATE_7_SEG_H_
#define INC_TASK_UPDATE_7_SEG_H_

#include "stm32f1xx_hal.h"

typedef struct{
	uint8_t led[4];
} ledBuffer;

extern ledBuffer myDisplay;
extern uint8_t ledIndex;

void update7SEGBuffer();
void update7SEGIndex();

#endif /* INC_TASK_UPDATE_7_SEG_H_ */
