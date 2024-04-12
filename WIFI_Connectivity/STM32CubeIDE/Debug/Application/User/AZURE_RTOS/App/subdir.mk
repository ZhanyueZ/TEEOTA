################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/AZURE_RTOS/App/app_azure_rtos.c 

OBJS += \
./Application/User/AZURE_RTOS/App/app_azure_rtos.o 

C_DEPS += \
./Application/User/AZURE_RTOS/App/app_azure_rtos.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/AZURE_RTOS/App/app_azure_rtos.o: F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/AZURE_RTOS/App/app_azure_rtos.c Application/User/AZURE_RTOS/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DNX_BSD_ENABLE_DNS -D_SYS_SELECT_H -DNX_INCLUDE_USER_DEFINE_FILE -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUSE_HAL_DRIVER -DSTM32H573xx -c -I../../NetXDuo/App -I"F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/STM32CubeIDE/Application/User/Inc" -I../../Core/Inc -I../../AZURE_RTOS/App -I../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/netxduo/addons/dhcp -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../Middlewares/ST/netxduo/common/inc -I../../Middlewares/ST/netxduo/ports/cortex_m33/gnu/inc -I../../Middlewares/ST/netxduo/addons/dns -I../../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/mx_wifi -I../../Middlewares/ST/netxduo/common/drivers/wifi/mxchip -I../../NetXDuo/Target -I../../Middlewares/ST/netxduo/addons/BSD -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-AZURE_RTOS-2f-App

clean-Application-2f-User-2f-AZURE_RTOS-2f-App:
	-$(RM) ./Application/User/AZURE_RTOS/App/app_azure_rtos.cyclo ./Application/User/AZURE_RTOS/App/app_azure_rtos.d ./Application/User/AZURE_RTOS/App/app_azure_rtos.o ./Application/User/AZURE_RTOS/App/app_azure_rtos.su

.PHONY: clean-Application-2f-User-2f-AZURE_RTOS-2f-App

