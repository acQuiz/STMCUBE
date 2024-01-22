/*
 * MCU.cpp
 *
 *  Created on: Nov 30, 2023
 *      Author: adamc
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


//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//
//	uint8_t Data[50]; // Tablica przechowujaca wysylana wiadomosc.
//	uint16_t size = 0; // Rozmiar wysylanej wiadomosci
//
//	// Odebrany znak zostaje przekonwertowany na liczbe calkowita i sprawdzony
//	// instrukcja warunkowa
//	switch (atoi(&Received)) {
//
//	case 0: // Jezeli odebrany zostanie znak 0
//		size = sprintf(Data, "STOP\n\r");
//		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
//		break;
//
//	case 1: // Jezeli odebrany zostanie znak 1
//		size = sprintf(Data, "START\n\r");
//		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
//		break;
//
//	default: // Jezeli odebrano nieobslugiwany znak
//		size = sprintf(Data, "Odebrano nieznany znak: %c\n\r", Received);
//		break;
//	}
//
//	HAL_UART_Transmit_IT(&huart1, Data, size); // Rozpoczecie nadawania danych z wykorzystaniem przerwan
//	HAL_UART_Receive_IT(&huart1, &Received, 1); // Ponowne włączenie nasłuchiwania
//}
