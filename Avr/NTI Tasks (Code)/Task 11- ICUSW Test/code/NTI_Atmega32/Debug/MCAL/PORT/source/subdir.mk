################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/PORT/source/PORT.c \
../MCAL/PORT/source/PORT_config.c 

OBJS += \
./MCAL/PORT/source/PORT.o \
./MCAL/PORT/source/PORT_config.o 

C_DEPS += \
./MCAL/PORT/source/PORT.d \
./MCAL/PORT/source/PORT_config.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/PORT/source/%.o: ../MCAL/PORT/source/%.c MCAL/PORT/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


