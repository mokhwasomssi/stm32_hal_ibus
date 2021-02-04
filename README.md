# stm32f4_hal_flysky_ibus

__stm32f4 library for flysky RC IBUS protocol using hardware UART__

## 0. Development environment  
* IDE : [STM32Cubeide (STM32Cube HAL)](https://www.st.com/en/development-tools/stm32cubeide)
* MCU : [WeAct Black Pill V3.0 (STM32F411CEU6)](https://github.com/WeActTC/MiniF4-STM32F4x1)
* RC transmitter : [FS-i6](https://www.flysky-cn.com/fsi6)
* RC receiver : [FS-A8S](https://www.getfpv.com/flysky-fs-a8s-fs-a8s-2-4g-8ch-mini-receiver-with-ppm-i-bus-sbus-output.html) (No more production)





## 1. Feature

...


## 2. User Configuration
### STM32CubeMX
* USART1
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

## 3. flysky ibus protocol

Data is transmitted at 115200bps and a new value can be read every 7ms.  
It will return a value between 1000 and 2000 if there is any data  
it will return 0, if the transmitter (the remote control) is off.  
Flysky iBUS uses a half-duplex asynchronous protocol format at 115200 baud.


## 4. Reference
https://github.com/bmellink/IBusBM  
https://www.arduino.cc/reference/en/libraries/ibusbm/  
https://youtu.be/ylp-ZKjsPiE