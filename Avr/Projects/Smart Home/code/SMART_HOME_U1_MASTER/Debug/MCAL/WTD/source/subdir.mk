################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/WTD/source/WDT.c \
../MCAL/WTD/source/WDT_config.c 

OBJS += \
./MCAL/WTD/source/WDT.o \
./MCAL/WTD/source/WDT_config.o 

C_DEPS += \
./MCAL/WTD/source/WDT.d \
./MCAL/WTD/source/WDT_config.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/WTD/source/%.o: ../MCAL/WTD/source/%.c MCAL/WTD/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


