################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Queue/queue.c 

OBJS += \
./Queue/queue.o 

C_DEPS += \
./Queue/queue.d 


# Each subdirectory must supply rules for building sources it contributes
Queue/%.o Queue/%.su Queue/%.cyclo: ../Queue/%.c Queue/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/BESS/Jupiter_display/Nextion_STM32_Library" -I"D:/BESS/Jupiter_display/Nextion_Wrapper" -I"D:/BESS/Jupiter_display/Application" -I"D:/BESS/Jupiter_display/Queue" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Queue

clean-Queue:
	-$(RM) ./Queue/queue.cyclo ./Queue/queue.d ./Queue/queue.o ./Queue/queue.su

.PHONY: clean-Queue

