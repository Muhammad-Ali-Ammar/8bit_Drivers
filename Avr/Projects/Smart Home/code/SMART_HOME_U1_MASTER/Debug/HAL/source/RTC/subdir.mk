################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/source/RTC/RTC.c \
../HAL/source/RTC/RTC_config.c 

OBJS += \
./HAL/source/RTC/RTC.o \
./HAL/source/RTC/RTC_config.o 

C_DEPS += \
./HAL/source/RTC/RTC.d \
./HAL/source/RTC/RTC_config.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/source/RTC/%.o: ../HAL/source/RTC/%.c HAL/source/RTC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


