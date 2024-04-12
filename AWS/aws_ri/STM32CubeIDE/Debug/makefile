################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/tinycbor/subdir.mk
-include Middlewares/lwip/netif/subdir.mk
-include Middlewares/lwip/core/subdir.mk
-include Middlewares/lwip/apps/subdir.mk
-include Middlewares/lwip/api/subdir.mk
-include Middlewares/Unity/subdir.mk
-include Middlewares/FreeRTOS/kernel/subdir.mk
-include Middlewares/FreeRTOS/corePKCS11/subdir.mk
-include Middlewares/FreeRTOS/coreMQTT-Agent/subdir.mk
-include Middlewares/FreeRTOS/coreMQTT/subdir.mk
-include Middlewares/FreeRTOS/coreJSON/subdir.mk
-include Middlewares/FreeRTOS/backoffAlgorithm/subdir.mk
-include Middlewares/FreeRTOS/FreeRTOS-Libraries-Integration-Tests/transport_interface/subdir.mk
-include Middlewares/FreeRTOS/FreeRTOS-Libraries-Integration-Tests/pkcs11/subdir.mk
-include Middlewares/FreeRTOS/FreeRTOS-Libraries-Integration-Tests/ota/subdir.mk
-include Middlewares/FreeRTOS/FreeRTOS-Libraries-Integration-Tests/mqtt/subdir.mk
-include Middlewares/FreeRTOS/FreeRTOS-Libraries-Integration-Tests/subdir.mk
-include Middlewares/AWS/OTA/subdir.mk
-include Middlewares/AWS/IoTJobs/subdir.mk
-include Middlewares/AWS/IoTDeviceShadow/subdir.mk
-include Middlewares/AWS/IoTDeviceDefender/subdir.mk
-include Middlewares/ARM/mbedtls/subdir.mk
-include Middlewares/ARM/littlefs/subdir.mk
-include Drivers/STM32H5xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Application/User/ota_pal/subdir.mk
-include Application/User/fs/subdir.mk
-include Application/User/crypto/subdir.mk
-include Application/User/Startup/subdir.mk
-include Application/User/Core/subdir.mk
-include Application/User/Common/sys/subdir.mk
-include Application/User/Common/net/mxchip/subdir.mk
-include Application/User/Common/net/lwip_port/subdir.mk
-include Application/User/Common/net/subdir.mk
-include Application/User/Common/kvstore/subdir.mk
-include Application/User/Common/crypto/subdir.mk
-include Application/User/Common/cli/subdir.mk
-include Application/User/Common/app/ota/subdir.mk
-include Application/User/Common/app/mqtt/subdir.mk
-include Application/User/Common/app/defender/subdir.mk
-include Application/User/Common/app/subdir.mk
-include Application/User/subdir.mk
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


BUILD_ARTIFACT_NAME := STM32H573I-DK_aws_ri
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32H573I-DK_aws_ri.elf \

MAP_FILES += \
STM32H573I-DK_aws_ri.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32H573I-DK_aws_ri.list \

OBJCOPY_BIN += \
STM32H573I-DK_aws_ri.bin \


# All Target
all: main-build

# Main-build Target
main-build: STM32H573I-DK_aws_ri.elf secondary-outputs

# Tool invocations
STM32H573I-DK_aws_ri.elf STM32H573I-DK_aws_ri.map: $(OBJS) $(USER_OBJS) C:\Users\89336\STM32CubeIDE\workspace_1.13.1\en.x-cube-aws-h5-v1-0-0\STM32CubeExpansion_Cloud_AWS_H5_V1.0.0\Projects\STM32H573I-DK\aws_ri\STM32CubeIDE\STM32H573IIKXQ_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "STM32H573I-DK_aws_ri.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m33 -T"C:\Users\89336\STM32CubeIDE\workspace_1.13.1\en.x-cube-aws-h5-v1-0-0\STM32CubeExpansion_Cloud_AWS_H5_V1.0.0\Projects\STM32H573I-DK\aws_ri\STM32CubeIDE\STM32H573IIKXQ_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32H573I-DK_aws_ri.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32H573I-DK_aws_ri.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32H573I-DK_aws_ri.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32H573I-DK_aws_ri.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32H573I-DK_aws_ri.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) STM32H573I-DK_aws_ri.bin STM32H573I-DK_aws_ri.elf STM32H573I-DK_aws_ri.list STM32H573I-DK_aws_ri.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
