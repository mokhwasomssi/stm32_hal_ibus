/*
 * flysky_ibus.h
 *
 * This library was written by referring to "https://github.com/bmellink/IBusBM"
 *
 *  Created on: Feb 4, 2021
 *      Author: mokhwasomssi
 */

#ifndef _FLYSKY_IBUS_H_
#define _FLYSKY_IBUS_H_


#include "usart.h"


/* User configuration */
#define IBUS_UART				(&huart1)
#define IBUS_UART_INSTANCE		(USART1)
#define IBUS_USER_CHANNELS		6			// Use 6 channels
/* User configuration */

#define IBUS_LENGTH				0x20	// 32 bytes
#define IBUS_COMMAND40			0x40	// Command to set servo or motor speed is always 0x40
#define IBUS_MAX_CHANNLES		14

void ibus_init();
bool ibus_read_channel();


#endif /* _FLYSKY_IBUS_H_ */
