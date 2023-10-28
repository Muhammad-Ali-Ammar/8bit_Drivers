################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SERIVICES/source/calculation_functions.c 

OBJS += \
./SERIVICES/source/calculation_functions.o 

C_DEPS += \
./SERIVICES/source/calculation_functions.d 


# Each subdirectory must supply rules for building sources it contributes
SERIVICES/source/%.o: ../SERIVICES/source/%.c SERIVICES/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


