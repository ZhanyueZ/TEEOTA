################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/app_threadx.c \
F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/main.c \
F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/stm32h5xx_hal_msp.c \
F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/stm32h5xx_hal_timebase_tim.c \
F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/stm32h5xx_it.c \
../Application/User/Core/syscalls.c \
../Application/User/Core/sysmem.c 

S_UPPER_SRCS += \
F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/tx_initialize_low_level.S 

OBJS += \
./Application/User/Core/app_threadx.o \
./Application/User/Core/main.o \
./Application/User/Core/stm32h5xx_hal_msp.o \
./Application/User/Core/stm32h5xx_hal_timebase_tim.o \
./Application/User/Core/stm32h5xx_it.o \
./Application/User/Core/syscalls.o \
./Application/User/Core/sysmem.o \
./Application/User/Core/tx_initialize_low_level.o 

S_UPPER_DEPS += \
./Application/User/Core/tx_initialize_low_level.d 

C_DEPS += \
./Application/User/Core/app_threadx.d \
./Application/User/Core/main.d \
./Application/User/Core/stm32h5xx_hal_msp.d \
./Application/User/Core/stm32h5xx_hal_timebase_tim.d \
./Application/User/Core/stm32h5xx_it.d \
./Application/User/Core/syscalls.d \
./Application/User/Core/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/app_threadx.o: F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/app_threadx.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DNX_BSD_ENABLE_DNS -D_SYS_SELECT_H -DNX_INCLUDE_USER_DEFINE_FILE -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUSE_HAL_DRIVER -DSTM32H573xx -c -I../../NetXDuo/App -I../../Core/Inc -I../../AZURE_RTOS/App -I../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/netxduo/addons/dhcp -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../Middlewares/ST/netxduo/common/inc -I../../Middlewares/ST/netxduo/ports/cortex_m33/gnu/inc -I../../Middlewares/ST/netxduo/addons/dns -I../../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/mx_wifi -I../../Middlewares/ST/netxduo/common/drivers/wifi/mxchip -I../../NetXDuo/Target -I../../Middlewares/ST/netxduo/addons/BSD -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/Core/main.o: F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/main.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DNX_BSD_ENABLE_DNS -D_SYS_SELECT_H -DNX_INCLUDE_USER_DEFINE_FILE -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUSE_HAL_DRIVER -DSTM32H573xx -c -I../../NetXDuo/App -I../../Core/Inc -I../../AZURE_RTOS/App -I../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/netxduo/addons/dhcp -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../Middlewares/ST/netxduo/common/inc -I../../Middlewares/ST/netxduo/ports/cortex_m33/gnu/inc -I../../Middlewares/ST/netxduo/addons/dns -I../../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/mx_wifi -I../../Middlewares/ST/netxduo/common/drivers/wifi/mxchip -I../../NetXDuo/Target -I../../Middlewares/ST/netxduo/addons/BSD -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/Core/stm32h5xx_hal_msp.o: F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/stm32h5xx_hal_msp.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DNX_BSD_ENABLE_DNS -D_SYS_SELECT_H -DNX_INCLUDE_USER_DEFINE_FILE -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUSE_HAL_DRIVER -DSTM32H573xx -c -I../../NetXDuo/App -I../../Core/Inc -I../../AZURE_RTOS/App -I../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/netxduo/addons/dhcp -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../Middlewares/ST/netxduo/common/inc -I../../Middlewares/ST/netxduo/ports/cortex_m33/gnu/inc -I../../Middlewares/ST/netxduo/addons/dns -I../../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/mx_wifi -I../../Middlewares/ST/netxduo/common/drivers/wifi/mxchip -I../../NetXDuo/Target -I../../Middlewares/ST/netxduo/addons/BSD -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/Core/stm32h5xx_hal_timebase_tim.o: F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/stm32h5xx_hal_timebase_tim.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DNX_BSD_ENABLE_DNS -D_SYS_SELECT_H -DNX_INCLUDE_USER_DEFINE_FILE -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUSE_HAL_DRIVER -DSTM32H573xx -c -I../../NetXDuo/App -I../../Core/Inc -I../../AZURE_RTOS/App -I../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/netxduo/addons/dhcp -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../Middlewares/ST/netxduo/common/inc -I../../Middlewares/ST/netxduo/ports/cortex_m33/gnu/inc -I../../Middlewares/ST/netxduo/addons/dns -I../../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/mx_wifi -I../../Middlewares/ST/netxduo/common/drivers/wifi/mxchip -I../../NetXDuo/Target -I../../Middlewares/ST/netxduo/addons/BSD -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/Core/stm32h5xx_it.o: F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/stm32h5xx_it.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DNX_BSD_ENABLE_DNS -D_SYS_SELECT_H -DNX_INCLUDE_USER_DEFINE_FILE -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUSE_HAL_DRIVER -DSTM32H573xx -c -I../../NetXDuo/App -I../../Core/Inc -I../../AZURE_RTOS/App -I../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/netxduo/addons/dhcp -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../Middlewares/ST/netxduo/common/inc -I../../Middlewares/ST/netxduo/ports/cortex_m33/gnu/inc -I../../Middlewares/ST/netxduo/addons/dns -I../../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/mx_wifi -I../../Middlewares/ST/netxduo/common/drivers/wifi/mxchip -I../../NetXDuo/Target -I../../Middlewares/ST/netxduo/addons/BSD -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/Core/%.o Application/User/Core/%.su Application/User/Core/%.cyclo: ../Application/User/Core/%.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DENABLE_IOT_WARNING -DNX_BSD_ENABLE_DNS -D_SYS_SELECT_H -DNX_INCLUDE_USER_DEFINE_FILE -DTX_INCLUDE_USER_DEFINE_FILE -DTX_SINGLE_MODE_NON_SECURE=1 -DUSE_HAL_DRIVER -DSTM32H573xx -c -I../../NetXDuo/App -I../../Core/Inc -I../../AZURE_RTOS/App -I../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/netxduo/addons/dhcp -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../Middlewares/ST/netxduo/common/inc -I../../Middlewares/ST/netxduo/ports/cortex_m33/gnu/inc -I../../Middlewares/ST/netxduo/addons/dns -I../../Middlewares/ST/threadx/ports/cortex_m33/gnu/inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/mx_wifi -I../../Middlewares/ST/netxduo/common/drivers/wifi/mxchip -I../../NetXDuo/Target -I../../Middlewares/ST/netxduo/addons/BSD -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/Core/tx_initialize_low_level.o: F:/STM32_CAPSTONE/workspace/Nx_Network_Basics_wifi/Core/Src/tx_initialize_low_level.S Application/User/Core/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m33 -DTX_SINGLE_MODE_NON_SECURE=1 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Application-2f-User-2f-Core

