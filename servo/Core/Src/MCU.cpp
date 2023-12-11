/*
 * MCU.cpp
 *
 *  Created on: Nov 30, 2023
 *      Author: bogda
 */
#include "MCU.h"

void mcu_uart5_transmit(const uint8_t* const frame, uint8_t length){
	HAL_HalfDuplex_EnableTransmitter( &huart5 );
	HAL_UART_Transmit(&huart5, frame, length, 2);
}


