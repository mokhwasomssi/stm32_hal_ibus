# stm32f4_hal_ibus

## Brief

__ibus is a Flysky RC receiver protocol__  
___TAG - `ibus`, `FLYSKY`, `UART`, `STM32 HAL`___

## Library Features
- Receive data using DMA mode
- Check data is valid
- Parsing raw data

## Dev environment  
- STM32CubeIDE
- STM32 HAL driver
- STM32F411CEU6
- FLYSKY Transmitter & Receiver
    - FS-i6, FS-A8S

## FLYSKY ibus protocol

![image](https://user-images.githubusercontent.com/48342925/107107872-41d7f100-6877-11eb-931f-af72b5685ef4.png)  
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
    - Checksum  
        - 0xFFFF - (sum of previous 30 bytes)