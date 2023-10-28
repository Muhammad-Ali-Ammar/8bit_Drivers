################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/source/KEYPAD/KEYPAD.c \
../HAL/source/KEYPAD/KEYPAD_config.c 

OBJS += \
./HAL/source/KEYPAD/KEYPAD.o \
./HAL/source/KEYPAD/KEYPAD_config.o 

C_DEPS += \
./HAL/source/KEYPAD/KEYPAD.d \
./HAL/source/KEYPAD/KEYPAD_config.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/source/KEYPAD/%.o: ../HAL/source/KEYPAD/%.c HAL/source/KEYPAD/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


