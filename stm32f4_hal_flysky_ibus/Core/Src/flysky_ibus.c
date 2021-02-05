/*
 * flysky_ibus.c
 *
 * This library was written by referring to "https://github.com/bmellink/IBusBM"
 *
 *  Created on: Feb 4, 2021
 *      Author: mokhwasomssi
 */

#include "flysky_ibus.h"

uint8_t rx_buffer[32] = {0};
uint16_t channel[IBUS_USER_CHANNELS] = {0};
uint16_t checksum_cal, checksum_ibus;

void IBUS_INIT()
{
	HAL_UART_Receive_IT(IBUS_UART, rx_buffer, 32);
}

void IBUS_READ_CHANNEL(uint8_t user_channels)
{
	uint16_t channel_buffer[IBUS_MAX_CHANNLES] = {0};

	if(rx_buffer[0] == IBUS_LENGTH && rx_buffer[1] == IBUS_COMMAND40)
	{
		checksum_cal = 0xffff - rx_buffer[0] - rx_buffer[1];

		for(int i = 0; i < IBUS_MAX_CHANNLES; i++)
		{
			channel_buffer[i] = (uint16_t)(rx_buffer[i * 2 + 3] << 8 | rx_buffer[i * 2 + 2]);
			checksum_cal = checksum_cal - rx_buffer[i * 2 + 3] - rx_buffer[i * 2 + 2];
		}

		checksum_ibus = rx_buffer[31] << 8 | rx_buffer[30];

		if(checksum_cal == checksum_ibus)
		{
			for(int j = 0; j < user_channels; j++)
			{
				channel[j] = channel_buffer[j];
			}
		}
	}

	HAL_UART_Receive_IT(IBUS_UART, rx_buffer, 32);
}

