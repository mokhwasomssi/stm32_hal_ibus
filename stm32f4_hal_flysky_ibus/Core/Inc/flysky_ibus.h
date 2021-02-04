/*
 * flysky_ibus.h
 *
 *  Created on: Feb 4, 2021
 *      Author: mokhwasomssi
 */

#ifndef _FLYSKY_IBUS_H_
#define _FLYSKY_IBUS_H_

#include "stm32f4xx_hal.h"

typedef struct _channel
{
    uint16_t channel_1;
    uint16_t channel_2;
    uint16_t channel_3;
    uint16_t channel_4;
    uint16_t channel_5;
    uint16_t channel_6;

} channel_t;

void read_channel(channel_t* channel, uint16_t* rawdata);

#endif /* INC_FLYSKY_IBUS_H_ */
