#include "task_update_7_seg.h"
#include "task_display_7_seg.h"
#include "main.h"

ledBuffer myDisplay = {{1,2,3,4}};
uint8_t ledIndex = 0;

void update7SEGBuffer(){
	HAL_GPIO_WritePin(EN0_GPIO_Port,EN0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin, GPIO_PIN_SET);
	display7SEG(myDisplay.led[ledIndex]);
	HAL_GPIO_WritePin(EN0_GPIO_Port,EN0_Pin, ledIndex != 0);
	HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin, ledIndex != 1);
	HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin, ledIndex != 2);
	HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin, ledIndex != 3);
}

void update7SEGIndex(){
	ledIndex = (ledIndex + 1)%4;
}
