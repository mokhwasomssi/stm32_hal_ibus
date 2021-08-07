/*
 * flysky_ibus.c
 *
 * This library was written by referring to "https://github.com/bmellink/IBusBM"
 *
 *  Created on: Feb 4, 2021
 *      Author: mokhwasomssi
 */


#include "ibus.h"


static uint8_t uart_rx_buffer[32] = {0};


/* ibus Main Functions */
void ibus_init()
{
	HAL_UART_Receive_DMA(IBUS_UART, uart_rx_buffer, 32);
}

bool ibus_read_channel(uint16_t* ibus_data)
{
	if(!ibus_is_valid())
		return false;

	if(!ibus_checksum())
		return false;

	ibus_little_endian(ibus_data);

	return true;
}


/* ibus Sub Functions */
bool ibus_is_valid()
{
	// is it ibus?
	return (uart_rx_buffer[0] == IBUS_LENGTH && uart_rx_buffer[1] == IBUS_COMMAND40);
}


bool ibus_checksum()
{
 	uint16_t checksum_cal = 0xffff;
	uint16_t checksum_ibus;

	for(int i = 0; i < 30; i++)
	{
		checksum_cal -= uart_rx_buffer[i];
	}

	checksum_ibus = uart_rx_buffer[31] << 8 | uart_rx_buffer[30]; // checksum value from ibus
	
	return (checksum_ibus == checksum_cal);
}


void ibus_little_endian(uint16_t* ibus_data)
{
	for(int ch_index = 0, bf_index = 2; ch_index < IBUS_USER_CHANNELS; ch_index++, bf_index += 2)
	{
		ibus_data[ch_index] = uart_rx_buffer[bf_index + 1] << 8 | uart_rx_buffer[bf_index];
	}
}
