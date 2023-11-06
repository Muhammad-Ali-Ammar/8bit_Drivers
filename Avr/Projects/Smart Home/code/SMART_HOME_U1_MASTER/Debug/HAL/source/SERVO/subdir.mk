################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/source/SERVO/SERVO.c \
../HAL/source/SERVO/SERVO_config.c 

OBJS += \
./HAL/source/SERVO/SERVO.o \
./HAL/source/SERVO/SERVO_config.o 

C_DEPS += \
./HAL/source/SERVO/SERVO.d \
./HAL/source/SERVO/SERVO_config.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/source/SERVO/%.o: ../HAL/source/SERVO/%.c HAL/source/SERVO/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


