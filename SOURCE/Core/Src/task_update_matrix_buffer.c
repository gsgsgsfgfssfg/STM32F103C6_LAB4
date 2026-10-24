#include "task_update_matrix_buffer.h"
#include "task_display_matrix.h"
#include "main.h"

const int MAX_LED_MATRIX = 8;
const int MAX_FRAME = 9;
int index_led_matrix = 0;
int index_frame = 0;
uint8_t matrix_buffer[9][8] = {
		{0x00, 0xfc, 0x12, 0x11, 0x11, 0x12 ,0xfc, 0x00},
		{0xfc, 0x12, 0x11, 0x11, 0x12 ,0xfc, 0x00, 0x00},
		{0x12, 0x11, 0x11, 0x12 ,0xfc, 0x00, 0x00, 0x00},
		{0x11, 0x11, 0x12 ,0xfc, 0x00, 0x00, 0x00, 0xfc},
		{0x11, 0x12 ,0xfc, 0x00, 0x00, 0x00, 0xfc, 0x12},
		{0x12 ,0xfc, 0x00, 0x00, 0x00, 0xfc, 0x12, 0x11},
		{0xfc, 0x00, 0x00, 0x00, 0xfc, 0x12, 0x11, 0x11},
		{0x00, 0x00, 0x00, 0xfc, 0x12, 0x11, 0x11, 0x12},
		{0x00, 0x00, 0xfc, 0x12, 0x11, 0x11, 0x12, 0xfc},
};

void updateFrame(){
	index_frame = (index_frame + 1)%MAX_FRAME;
}

void updateIndex(){
	index_led_matrix = (index_led_matrix + 1)%MAX_LED_MATRIX;
	updateMatrixBuffer();
}

void updateMatrixBuffer(){
	switch(index_led_matrix){
		case 0:
			HAL_GPIO_WritePin(GPIOA,ENM0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_SET);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOA,ENM1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,ENM0_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_SET);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOA,ENM2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,ENM0_Pin |ENM1_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_SET);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA,ENM3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_SET);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOA,ENM4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_SET);
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOA,ENM5_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_SET);
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOA,ENM6_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin
                          |ENM5_Pin|ENM7_Pin, GPIO_PIN_SET);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOA,ENM7_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin
                          |ENM5_Pin|ENM6_Pin, GPIO_PIN_SET);
			break;
		default: return;
	}
	displayLedMatrix(matrix_buffer[index_frame][index_led_matrix]);
}
