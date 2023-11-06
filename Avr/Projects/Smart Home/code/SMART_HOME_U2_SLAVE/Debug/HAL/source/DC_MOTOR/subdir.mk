################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/source/DC_MOTOR/DC_MOTOR.c 

OBJS += \
./HAL/source/DC_MOTOR/DC_MOTOR.o 

C_DEPS += \
./HAL/source/DC_MOTOR/DC_MOTOR.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/source/DC_MOTOR/%.o: ../HAL/source/DC_MOTOR/%.c HAL/source/DC_MOTOR/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


