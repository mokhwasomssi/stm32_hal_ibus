/*
 * flysky_ibus.c
 *
 *  Created on: Feb 4, 2021
 *      Author: mokhwasomssi
 */

#include "flysky_ibus.h"

uint8_t rx_buffer[32] = {0};
uint16_t channel[IBUS_CHANNLES] = {0};
uint16_t checksum_cal, checksum_ibus;

void IBUS_INIT()
{
	HAL_UART_Receive_IT(IBUS_UART, rx_buffer, 32);
}

void IBUS_READ_CHANNEL()
{
	if(rx_buffer[0] == IBUS_LENGTH && rx_buffer[1] == IBUS_COMMAND40)
	{
		checksum_cal = 0xffff - rx_buffer[0] - rx_buffer[1];

		for(int i = 0; i < IBUS_CHANNLES; i++)
		{
			channel[i] = (uint16_t)(rx_buffer[i * 2 + 3] << 8 | rx_buffer[i * 2 + 2]);
			checksum_cal = checksum_cal - rx_buffer[i * 2 + 3] - rx_buffer[i * 2 + 2];
		}

		checksum_ibus = rx_buffer[31] << 8 | rx_buffer[30];

		if(checksum_cal == checksum_ibus)
		{
			HAL_UART_Receive_IT(IBUS_UART, rx_buffer, 32);
		}
	}
}

