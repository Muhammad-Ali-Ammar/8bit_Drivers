################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/ADC/source/ADC.c \
../MCAL/ADC/source/ADC_config.c 

OBJS += \
./MCAL/ADC/source/ADC.o \
./MCAL/ADC/source/ADC_config.o 

C_DEPS += \
./MCAL/ADC/source/ADC.d \
./MCAL/ADC/source/ADC_config.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/ADC/source/%.o: ../MCAL/ADC/source/%.c MCAL/ADC/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


