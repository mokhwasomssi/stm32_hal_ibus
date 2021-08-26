# stm32f4_hal_ibus

## Brief

__ibus is a Flysky RC receiver protocol__  

___KEYWORD - `i-bus`, `FLYSKY`, `UART`, `STM32 HAL` `DMA`___

## Library Feature
- Receive stick data using DMA mode
    - 1000 - 2000
- Software fail-safe

## Dev environment  
- STM32CubeIDE
- STM32 HAL driver
- STM32F411
- FLYSKY Transmitter & Receiver
    - FS-i6, FS-A8S (fail-safe X)

## FLYSKY ibus protocol

<img src = https://user-images.githubusercontent.com/48342925/107107872-41d7f100-6877-11eb-931f-af72b5685ef4.png width = "80%">

* The ibus protocol is one of RX protocols developed by Flysky
* half-duplex
* Control multiple servos and motors using a single digital line.
* Support 14 channels
* New value can be read every 7ms
* The values received for each channel are between 1000 and 2000
* The ibus library requires a dedicated hardware serial (UART) port on microcontroller 
    * UART RX required
    * 115200 baud
    * 8N1
* Data frame  
    - 32 bytes
    - Structure
        - Example set of 32 bytes  
            ```
            20 40 DB 5 DC 5 54 5 DC 5 E8 3 D0 7 D2 5 E8 3 DC 5 DC 5 DC 5 DC 5 DC 5 DC 5 DA F3
            ```
        - Section  
            |Protocol length|Command code|CH1|CH2|CH3|...|CH14|Checksum|
            |:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
            |0x20|0x40|0xDB 0x05|0xDC 0x05|0x54 0x05|...|0xDC 0x05|0xDA 0xF3|
    - Little Endian
        |ibus data|HEX|DEC|
        |:---:|:---:|:---:|
        |CH1|0x05DB|1499|
        |CH2|0x05DC|1500|
        |CH3|0x0554|1364|
        |...|...|...|
        |CH14|0x05DC|1500|
        |Checksum|0xF3DA||
    - Checksum calculation
        - 0xFFFF - (sum of previous 30 bytes)

## STM32CubeMX
- UART
    ![image](https://user-images.githubusercontent.com/48342925/130916371-fba0d780-b273-4dc6-9996-b28158063f83.png)
- DMA
    ![image](https://user-images.githubusercontent.com/48342925/130916275-8f7e6641-5b73-459f-9c8c-d6e7b83db4c5.png)

## Example

### ibus.h
- UART1, 6 Channels
```c
/* User configuration */
#define IBUS_UART				(&huart1)
#define IBUS_USER_CHANNELS		6		// Use 6 channels
```

### main.c
- Only contain ibus things

```c
#include "ibus.h"

// variables to store ibus data
uint16_t ibus_data[IBUS_USER_CHANNELS];

// for software fail-safe
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

int main(void)
{
    ibus_init();

    while(1)
    {
        ibus_read(ibus_data);
	    ibus_soft_failsafe(ibus_data, 10); // if ibus is not updated, clear ibus data.
	    HAL_Delay(10);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == IBUS_UART)
		ibus_reset_failsafe();
}
```