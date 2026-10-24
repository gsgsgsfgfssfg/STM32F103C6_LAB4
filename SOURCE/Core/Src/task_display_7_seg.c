#include "task_display_7_seg.h"
#include "main.h"

const uint8_t Seg7Value[11] = {
		0b0000001,
		0b1001111,
		0b0010010,
		0b0000110,
		0b1001100,
		0b0100100,
		0b0100000,
		0b0001111,
		0b0000000,
		0b0000100,
		0b1111111
};

void display7SEG(uint8_t num){
	HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, GPIO_PIN_SET);
	int index=num;
	if (num > 9) index = 10;
	HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, Seg7Value[index] & 0x40);
	HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, Seg7Value[index] & 0x20);
	HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, Seg7Value[index] & 0x10);
	HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, Seg7Value[index] & 0x08);
	HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, Seg7Value[index] & 0x04);
	HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, Seg7Value[index] & 0x02);
	HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, Seg7Value[index] & 0x01);
}
