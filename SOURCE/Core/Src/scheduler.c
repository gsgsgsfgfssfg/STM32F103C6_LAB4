#include "scheduler.h"

uint8_t SCH_count;
static uint32_t nextTaskID=0;
TIM_HandleTypeDef htim2;
int TIME_CYCLES = 10;

uint32_t getNewTaskID(){
	nextTaskID++;
	return nextTaskID;
}
void SCH_Init(){
	HAL_TIM_Base_Start_IT(&htim2);
	TIME_CYCLES = ((htim2.Init.Prescaler + 1) * (htim2.Init.Period+1) * 1000)/HAL_RCC_GetHCLKFreq();
	for(unsigned char i=0;i<SCH_MAX_TASKS;i++){
		SCH_tasks_G[i].pTask = NULL;
		SCH_tasks_G[i].Delay = 0;
		SCH_tasks_G[i].Period = 0;
		SCH_tasks_G[i].RunMe = 0;
	}
	SCH_count = 0;
}

unsigned char SCH_Insert(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD, unsigned int TASKID){
	if (pFunction == NULL) {
		SCH_ReportError(SCH_ERROR_NULL_CALLBACK);
		return SCH_MAX_TASKS;
	}
	if (SCH_count >= SCH_MAX_TASKS) {
		SCH_ReportError(SCH_ERROR_QUEUE_FULL);
		return SCH_MAX_TASKS;
	}
	if (SCH_count == 0){
		SCH_tasks_G[0].pTask = pFunction;
		SCH_tasks_G[0].Delay = DELAY;
		SCH_tasks_G[0].Period = PERIOD;
		SCH_tasks_G[0].TaskID = TASKID;
	} else {
		uint32_t sum=0;
		uint8_t Index = 0;
		while(Index < SCH_count && sum + SCH_tasks_G[Index].Delay <= DELAY){
			sum += SCH_tasks_G[Index].Delay;
			Index++;
		}
		for(int i = SCH_count; i>Index;i--){
			SCH_tasks_G[i] = SCH_tasks_G[i-1];
		}
		SCH_tasks_G[Index].pTask = pFunction;
		SCH_tasks_G[Index].Delay = DELAY - sum;
		SCH_tasks_G[Index].Period = PERIOD;
		SCH_tasks_G[Index].TaskID = TASKID;
		if (Index != SCH_count){
			SCH_tasks_G[Index+1].Delay -= SCH_tasks_G[Index].Delay;
		}

	}
	SCH_count++;
	return SCH_OK;
}

unsigned char SCH_AddTask(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD){
	if (pFunction == NULL) {
		SCH_ReportError(SCH_ERROR_NULL_CALLBACK);
		return SCH_MAX_TASKS;
	}
	if (SCH_count >= SCH_MAX_TASKS) {
		SCH_ReportError(SCH_ERROR_QUEUE_FULL);
		return SCH_MAX_TASKS;
	}
	uint32_t TASKID = getNewTaskID();
	return SCH_Insert(pFunction, DELAY/TIME_CYCLES, PERIOD/TIME_CYCLES, TASKID);
}

void SCH_DispatchTasks(){
	if (SCH_count == 0) return;
	if (SCH_tasks_G[0].RunMe > 0){
		sTask t = SCH_tasks_G[0];
		t.pTask();
		if (SCH_DeleteTask(t.TaskID) == SCH_OK && t.Period !=0)
			SCH_Insert(t.pTask,t.Period,t.Period,t.TaskID);
	}
}

void SCH_Update(){
	if (SCH_count == 0) return;
	if (SCH_tasks_G[0].Delay > 0) SCH_tasks_G[0].Delay --;
	if (SCH_tasks_G[0].Delay <= 0) SCH_tasks_G[0].RunMe = 1;
}

unsigned char SCH_DeleteTask(const uint32_t TASK_ID){
	if (SCH_count == 0) return 0;
	uint8_t TASK_INDEX = 0;
	uint8_t found = 0;
	for(int i=0;i<SCH_count;i++) {
		if (SCH_tasks_G[i].TaskID == TASK_ID) {
			TASK_INDEX = i;
			found = 1;
			break;
		}
	}
	if (found == 0) {
		SCH_ReportError(SCH_ERROR_TASK_NOT_FOUND);
		return SCH_MAX_TASKS;
	}
	for(int i=TASK_INDEX; i<SCH_count-1;i++){
		SCH_tasks_G[i]=SCH_tasks_G[i+1];
		if (i == 0 && SCH_tasks_G[i].Delay == 0) SCH_tasks_G[i].RunMe = 1;
	}
	SCH_tasks_G[SCH_count-1].pTask = NULL;
	SCH_tasks_G[SCH_count-1].Delay = 0;
	SCH_tasks_G[SCH_count-1].Period = 0;
	SCH_count--;
	return TASK_INDEX;
}

void SCH_ReportError(uint8_t errorCode){
	if (errorCode ==  SCH_OK) return;
	setError(errorCode);
	errorLedStart();
}
