#include "scheduler.h"

int TIME_CYCLES = 10;
uint8_t SCH_count;

void SCH_Init(){
	for(unsigned char i=0;i<SCH_MAX_TASKS;i++){
		SCH_tasks_G[i].pTask = NULL;
		SCH_tasks_G[i].Delay = 0;
		SCH_tasks_G[i].Period = 0;
		SCH_tasks_G[i].RunMe = 0;
	}
	SCH_count = 0;
}

unsigned char SCH_AddTask(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD){
	if (SCH_count >= SCH_MAX_TASKS) return 0;
	unsigned char Index = 0;
	if (SCH_count == 0){
		SCH_tasks_G[0].pTask = pFunction;
		SCH_tasks_G[0].Delay = DELAY/TIME_CYCLES;
		SCH_tasks_G[0].Period = PERIOD/TIME_CYCLES;
	} else {
		uint32_t sum=0;
		while(Index < SCH_count && sum + SCH_tasks_G[Index].Delay <= DELAY/TIME_CYCLES){
			sum += SCH_tasks_G[Index].Delay;
			Index++;
		}
		for(int i = SCH_count; i>Index;i--){
			SCH_tasks_G[i] = SCH_tasks_G[i-1];
		}
		SCH_tasks_G[Index].pTask = pFunction;
		SCH_tasks_G[Index].Delay = DELAY/TIME_CYCLES - sum;
		SCH_tasks_G[Index].Period = PERIOD/TIME_CYCLES;
		if (Index != SCH_count){
			SCH_tasks_G[Index+1].Delay -= SCH_tasks_G[Index].Delay;
		}

	}
	SCH_count++;
	return Index;
}

void SCH_DispatchTasks(){
	if (SCH_count == 0) return;
	if (SCH_tasks_G[0].RunMe > 0){
		sTask t = SCH_tasks_G[0];
		t.pTask();
		if (SCH_DeleteTask(0) == 1 && t.Period !=0)
			SCH_AddTask(t.pTask,t.Period*TIME_CYCLES,t.Period*TIME_CYCLES);
	}
}

void SCH_Update(){
	if (SCH_count == 0) return;
	if (SCH_tasks_G[0].Delay > 0) SCH_tasks_G[0].Delay --;
	if (SCH_tasks_G[0].Delay <= 0) SCH_tasks_G[0].RunMe = 1;
}

unsigned char SCH_DeleteTask(const unsigned char TASK_INDEX){
	if (SCH_count == 0) return 0;
	for(int i=TASK_INDEX; i<SCH_count-1;i++){
		SCH_tasks_G[i]=SCH_tasks_G[i+1];
		if (i == 0 && SCH_tasks_G[i].Delay == 0) SCH_tasks_G[i].RunMe = 1;
	}
	SCH_tasks_G[SCH_count-1].pTask = NULL;
	SCH_tasks_G[SCH_count-1].Delay = 0;
	SCH_tasks_G[SCH_count-1].Period = 0;
	SCH_count--;
	return 1;
}
