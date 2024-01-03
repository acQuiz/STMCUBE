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

//void mcu_uart5_reciver();{
	//HAL_HalfDuplex_EnableReceiver(UART_HandleTypeDef *huart);
	//HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	//HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout
//}

