################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/system_stm32h5xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32h5xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32h5xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32h5xx.o: F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/system_stm32h5xx.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DNX_BSD_ENABLE_DNS -D_SYS_SELECT_H -DNX_INCLUDE_USER_DEFINE_FILE -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUSE_HAL_DRIVER -DSTM32H573xx -c -I../../NetXDuo/App -I../../Core/Inc -I../../AZURE_RTOS/App -I../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/netxduo/addons/dhcp -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../Middlewares/ST/netxduo/common/inc -I../../Middlewares/ST/netxduo/ports/cortex_m33/gnu/inc -I../../Middlewares/ST/netxduo/addons/dns -I../../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/mx_wifi -I../../Middlewares/ST/netxduo/common/drivers/wifi/mxchip -I../../NetXDuo/Target -I../../Middlewares/ST/netxduo/addons/BSD -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS

clean-Drivers-2f-CMSIS:
	-$(RM) ./Drivers/CMSIS/system_stm32h5xx.cyclo ./Drivers/CMSIS/system_stm32h5xx.d ./Drivers/CMSIS/system_stm32h5xx.o ./Drivers/CMSIS/system_stm32h5xx.su

.PHONY: clean-Drivers-2f-CMSIS

