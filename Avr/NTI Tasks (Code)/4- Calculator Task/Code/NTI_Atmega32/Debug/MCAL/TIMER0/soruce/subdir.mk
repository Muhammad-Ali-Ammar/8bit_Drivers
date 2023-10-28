################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/TIMER0/soruce/TIMER.c \
../MCAL/TIMER0/soruce/TIMER0_config.c 

OBJS += \
./MCAL/TIMER0/soruce/TIMER.o \
./MCAL/TIMER0/soruce/TIMER0_config.o 

C_DEPS += \
./MCAL/TIMER0/soruce/TIMER.d \
./MCAL/TIMER0/soruce/TIMER0_config.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/TIMER0/soruce/%.o: ../MCAL/TIMER0/soruce/%.c MCAL/TIMER0/soruce/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


