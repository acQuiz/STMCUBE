/*
 * MCU.h
 *
 *  Created on: Nov 30, 2023
 *      Author: bogda
 */

#ifndef MCU_H_
#define MCU_H_

#include "main.h"

extern UART_HandleTypeDef huart5;


void mcu_uart5_transmit(const uint8_t* const frame, uint8_t length);

//void mcu_uart5_reciver();


#endif /* MCU_H_ */
