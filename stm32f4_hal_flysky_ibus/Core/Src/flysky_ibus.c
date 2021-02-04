/*
 * flysky_ibus.c
 *
 *  Created on: Feb 4, 2021
 *      Author: mokhwasomssi
 */

#include "flysky_ibus.h"

void read_channel(channel_t* channel, uint16_t* rawdata)
{
	channel->channel_1 = rawdata[3] << 8 | rawdata[2];
	channel->channel_2 = rawdata[5] << 8 | rawdata[4];
	channel->channel_3 = rawdata[7] << 8 | rawdata[6];
	channel->channel_4 = rawdata[9] << 8 | rawdata[8];
	channel->channel_5 = rawdata[11] << 8 | rawdata[10];
	channel->channel_6 = rawdata[13] << 8 | rawdata[12];
}
