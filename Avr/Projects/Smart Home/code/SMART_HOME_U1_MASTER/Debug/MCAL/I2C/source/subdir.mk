################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/I2C/source/I2C.c \
../MCAL/I2C/source/I2C_config.c 

OBJS += \
./MCAL/I2C/source/I2C.o \
./MCAL/I2C/source/I2C_config.o 

C_DEPS += \
./MCAL/I2C/source/I2C.d \
./MCAL/I2C/source/I2C_config.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/I2C/source/%.o: ../MCAL/I2C/source/%.c MCAL/I2C/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


