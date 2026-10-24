#include "task_display_matrix.h"
#include "main.h"

void displayLedMatrix(uint8_t buffer){
	HAL_GPIO_WritePin(ROW0_GPIO_Port,ROW0_Pin,!(buffer & 0x01));
	HAL_GPIO_WritePin(ROW1_GPIO_Port,ROW1_Pin,!(buffer & 0x02));
	HAL_GPIO_WritePin(ROW2_GPIO_Port,ROW2_Pin,!(buffer & 0x04));
	HAL_GPIO_WritePin(ROW3_GPIO_Port,ROW3_Pin,!(buffer & 0x08));
	HAL_GPIO_WritePin(ROW4_GPIO_Port,ROW4_Pin,!(buffer & 0x10));
	HAL_GPIO_WritePin(ROW5_GPIO_Port,ROW5_Pin,!(buffer & 0x20));
	HAL_GPIO_WritePin(ROW6_GPIO_Port,ROW6_Pin,!(buffer & 0x40));
	HAL_GPIO_WritePin(ROW7_GPIO_Port,ROW7_Pin,!(buffer & 0x80));
}