clean-Application-2f-User-2f-Core:
	-$(RM) ./Application/User/Core/app_threadx.cyclo ./Application/User/Core/app_threadx.d ./Application/User/Core/app_threadx.o ./Application/User/Core/app_threadx.su ./Application/User/Core/main.cyclo ./Application/User/Core/main.d ./Application/User/Core/main.o ./Application/User/Core/main.su ./Application/User/Core/stm32h5xx_hal_msp.cyclo ./Application/User/Core/stm32h5xx_hal_msp.d ./Application/User/Core/stm32h5xx_hal_msp.o ./Application/User/Core/stm32h5xx_hal_msp.su ./Application/User/Core/stm32h5xx_hal_timebase_tim.cyclo ./Application/User/Core/stm32h5xx_hal_timebase_tim.d ./Application/User/Core/stm32h5xx_hal_timebase_tim.o ./Application/User/Core/stm32h5xx_hal_timebase_tim.su ./Application/User/Core/stm32h5xx_it.cyclo ./Application/User/Core/stm32h5xx_it.d ./Application/User/Core/stm32h5xx_it.o ./Application/User/Core/stm32h5xx_it.su ./Application/User/Core/syscalls.cyclo ./Application/User/Core/syscalls.d ./Application/User/Core/syscalls.o ./Application/User/Core/syscalls.su ./Application/User/Core/sysmem.cyclo ./Application/User/Core/sysmem.d ./Application/User/Core/sysmem.o ./Application/User/Core/sysmem.su ./Application/User/Core/tx_initialize_low_level.d ./Application/User/Core/tx_initialize_low_level.o

.PHONY: clean-Application-2f-User-2f-Core

