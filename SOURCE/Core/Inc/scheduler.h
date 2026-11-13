#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "global.h"
#include "sch_error.h"
#include "uart.h"

extern TIM_HandleTypeDef htim2;
extern int TIME_CYCLES;

typedef struct{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	char *TaskID;
} sTask;

#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0
sTask SCH_tasks_G[SCH_MAX_TASKS];

uint32_t getNewTaskID();
void SCH_Init();
unsigned char SCH_Insert(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD, char *TASKID);
unsigned char SCH_AddTask(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD, char *TASKID);
void SCH_DispatchTasks();
void SCH_Update();
unsigned char SCH_DeleteTask (const char *TASK_ID);
void SCH_ReportError(uint8_t errorCode);
uint32_t SCH_GetTime();
#endif /* INC_SCHEDULER_H_ */
