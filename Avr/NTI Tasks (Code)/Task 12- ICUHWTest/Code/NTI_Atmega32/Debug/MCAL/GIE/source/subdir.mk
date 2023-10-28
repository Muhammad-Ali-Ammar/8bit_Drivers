################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/GIE/source/GIE.c \
../MCAL/GIE/source/GIE_config.c 

OBJS += \
./MCAL/GIE/source/GIE.o \
./MCAL/GIE/source/GIE_config.o 

C_DEPS += \
./MCAL/GIE/source/GIE.d \
./MCAL/GIE/source/GIE_config.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/GIE/source/%.o: ../MCAL/GIE/source/%.c MCAL/GIE/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


