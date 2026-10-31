/*
 * watchdog.h
 *
 *  Created on: Oct 31, 2026
 *      Author: PHUOC_NHM
 */

#ifndef INC_WATCHDOG_H_
#define INC_WATCHDOG_H_

#include "global.h"

extern IWDG_HandleTypeDef hiwdg;

void setWatchDogLED(GPIO_PinState val);
void blinkWatchDogLED();
void watchDogInit();
uint8_t isWatchDogReset();
void watchDogRefresh();

#endif /* INC_WATCHDOG_H_ */
