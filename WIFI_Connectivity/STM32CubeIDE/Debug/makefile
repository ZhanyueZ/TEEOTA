################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/ThreadX/Core/subdir.mk
-include Middlewares/NetXDuo/NX\ Core/subdir.mk
-include Middlewares/NetXDuo/Addons_BSD/subdir.mk
-include Middlewares/NetXDuo/Addons\ DNS/subdir.mk
-include Middlewares/NetXDuo/Addons\ DHCP\ Client/subdir.mk
-include Middlewares/Interfaces/Network/wifi/subdir.mk
-include Drivers/STM32H5xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/Components/mx_wifi/io_pattern/subdir.mk
-include Drivers/BSP/Components/mx_wifi/core/subdir.mk
-include Drivers/BSP/Components/mx_wifi/subdir.mk
-include Application/User/Startup/subdir.mk
-include Application/User/NetXDuo/App/subdir.mk
-include Application/User/Core/subdir.mk
-include Application/User/AZURE_RTOS/App/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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


BUILD_ARTIFACT_NAME := Nx_Network_Basics_wifi
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Nx_Network_Basics_wifi.elf \

MAP_FILES += \
Nx_Network_Basics_wifi.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Nx_Network_Basics_wifi.list \

OBJCOPY_HEX += \
Nx_Network_Basics_wifi.hex \


# All Target
all: main-build

# Main-build Target
main-build: Nx_Network_Basics_wifi.elf secondary-outputs

# Tool invocations
Nx_Network_Basics_wifi.elf Nx_Network_Basics_wifi.map: $(OBJS) $(USER_OBJS) F:\STM32_CAPSTONE\workspace\Nx_Network_Basics_wifi\STM32CubeIDE\STM32H573IIKXQ_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Nx_Network_Basics_wifi.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m33 -T"F:\STM32_CAPSTONE\workspace\Nx_Network_Basics_wifi\STM32CubeIDE\STM32H573IIKXQ_FLASH.ld" --specs=nosys.specs -Wl,-Map="Nx_Network_Basics_wifi.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Nx_Network_Basics_wifi.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Nx_Network_Basics_wifi.list"
	@echo 'Finished building: $@'
	@echo ' '

Nx_Network_Basics_wifi.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Nx_Network_Basics_wifi.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Nx_Network_Basics_wifi.elf Nx_Network_Basics_wifi.hex Nx_Network_Basics_wifi.list Nx_Network_Basics_wifi.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
