#ifndef INC_UART_H_
#define INC_UART_H_

#include "global.h"
#include <stdio.h>
#include <string.h>

#define UART_OK                 0
#define UART_QUEUE_FULL        -1
#define UART_MESSAGE_TOO_LONG  -2
#define UART_ERROR             -3

extern UART_HandleTypeDef huart2;

void uart_init(void);
int uart_print(const char *msg);

#endif /* INC_UART_H_ */
