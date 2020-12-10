################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Device_driver/drivers/LT542(c.a.).c \
../Device_driver/drivers/adlx345.c \
../Device_driver/drivers/basic_timer.c \
../Device_driver/drivers/dma.c \
../Device_driver/drivers/gpio.c \
../Device_driver/drivers/i2c.c \
../Device_driver/drivers/random_no_gen.c \
../Device_driver/drivers/rcc.c \
../Device_driver/drivers/spi.c \
../Device_driver/drivers/usart.c 

OBJS += \
./Device_driver/drivers/LT542(c.a.).o \
./Device_driver/drivers/adlx345.o \
./Device_driver/drivers/basic_timer.o \
./Device_driver/drivers/dma.o \
./Device_driver/drivers/gpio.o \
./Device_driver/drivers/i2c.o \
./Device_driver/drivers/random_no_gen.o \
./Device_driver/drivers/rcc.o \
./Device_driver/drivers/spi.o \
./Device_driver/drivers/usart.o 

C_DEPS += \
./Device_driver/drivers/LT542(c.a.).d \
./Device_driver/drivers/adlx345.d \
./Device_driver/drivers/basic_timer.d \
./Device_driver/drivers/dma.d \
./Device_driver/drivers/gpio.d \
./Device_driver/drivers/i2c.d \
./Device_driver/drivers/random_no_gen.d \
./Device_driver/drivers/rcc.d \
./Device_driver/drivers/spi.d \
./Device_driver/drivers/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Device_driver/drivers/LT542(c.a.).o: ../Device_driver/drivers/LT542(c.a.).c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407G_DISC1 -DDEBUG -I"C:/Ac6/SystemWorkbench/workspace/my_home_project/Device_driver/headers" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"Device_driver/drivers/LT542(c.a.).d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Device_driver/drivers/%.o: ../Device_driver/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407G_DISC1 -DDEBUG -I"C:/Ac6/SystemWorkbench/workspace/my_home_project/Device_driver/headers" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


