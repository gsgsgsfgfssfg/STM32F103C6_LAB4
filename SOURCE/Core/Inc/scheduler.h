#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stm32f1xx_hal.h"

typedef struct{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask;

#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0
extern int TIME_CYCLES;
sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init();
unsigned char SCH_AddTask(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD);
void SCH_DispatchTasks();
void SCH_Update();
unsigned char SCH_DeleteTask (const unsigned char TASK_INDEX);
#endif /* INC_SCHEDULER_H_ */
