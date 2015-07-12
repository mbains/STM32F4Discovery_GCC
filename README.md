STM32F4Discovery GCC Template
=============================
This project allows you to use open source tools to quickly target an affordable Cortex M4 microcontroller board based on the STM32F407VGT6 from STMicroelectronics. It features a megabyte of flash, 192kb of RAM, an STLINK interface for programming/debugging, a USB interface, accelerometer and various I/O for under $15: [STM32F4 Discovery] (http://www.st.com/web/catalog/tools/FM116/SC959/SS1532/PF252419)


## Features
The project files will setup:
* Stack Allocation
* ISR Vectors
* System Initialization 
* Libc printf Retargetting via USART

## Required Software
* [gcc-arm-embedded] (https://launchpad.net/gcc-arm-embedded)
* [STM32F4xx_DSP_StdPeriph_Lib_V1.5.1] (http://www.st.com/web/en/catalog/tools/PF257901)

## Building
```
cd console_demo; make
```

## Credits
Much of the code here is based on Professor Geoffrey Brown's book [Discovering the STM32 Microcontroller] (http://www.cs.indiana.edu/~geobrown/book.pdf)
