################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Nextion_Wrapper/nextion_wrapper.c 

OBJS += \
./Nextion_Wrapper/nextion_wrapper.o 

C_DEPS += \
./Nextion_Wrapper/nextion_wrapper.d 


# Each subdirectory must supply rules for building sources it contributes
Nextion_Wrapper/%.o Nextion_Wrapper/%.su Nextion_Wrapper/%.cyclo: ../Nextion_Wrapper/%.c Nextion_Wrapper/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/BESS/Jupiter_display/Nextion_STM32_Library" -I"D:/BESS/Jupiter_display/Nextion_Wrapper" -I"D:/BESS/Jupiter_display/Application" -I"D:/BESS/Jupiter_display/Queue" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Nextion_Wrapper

clean-Nextion_Wrapper:
	-$(RM) ./Nextion_Wrapper/nextion_wrapper.cyclo ./Nextion_Wrapper/nextion_wrapper.d ./Nextion_Wrapper/nextion_wrapper.o ./Nextion_Wrapper/nextion_wrapper.su

.PHONY: clean-Nextion_Wrapper

