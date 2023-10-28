################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/source/LCD/LCD.c \
../HAL/source/LCD/LCD_config.c 

OBJS += \
./HAL/source/LCD/LCD.o \
./HAL/source/LCD/LCD_config.o 

C_DEPS += \
./HAL/source/LCD/LCD.d \
./HAL/source/LCD/LCD_config.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/source/LCD/%.o: ../HAL/source/LCD/%.c HAL/source/LCD/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


