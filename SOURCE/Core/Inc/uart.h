#ifndef INC_UART_H_
#define INC_UART_H_

#include "global.h"
#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart2;
extern uint8_t temp;

void uart_init();
void uart_print(const char *msg);

#endif /* INC_UART_H_ */
