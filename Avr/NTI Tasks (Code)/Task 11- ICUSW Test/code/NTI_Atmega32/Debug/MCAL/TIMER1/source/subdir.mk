################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/TIMER1/source/TIMER1.c \
../MCAL/TIMER1/source/TIMER1_config.c 

OBJS += \
./MCAL/TIMER1/source/TIMER1.o \
./MCAL/TIMER1/source/TIMER1_config.o 

C_DEPS += \
./MCAL/TIMER1/source/TIMER1.d \
./MCAL/TIMER1/source/TIMER1_config.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/TIMER1/source/%.o: ../MCAL/TIMER1/source/%.c MCAL/TIMER1/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


