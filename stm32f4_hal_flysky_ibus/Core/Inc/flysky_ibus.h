/*
 * flysky_ibus.h
 *
 *  Created on: Feb 4, 2021
 *      Author: mokhwasomssi
 */

#ifndef _FLYSKY_IBUS_H_
#define _FLYSKY_IBUS_H_

#include "stm32f4xx_hal.h"
#include "usart.h"

#define IBUS_UART			(&huart1)
#define IBUS_UART_INSTANCE	(USART1)

#define IBUS_LENGTH			0x20	// 32 bytes
#define IBUS_COMMAND40		0x40	// Command to set servo or motor speed is always 0x40
#define IBUS_CHANNLES		14

void IBUS_INIT();
void IBUS_READ_CHANNEL();


#endif /* INC_FLYSKY_IBUS_H_ */
