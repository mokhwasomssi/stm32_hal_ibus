# stm32f4_hal_flysky_ibus

**Receive each channel data from FLYSKY RC receiver which is using ibus protocol**  

## 0. Development environment  
* IDE : [STM32Cubeide (STM32Cube HAL)](https://www.st.com/en/development-tools/stm32cubeide)
* MCU : [WeAct Black Pill V3.0 (STM32F411CEU6)](https://github.com/WeActTC/MiniF4-STM32F4x1)
* RC transmitter : [FS-i6](https://www.flysky-cn.com/fsi6)
* RC receiver : [FS-A8S](https://www.getfpv.com/flysky-fs-a8s-fs-a8s-2-4g-8ch-mini-receiver-with-ppm-i-bus-sbus-output.html) (No more production)

## 1. Feature
* Receive data  
    `RC transmitter` -> `RC receiver` -> `UART(ibus protocol)` -> `STM32F4 MCU`
* Send data (telemetry or sensors) function is not included

## 2. User Configuration
* STM32F4xx
* USART1 - PA10 (RX)

### _STM32CubeMX_
* Setting
```
Project Manager -> Code Generator -> Generated files 
-> Generate peripheral initialization as a pair of '.c/.h'files per peripheral
```
* USART1 (RX)
```
- Mode
    Mode : Asynchronous
    Hardware Flow Control (RS232) : Disable

- Configuration
    Parameter Settings
        Basic Parameters
            Baud Rate             : 115200 Bits/s
            Word Length           : 8 Bits (including Parity)
            Parity                : None
            Stop Bits             : 1
        Advanced Parameters
            Data Direction        : Receive Only
            Over Sampling         : 16 Samples

    NVIC Settings
        USART1 global interrupt   : Enabled
``` 
### _flysky_ibus.h_
```
...

#define IBUS_UART				(&huart1)
#define IBUS_UART_INSTANCE		(USART1)  
#define IBUS_USER_CHANNELS		6			// Use 6 channels

...
```

### _main.c_
```
...

#include "flysky_ibus.h"

...

...

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == IBUS_UART_INSTANCE)
	{
		IBUS_READ_CHANNEL(IBUS_USER_CHANNELS);
	}
}

...

int main(void)
{
    ...

    IBUS_INIT();

    ...
}

```

## 3. flysky ibus protocol

![image](https://user-images.githubusercontent.com/48342925/107107872-41d7f100-6877-11eb-931f-af72b5685ef4.png)

* The ibus protocol is one of RX protocols developed by Flysky
* half-duplex
* Control multiple servos and motors using a single digital line.
* New value can be read every 7ms
* The values received for each channel are between 1000 and 2000
* The ibus library requires a dedicated hardware serial (UART) port on microcontroller 
    * UART RX required
    * 115200 baud
    * 8N1

* Data frame
```
 // modified the contents in https://github.com/bmellink/IBusBM/blob/master/src/IBusBM.cpp

 supports max 14 channels in this lib 
 (with messagelength of 0x20 there is room for 14 channels)

  Example set of 32 bytes coming over the iBUS line for setting servos: 
    20 40 DB 5 DC 5 54 5 DC 5 E8 3 D0 7 D2 5 E8 3 DC 5 DC 5 DC 5 DC 5 DC 5 DC 5 DA F3
  
  Explanation
    Protocol length: 20
    Command code: 40 
    Channel 0: DB 5  -> value 0x5DB
    Channel 1: DC 5  -> value 0x5Dc
    Channel 2: 54 5  -> value 0x554
    Channel 3: DC 5  -> value 0x5DC
    Channel 4: E8 3  -> value 0x3E8
    Channel 5: D0 7  -> value 0x7D0
    Channel 6: D2 5  -> value 0x5D2
    Channel 7: E8 3  -> value 0x3E8
    Channel 8: DC 5  -> value 0x5DC
    Channel 9: DC 5  -> value 0x5DC
    Channel 10: DC 5 -> value 0x5DC
    Channel 11: DC 5 -> value 0x5DC
    Channel 12: DC 5 -> value 0x5DC
    Channel 13: DC 5 -> value 0x5DC
    Checksum: DA F3 -> value 0xF3DA
    
    Checksum value = 0xFFFF - (sum of previous 30 bytes)
 ```

## 4. Reference
https://github.com/bmellink/IBusBM  
https://www.arduino.cc/reference/en/libraries/ibusbm/  
https://youtu.be/ylp-ZKjsPiE  
https://medium.com/@werneckpaiva/how-to-read-rc-signal-with-arduino-using-flysky-ibus-73448bc924eb
https://oscarliang.com/pwm-ppm-sbus-dsm2-dsmx-sumd-difference/  
http://blog.dsp.id.au/posts/2017/10/22/flysky-ibus-protocol/