#include "uart.h"

UART_HandleTypeDef huart2;
uint8_t temp = 0;
void uart_init(){
	HAL_UART_Receive_IT(&huart2, &temp, 1);
}
void uart_print(const char *msg){
	HAL_UART_Transmit(&huart2, (void*)msg, strlen(msg),50);
}
