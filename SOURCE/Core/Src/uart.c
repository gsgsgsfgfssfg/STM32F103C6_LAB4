#include "uart.h"

#define UART_QUEUE_SIZE     25
#define UART_MESSAGE_SIZE   200

UART_HandleTypeDef huart2;

static uint8_t rx_temp;

static uint8_t tx_busy = 0;

static char tx_buffer[UART_MESSAGE_SIZE];

typedef struct {
    char data[UART_MESSAGE_SIZE];
    uint16_t length;
} UART_Message;

static UART_Message tx_queue[UART_QUEUE_SIZE];

static uint8_t queue_head = 0;
static uint8_t queue_tail = 0;
static uint8_t queue_count = 0;

static void uart_start_next(void){
    if (queue_count == 0) {
        tx_busy = 0;
        return;
    }

    memcpy(tx_buffer,
           tx_queue[queue_tail].data,
           tx_queue[queue_tail].length);

    uint16_t len = tx_queue[queue_tail].length;

    queue_tail = (queue_tail + 1) % UART_QUEUE_SIZE;
    queue_count--;

    tx_busy = 1;

    if (HAL_UART_Transmit_IT(
            &huart2,
            (uint8_t *)tx_buffer,
            len) != HAL_OK) {

        tx_busy = 0;
        /* TODO: Handle transmission error */
    }
}


void uart_init(void){
    tx_busy = 0;

    queue_head = 0;
    queue_tail = 0;
    queue_count = 0;

    HAL_UART_Receive_IT(&huart2, &rx_temp, 1);
}


int uart_print(const char *msg){
    if (msg == NULL) {
        return UART_ERROR;
    }

    uint16_t len = strlen(msg);

    if (len == 0) {
        return UART_OK;
    }

    if (len >= UART_MESSAGE_SIZE) {
        return UART_MESSAGE_TOO_LONG;
    }

    uint32_t primask = __get_PRIMASK();
    __disable_irq();

    if (queue_count >= UART_QUEUE_SIZE) {
        if (!primask) __enable_irq();
        return UART_QUEUE_FULL;
    }

    memcpy(tx_queue[queue_head].data, msg, len);
    tx_queue[queue_head].length = len;

    queue_head = (queue_head + 1) % UART_QUEUE_SIZE;
    queue_count++;

    if (!tx_busy) {
        uart_start_next();
    }

    if (!primask) __enable_irq();

    return UART_OK;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2) {
        uart_start_next();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2) {

        /* TODO: Process received byte */
    	HAL_UART_Transmit_IT(&huart2, &rx_temp, 1);
        HAL_UART_Receive_IT(&huart2, &rx_temp, 1);
    }
}
