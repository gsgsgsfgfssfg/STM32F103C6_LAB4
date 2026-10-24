#include "task_led_blinking.h"
#include "main.h"

void ledBlinking(){
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}
