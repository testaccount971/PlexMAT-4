################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Fluid_Sense.c \
../Core/Src/Nozzle_Motor_Z.c \
../Core/Src/Probe_Motor_Z.c \
../Core/Src/Rocking_Motor.c \
../Core/Src/Syringe_Motor.c \
../Core/Src/X_Motor.c \
../Core/Src/command_processor.c \
../Core/Src/commands.c \
../Core/Src/define.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/pump.c \
../Core/Src/sensors.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c \
../Core/Src/valves.c 

OBJS += \
./Core/Src/Fluid_Sense.o \
./Core/Src/Nozzle_Motor_Z.o \
./Core/Src/Probe_Motor_Z.o \
./Core/Src/Rocking_Motor.o \
./Core/Src/Syringe_Motor.o \
./Core/Src/X_Motor.o \
./Core/Src/command_processor.o \
./Core/Src/commands.o \
./Core/Src/define.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/pump.o \
./Core/Src/sensors.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o \
./Core/Src/valves.o 

C_DEPS += \
./Core/Src/Fluid_Sense.d \
./Core/Src/Nozzle_Motor_Z.d \
./Core/Src/Probe_Motor_Z.d \
./Core/Src/Rocking_Motor.d \
./Core/Src/Syringe_Motor.d \
./Core/Src/X_Motor.d \
./Core/Src/command_processor.d \
./Core/Src/commands.d \
./Core/Src/define.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/pump.d \
./Core/Src/sensors.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d \
./Core/Src/valves.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Fluid_Sense.cyclo ./Core/Src/Fluid_Sense.d ./Core/Src/Fluid_Sense.o ./Core/Src/Fluid_Sense.su ./Core/Src/Nozzle_Motor_Z.cyclo ./Core/Src/Nozzle_Motor_Z.d ./Core/Src/Nozzle_Motor_Z.o ./Core/Src/Nozzle_Motor_Z.su ./Core/Src/Probe_Motor_Z.cyclo ./Core/Src/Probe_Motor_Z.d ./Core/Src/Probe_Motor_Z.o ./Core/Src/Probe_Motor_Z.su ./Core/Src/Rocking_Motor.cyclo ./Core/Src/Rocking_Motor.d ./Core/Src/Rocking_Motor.o ./Core/Src/Rocking_Motor.su ./Core/Src/Syringe_Motor.cyclo ./Core/Src/Syringe_Motor.d ./Core/Src/Syringe_Motor.o ./Core/Src/Syringe_Motor.su ./Core/Src/X_Motor.cyclo ./Core/Src/X_Motor.d ./Core/Src/X_Motor.o ./Core/Src/X_Motor.su ./Core/Src/command_processor.cyclo ./Core/Src/command_processor.d ./Core/Src/command_processor.o ./Core/Src/command_processor.su ./Core/Src/commands.cyclo ./Core/Src/commands.d ./Core/Src/commands.o ./Core/Src/commands.su ./Core/Src/define.cyclo ./Core/Src/define.d ./Core/Src/define.o ./Core/Src/define.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pump.cyclo ./Core/Src/pump.d ./Core/Src/pump.o ./Core/Src/pump.su ./Core/Src/sensors.cyclo ./Core/Src/sensors.d ./Core/Src/sensors.o ./Core/Src/sensors.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/valves.cyclo ./Core/Src/valves.d ./Core/Src/valves.o ./Core/Src/valves.su

.PHONY: clean-Core-2f-Src

