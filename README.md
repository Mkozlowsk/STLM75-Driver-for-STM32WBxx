# STLM75-Driver-for-STM32WBxx
Driver library for a STLM75 temperature sensor and thermal watchdog. Based on a STM32WBxx microcontroller and custom I2C library.
In progress / Needs revision

## Project Description
The project implements a STLM75 thermomether driver. Relevant files include Inc/stlm75Drv.h and Src/stlm75Drv.c. I2C communication is provided by function I2CDrv_Transaction, which can be replaced by a different I2C interface.
Provided example uses STM32WB Low-level libraries and FreeRtos (Not finished).

### Features
- STLM75 Driver
- Example for STM32WB

### Technologies and Tools
- **CubeIDE**  
- **C**  
- **STM32WBxx**
