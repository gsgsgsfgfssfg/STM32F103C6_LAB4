#ifndef INC_SCH_ERROR_H_
#define INC_SCH_ERROR_H_

#include "global.h"
#include "scheduler.h"

#define SCH_OK                       0
#define SCH_ERROR_NULL_CALLBACK      1
#define SCH_ERROR_QUEUE_FULL         2
#define SCH_ERROR_TASK_NOT_FOUND     3

extern uint8_t SCH_ERROR_CODE_G;
extern uint8_t errorTimerTick;

void setError(uint8_t error);
void errorInit();
uint8_t getError(uint8_t error);
void errorLedStart();
void errorRun();

#endif /* INC_SCH_ERROR_H_ */
