#include "watchdog.h"

IWDG_HandleTypeDef hiwdg;

void setWatchDogLED(GPIO_PinState val){
	HAL_GPIO_WritePin(WATCHDOG_GPIO_Port, WATCHDOG_Pin, val);
}
void blinkWatchDogLED(){
	for(int i=0;i<5;i++){
		setWatchDogLED(GPIO_PIN_RESET);
		HAL_Delay(100);
		setWatchDogLED(GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_IWDG_Refresh(&hiwdg);
	}
}
void watchDogInit(){
	if (isWatchDogReset() == 1) blinkWatchDogLED();
	setWatchDogLED(GPIO_PIN_SET);
}
uint8_t isWatchDogReset(){
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET){
		__HAL_RCC_CLEAR_RESET_FLAGS();
		return 1;
	}
	return 0;
}
void watchDogRefresh(){
	HAL_IWDG_Refresh(&hiwdg);
}
