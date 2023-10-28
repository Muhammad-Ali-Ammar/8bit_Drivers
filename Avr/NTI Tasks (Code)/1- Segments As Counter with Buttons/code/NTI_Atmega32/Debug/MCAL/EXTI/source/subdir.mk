################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/EXTI/source/EXTI.c \
../MCAL/EXTI/source/EXTI_config.c 

OBJS += \
./MCAL/EXTI/source/EXTI.o \
./MCAL/EXTI/source/EXTI_config.o 

C_DEPS += \
./MCAL/EXTI/source/EXTI.d \
./MCAL/EXTI/source/EXTI_config.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/EXTI/source/%.o: ../MCAL/EXTI/source/%.c MCAL/EXTI/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


