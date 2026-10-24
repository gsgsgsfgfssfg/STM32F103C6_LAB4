#ifndef INC_TASK_UPDATE_MATRIX_BUFFER_H_
#define INC_TASK_UPDATE_MATRIX_BUFFER_H_

#include "stm32f1xx_hal.h"

extern const int MAX_LED_MATRIX;
extern const int MAX_FRAME;
extern int index_led_matrix;
extern int index_frame;
extern uint8_t matrix_buffer[9][8];

void updateFrame();
void updateIndex();
void updateMatrixBuffer();

#endif /* INC_TASK_UPDATE_MATRIX_BUFFER_H_ */
