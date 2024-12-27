################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_ll_gpio.c \
D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_ll_rcc.c \
D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_ll_usart.c \
D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_ll_utils.c 

OBJS += \
./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_gpio.o \
./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_rcc.o \
./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_usart.o \
./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_utils.o 

C_DEPS += \
./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_gpio.d \
./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_rcc.d \
./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_usart.d \
./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_gpio.o: D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_ll_gpio.c Drivers/STM32WBxx_LL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32WB15xx -DSTM32 -DSTM32WB -DNUCLEO_WB15CC -DSTM32WB15CCUx -c -I../Inc -I/Drivers -I../../common/FreeRTOS/FreeRTOS/Source/include -I../../common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../common/STM32CubeWB/Drivers/CMSIS/Include -I../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Inc -I"../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src" -I"../../common/STM32CubeWB/Drivers/CMSIS/Device/ST/STM32WBxx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_rcc.o: D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_ll_rcc.c Drivers/STM32WBxx_LL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32WB15xx -DSTM32 -DSTM32WB -DNUCLEO_WB15CC -DSTM32WB15CCUx -c -I../Inc -I/Drivers -I../../common/FreeRTOS/FreeRTOS/Source/include -I../../common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../common/STM32CubeWB/Drivers/CMSIS/Include -I../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Inc -I"../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src" -I"../../common/STM32CubeWB/Drivers/CMSIS/Device/ST/STM32WBxx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_usart.o: D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_ll_usart.c Drivers/STM32WBxx_LL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32WB15xx -DSTM32 -DSTM32WB -DNUCLEO_WB15CC -DSTM32WB15CCUx -c -I../Inc -I/Drivers -I../../common/FreeRTOS/FreeRTOS/Source/include -I../../common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../common/STM32CubeWB/Drivers/CMSIS/Include -I../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Inc -I"../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src" -I"../../common/STM32CubeWB/Drivers/CMSIS/Device/ST/STM32WBxx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_utils.o: D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src/stm32wbxx_ll_utils.c Drivers/STM32WBxx_LL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32WB15xx -DSTM32 -DSTM32WB -DNUCLEO_WB15CC -DSTM32WB15CCUx -c -I../Inc -I/Drivers -I../../common/FreeRTOS/FreeRTOS/Source/include -I../../common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../common/STM32CubeWB/Drivers/CMSIS/Include -I../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Inc -I"../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src" -I"../../common/STM32CubeWB/Drivers/CMSIS/Device/ST/STM32WBxx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32WBxx_LL_Driver

clean-Drivers-2f-STM32WBxx_LL_Driver:
	-$(RM) ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_gpio.cyclo ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_gpio.d ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_gpio.o ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_gpio.su ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_rcc.cyclo ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_rcc.d ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_rcc.o ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_rcc.su ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_usart.cyclo ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_usart.d ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_usart.o ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_usart.su ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_utils.cyclo ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_utils.d ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_utils.o ./Drivers/STM32WBxx_LL_Driver/stm32wbxx_ll_utils.su

.PHONY: clean-Drivers-2f-STM32WBxx_LL_Driver

