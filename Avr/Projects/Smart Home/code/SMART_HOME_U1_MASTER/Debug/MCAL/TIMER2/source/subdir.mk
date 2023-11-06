################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/TIMER2/source/TIMER2.c \
../MCAL/TIMER2/source/TIMER2_config.c 

OBJS += \
./MCAL/TIMER2/source/TIMER2.o \
./MCAL/TIMER2/source/TIMER2_config.o 

C_DEPS += \
./MCAL/TIMER2/source/TIMER2.d \
./MCAL/TIMER2/source/TIMER2_config.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/TIMER2/source/%.o: ../MCAL/TIMER2/source/%.c MCAL/TIMER2/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


