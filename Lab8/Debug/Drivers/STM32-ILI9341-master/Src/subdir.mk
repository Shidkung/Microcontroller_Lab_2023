################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32-ILI9341-master/Src/gpio.c \
../Drivers/STM32-ILI9341-master/Src/main.c \
../Drivers/STM32-ILI9341-master/Src/rng.c \
../Drivers/STM32-ILI9341-master/Src/spi.c \
../Drivers/STM32-ILI9341-master/Src/stm32f7xx_hal_msp.c \
../Drivers/STM32-ILI9341-master/Src/stm32f7xx_it.c \
../Drivers/STM32-ILI9341-master/Src/tim.c \
../Drivers/STM32-ILI9341-master/Src/usart.c 

OBJS += \
./Drivers/STM32-ILI9341-master/Src/gpio.o \
./Drivers/STM32-ILI9341-master/Src/main.o \
./Drivers/STM32-ILI9341-master/Src/rng.o \
./Drivers/STM32-ILI9341-master/Src/spi.o \
./Drivers/STM32-ILI9341-master/Src/stm32f7xx_hal_msp.o \
./Drivers/STM32-ILI9341-master/Src/stm32f7xx_it.o \
./Drivers/STM32-ILI9341-master/Src/tim.o \
./Drivers/STM32-ILI9341-master/Src/usart.o 

C_DEPS += \
./Drivers/STM32-ILI9341-master/Src/gpio.d \
./Drivers/STM32-ILI9341-master/Src/main.d \
./Drivers/STM32-ILI9341-master/Src/rng.d \
./Drivers/STM32-ILI9341-master/Src/spi.d \
./Drivers/STM32-ILI9341-master/Src/stm32f7xx_hal_msp.d \
./Drivers/STM32-ILI9341-master/Src/stm32f7xx_it.d \
./Drivers/STM32-ILI9341-master/Src/tim.d \
./Drivers/STM32-ILI9341-master/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32-ILI9341-master/Src/%.o Drivers/STM32-ILI9341-master/Src/%.su Drivers/STM32-ILI9341-master/Src/%.cyclo: ../Drivers/STM32-ILI9341-master/Src/%.c Drivers/STM32-ILI9341-master/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/User/Desktop/MAD_2023/Lab8/Drivers/STM32-ILI9341-master" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32-2d-ILI9341-2d-master-2f-Src

clean-Drivers-2f-STM32-2d-ILI9341-2d-master-2f-Src:
	-$(RM) ./Drivers/STM32-ILI9341-master/Src/gpio.cyclo ./Drivers/STM32-ILI9341-master/Src/gpio.d ./Drivers/STM32-ILI9341-master/Src/gpio.o ./Drivers/STM32-ILI9341-master/Src/gpio.su ./Drivers/STM32-ILI9341-master/Src/main.cyclo ./Drivers/STM32-ILI9341-master/Src/main.d ./Drivers/STM32-ILI9341-master/Src/main.o ./Drivers/STM32-ILI9341-master/Src/main.su ./Drivers/STM32-ILI9341-master/Src/rng.cyclo ./Drivers/STM32-ILI9341-master/Src/rng.d ./Drivers/STM32-ILI9341-master/Src/rng.o ./Drivers/STM32-ILI9341-master/Src/rng.su ./Drivers/STM32-ILI9341-master/Src/spi.cyclo ./Drivers/STM32-ILI9341-master/Src/spi.d ./Drivers/STM32-ILI9341-master/Src/spi.o ./Drivers/STM32-ILI9341-master/Src/spi.su ./Drivers/STM32-ILI9341-master/Src/stm32f7xx_hal_msp.cyclo ./Drivers/STM32-ILI9341-master/Src/stm32f7xx_hal_msp.d ./Drivers/STM32-ILI9341-master/Src/stm32f7xx_hal_msp.o ./Drivers/STM32-ILI9341-master/Src/stm32f7xx_hal_msp.su ./Drivers/STM32-ILI9341-master/Src/stm32f7xx_it.cyclo ./Drivers/STM32-ILI9341-master/Src/stm32f7xx_it.d ./Drivers/STM32-ILI9341-master/Src/stm32f7xx_it.o ./Drivers/STM32-ILI9341-master/Src/stm32f7xx_it.su ./Drivers/STM32-ILI9341-master/Src/tim.cyclo ./Drivers/STM32-ILI9341-master/Src/tim.d ./Drivers/STM32-ILI9341-master/Src/tim.o ./Drivers/STM32-ILI9341-master/Src/tim.su ./Drivers/STM32-ILI9341-master/Src/usart.cyclo ./Drivers/STM32-ILI9341-master/Src/usart.d ./Drivers/STM32-ILI9341-master/Src/usart.o ./Drivers/STM32-ILI9341-master/Src/usart.su

.PHONY: clean-Drivers-2f-STM32-2d-ILI9341-2d-master-2f-Src

