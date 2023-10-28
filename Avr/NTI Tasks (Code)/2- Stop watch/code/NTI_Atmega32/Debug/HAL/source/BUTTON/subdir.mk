################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/source/BUTTON/BUTTON.c \
../HAL/source/BUTTON/BUTTON_config.c 

OBJS += \
./HAL/source/BUTTON/BUTTON.o \
./HAL/source/BUTTON/BUTTON_config.o 

C_DEPS += \
./HAL/source/BUTTON/BUTTON.d \
./HAL/source/BUTTON/BUTTON_config.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/source/BUTTON/%.o: ../HAL/source/BUTTON/%.c HAL/source/BUTTON/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


