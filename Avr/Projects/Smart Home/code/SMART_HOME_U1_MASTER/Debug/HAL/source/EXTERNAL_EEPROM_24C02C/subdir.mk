################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/source/EXTERNAL_EEPROM_24C02C/EXTERNAL_EEPROM.c \
../HAL/source/EXTERNAL_EEPROM_24C02C/EXTERNAL_EEPROM_config.c 

OBJS += \
./HAL/source/EXTERNAL_EEPROM_24C02C/EXTERNAL_EEPROM.o \
./HAL/source/EXTERNAL_EEPROM_24C02C/EXTERNAL_EEPROM_config.o 

C_DEPS += \
./HAL/source/EXTERNAL_EEPROM_24C02C/EXTERNAL_EEPROM.d \
./HAL/source/EXTERNAL_EEPROM_24C02C/EXTERNAL_EEPROM_config.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/source/EXTERNAL_EEPROM_24C02C/%.o: ../HAL/source/EXTERNAL_EEPROM_24C02C/%.c HAL/source/EXTERNAL_EEPROM_24C02C/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


