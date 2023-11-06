################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SERIVICES/source/subdir.mk
-include MCAL/USART/source/subdir.mk
-include MCAL/TIMER1/source/subdir.mk
-include MCAL/TIMER0/soruce/subdir.mk
-include MCAL/SPI/source/subdir.mk
-include MCAL/PORT/source/subdir.mk
-include MCAL/I2C/source/subdir.mk
-include MCAL/GIE/source/subdir.mk
-include MCAL/DIO/source/subdir.mk
-include HAL/source/SERVO/subdir.mk
-include HAL/source/RTC/subdir.mk
-include HAL/source/LCD/subdir.mk
-include HAL/source/KEYPAD/subdir.mk
-include HAL/source/EXTERNAL_EEPROM_24C02C/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := SMART_HOME_U1_MASTER
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
SMART_HOME_U1_MASTER.lss \

FLASH_IMAGE += \
SMART_HOME_U1_MASTER.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: main-build

# Main-build Target
main-build: SMART_HOME_U1_MASTER.elf secondary-outputs

# Tool invocations
SMART_HOME_U1_MASTER.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SMART_HOME_U1_MASTER.map -mmcu=atmega32 -o "SMART_HOME_U1_MASTER.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SMART_HOME_U1_MASTER.lss: SMART_HOME_U1_MASTER.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SMART_HOME_U1_MASTER.elf  >"SMART_HOME_U1_MASTER.lss"
	@echo 'Finished building: $@'
	@echo ' '

SMART_HOME_U1_MASTER.hex: SMART_HOME_U1_MASTER.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SMART_HOME_U1_MASTER.elf  "SMART_HOME_U1_MASTER.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SMART_HOME_U1_MASTER.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 SMART_HOME_U1_MASTER.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SMART_HOME_U1_MASTER.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents main-build

-include ../makefile.targets
