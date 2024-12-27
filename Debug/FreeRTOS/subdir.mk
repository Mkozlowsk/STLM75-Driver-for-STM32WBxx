################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/FreeRTOS/FreeRTOS/Source/portable/MemMang/heap_3.c \
D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/FreeRTOS/FreeRTOS/Source/list.c \
D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/FreeRTOS/FreeRTOS/Source/queue.c \
D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/FreeRTOS/FreeRTOS/Source/tasks.c \
D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/FreeRTOS/FreeRTOS/Source/timers.c 

OBJS += \
./FreeRTOS/heap_3.o \
./FreeRTOS/list.o \
./FreeRTOS/port.o \
./FreeRTOS/queue.o \
./FreeRTOS/tasks.o \
./FreeRTOS/timers.o 

C_DEPS += \
./FreeRTOS/heap_3.d \
./FreeRTOS/list.d \
./FreeRTOS/port.d \
./FreeRTOS/queue.d \
./FreeRTOS/tasks.d \
./FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/heap_3.o: D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/FreeRTOS/FreeRTOS/Source/portable/MemMang/heap_3.c FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32WB15xx -DSTM32 -DSTM32WB -DNUCLEO_WB15CC -DSTM32WB15CCUx -c -I../Inc -I/Drivers -I../../common/FreeRTOS/FreeRTOS/Source/include -I../../common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../common/STM32CubeWB/Drivers/CMSIS/Include -I../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Inc -I"../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src" -I"../../common/STM32CubeWB/Drivers/CMSIS/Device/ST/STM32WBxx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
FreeRTOS/list.o: D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/FreeRTOS/FreeRTOS/Source/list.c FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32WB15xx -DSTM32 -DSTM32WB -DNUCLEO_WB15CC -DSTM32WB15CCUx -c -I../Inc -I/Drivers -I../../common/FreeRTOS/FreeRTOS/Source/include -I../../common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../common/STM32CubeWB/Drivers/CMSIS/Include -I../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Inc -I"../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src" -I"../../common/STM32CubeWB/Drivers/CMSIS/Device/ST/STM32WBxx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
FreeRTOS/port.o: D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32WB15xx -DSTM32 -DSTM32WB -DNUCLEO_WB15CC -DSTM32WB15CCUx -c -I../Inc -I/Drivers -I../../common/FreeRTOS/FreeRTOS/Source/include -I../../common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../common/STM32CubeWB/Drivers/CMSIS/Include -I../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Inc -I"../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src" -I"../../common/STM32CubeWB/Drivers/CMSIS/Device/ST/STM32WBxx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
FreeRTOS/queue.o: D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/FreeRTOS/FreeRTOS/Source/queue.c FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32WB15xx -DSTM32 -DSTM32WB -DNUCLEO_WB15CC -DSTM32WB15CCUx -c -I../Inc -I/Drivers -I../../common/FreeRTOS/FreeRTOS/Source/include -I../../common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../common/STM32CubeWB/Drivers/CMSIS/Include -I../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Inc -I"../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src" -I"../../common/STM32CubeWB/Drivers/CMSIS/Device/ST/STM32WBxx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
FreeRTOS/tasks.o: D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/FreeRTOS/FreeRTOS/Source/tasks.c FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32WB15xx -DSTM32 -DSTM32WB -DNUCLEO_WB15CC -DSTM32WB15CCUx -c -I../Inc -I/Drivers -I../../common/FreeRTOS/FreeRTOS/Source/include -I../../common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../common/STM32CubeWB/Drivers/CMSIS/Include -I../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Inc -I"../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src" -I"../../common/STM32CubeWB/Drivers/CMSIS/Device/ST/STM32WBxx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
FreeRTOS/timers.o: D:/Studia/UIOM/uiom_2024l_jml_mk_projekty/common/FreeRTOS/FreeRTOS/Source/timers.c FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32WB15xx -DSTM32 -DSTM32WB -DNUCLEO_WB15CC -DSTM32WB15CCUx -c -I../Inc -I/Drivers -I../../common/FreeRTOS/FreeRTOS/Source/include -I../../common/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../common/STM32CubeWB/Drivers/CMSIS/Include -I../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Inc -I"../../common/STM32CubeWB/Drivers/STM32WBxx_HAL_Driver/Src" -I"../../common/STM32CubeWB/Drivers/CMSIS/Device/ST/STM32WBxx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS

clean-FreeRTOS:
	-$(RM) ./FreeRTOS/heap_3.cyclo ./FreeRTOS/heap_3.d ./FreeRTOS/heap_3.o ./FreeRTOS/heap_3.su ./FreeRTOS/list.cyclo ./FreeRTOS/list.d ./FreeRTOS/list.o ./FreeRTOS/list.su ./FreeRTOS/port.cyclo ./FreeRTOS/port.d ./FreeRTOS/port.o ./FreeRTOS/port.su ./FreeRTOS/queue.cyclo ./FreeRTOS/queue.d ./FreeRTOS/queue.o ./FreeRTOS/queue.su ./FreeRTOS/tasks.cyclo ./FreeRTOS/tasks.d ./FreeRTOS/tasks.o ./FreeRTOS/tasks.su ./FreeRTOS/timers.cyclo ./FreeRTOS/timers.d ./FreeRTOS/timers.o ./FreeRTOS/timers.su

.PHONY: clean-FreeRTOS

