################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/I2CDrv.c \
../Src/MainDev.c \
../Src/WeatherDrv.c \
../Src/main.c \
../Src/stlm75Drv.c \
../Src/stm32wbxx_it.c \
../Src/stream_buffer.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32wbxx.c 

OBJS += \
./Src/I2CDrv.o \
./Src/MainDev.o \
./Src/WeatherDrv.o \
./Src/main.o \
./Src/stlm75Drv.o \
./Src/stm32wbxx_it.o \
./Src/stream_buffer.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32wbxx.o 

C_DEPS += \
./Src/I2CDrv.d \
./Src/MainDev.d \
./Src/WeatherDrv.d \
./Src/main.d \
./Src/stlm75Drv.d \
./Src/stm32wbxx_it.d \
./Src/stream_buffer.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32wbxx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32WB15xx -DSTM32 -DSTM32WB -DNUCLEO_WB15CC -DSTM32WB15CCUx -c -I../Inc -I/Drivers -I../../common/FreeRTOS/FreeRTOS/Source/include -I../../common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../common/STM32CubeWB/Drivers/CMSIS/Include -I../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Inc -I"../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src" -I"../../common/STM32CubeWB/Drivers/CMSIS/Device/ST/STM32WBxx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/I2CDrv.cyclo ./Src/I2CDrv.d ./Src/I2CDrv.o ./Src/I2CDrv.su ./Src/MainDev.cyclo ./Src/MainDev.d ./Src/MainDev.o ./Src/MainDev.su ./Src/WeatherDrv.cyclo ./Src/WeatherDrv.d ./Src/WeatherDrv.o ./Src/WeatherDrv.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/stlm75Drv.cyclo ./Src/stlm75Drv.d ./Src/stlm75Drv.o ./Src/stlm75Drv.su ./Src/stm32wbxx_it.cyclo ./Src/stm32wbxx_it.d ./Src/stm32wbxx_it.o ./Src/stm32wbxx_it.su ./Src/stream_buffer.cyclo ./Src/stream_buffer.d ./Src/stream_buffer.o ./Src/stream_buffer.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32wbxx.cyclo ./Src/system_stm32wbxx.d ./Src/system_stm32wbxx.o ./Src/system_stm32wbxx.su

.PHONY: clean-Src

