################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/USART/source/USART.c \
../MCAL/USART/source/USART_config.c 

OBJS += \
./MCAL/USART/source/USART.o \
./MCAL/USART/source/USART_config.o 

C_DEPS += \
./MCAL/USART/source/USART.d \
./MCAL/USART/source/USART_config.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/USART/source/%.o: ../MCAL/USART/source/%.c MCAL/USART/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


