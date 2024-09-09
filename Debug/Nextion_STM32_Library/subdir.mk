################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Nextion_STM32_Library/Nextion.c 

OBJS += \
./Nextion_STM32_Library/Nextion.o 

C_DEPS += \
./Nextion_STM32_Library/Nextion.d 


# Each subdirectory must supply rules for building sources it contributes
Nextion_STM32_Library/%.o Nextion_STM32_Library/%.su Nextion_STM32_Library/%.cyclo: ../Nextion_STM32_Library/%.c Nextion_STM32_Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/BESS/Jupiter_display/Nextion_STM32_Library" -I"D:/BESS/Jupiter_display/Nextion_Wrapper" -I"D:/BESS/Jupiter_display/Application" -I"D:/BESS/Jupiter_display/Queue" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Nextion_STM32_Library

clean-Nextion_STM32_Library:
	-$(RM) ./Nextion_STM32_Library/Nextion.cyclo ./Nextion_STM32_Library/Nextion.d ./Nextion_STM32_Library/Nextion.o ./Nextion_STM32_Library/Nextion.su

.PHONY: clean-Nextion_STM32_Library

