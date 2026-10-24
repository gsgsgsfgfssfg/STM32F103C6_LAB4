#include "task_dot_blinking.h"
#include "main.h"

void dotBlinking(){
	HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
}
