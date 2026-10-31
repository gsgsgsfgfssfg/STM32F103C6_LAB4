#include "sch_error.h"

uint8_t SCH_ERROR_CODE_G = SCH_OK;
uint8_t errorTimerTick = 0;

void setError(uint8_t error){
	SCH_ERROR_CODE_G = error;
}

void errorInit(){
	SCH_ERROR_CODE_G = SCH_OK;
	HAL_GPIO_WritePin(ERROR_LED_GPIO_Port, ERROR_LED_Pin, GPIO_PIN_SET);
}
uint8_t getError(uint8_t error){
	return SCH_ERROR_CODE_G;
}
void errorLedStart(){
	HAL_GPIO_WritePin(ERROR_LED_GPIO_Port, ERROR_LED_Pin, GPIO_PIN_RESET);
	errorTimerTick = 60000/TIME_CYCLES;
}
void errorRun(){
	if (errorTimerTick > 0){
		errorTimerTick--;
		if (errorTimerTick <= 0) HAL_GPIO_WritePin(ERROR_LED_GPIO_Port, ERROR_LED_Pin, GPIO_PIN_SET);
	}
}
