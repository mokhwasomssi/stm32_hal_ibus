/*
 * flysky_ibus.h
 *
 *  Created on: Feb 4, 2021
 *      Author: mokhwasomssi
 */


#ifndef __IBUS_H__
#define __IBUS_H__


#include "usart.h"              // header from stm32cubemx code generate
#include "stdbool.h"


/* User configuration */

// ibus UART Interface
#define IBUS_UART				(&huart1)
#define IBUS_UART_INSTANCE		(USART1)

// ibus User Channels
#define IBUS_USER_CHANNELS		6		// Use 6 channels

// ibus Constant
#define IBUS_LENGTH				0x20	// 32 bytes
#define IBUS_COMMAND40			0x40	// Command to set servo or motor speed is always 0x40
#define IBUS_MAX_CHANNLES		14


/* ibus Main Functions */
void ibus_init();
bool ibus_read_channel(uint16_t* ibus_data);


/* ibus Sub Functions */
bool ibus_is_valid();
bool ibus_checksum();
void ibus_little_endian(uint16_t* ibus_data);



#endif /* __IBUS_H__ */
