################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/89336/STM32CubeIDE/workspace_1.13.1/en.x-cube-aws-h5-v1-0-0/STM32CubeExpansion_Cloud_AWS_H5_V1.0.0/Middleware/FreeRTOS/backoffAlgorithm/source/backoff_algorithm.c 

OBJS += \
./Middlewares/FreeRTOS/backoffAlgorithm/backoff_algorithm.o 

C_DEPS += \
./Middlewares/FreeRTOS/backoffAlgorithm/backoff_algorithm.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/backoffAlgorithm/backoff_algorithm.o: C:/Users/89336/STM32CubeIDE/workspace_1.13.1/en.x-cube-aws-h5-v1-0-0/STM32CubeExpansion_Cloud_AWS_H5_V1.0.0/Middleware/FreeRTOS/backoffAlgorithm/source/backoff_algorithm.c Middlewares/FreeRTOS/backoffAlgorithm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG '-DCMSIS_device_header="main.h"' -DUSE_HAL_DRIVER -DSTM32H573xx '-DLFS_CONFIG=lfs_config.h' '-DMBEDTLS_CONFIG_FILE="mbedtls_config_ntz.h"' -DUNITY_INCLUDE_CONFIG_H -c -I../../Inc -I../../Src/fs -I../../Src/ota_pal -I../../../../../Projects/Common/cli -I../../../../../Projects/Common/config -I../../../../../Projects/Common/net -I../../../../../Projects/Common/include -I../../../../../Projects/Common/net/lwip_port/include -I../../../../../Projects/Common/kvstore -I../../../../../Projects/Common/app/mqtt -I../../../../../Middleware/ARM/mbedtls/include -I../../../../../Middleware/ARM/mbedtls/library -I../../../../../Middleware/ARM/littlefs -I../../../../../Middleware/AWS/IoTDeviceDefender/source/include -I../../../../../Middleware/AWS/IoTDeviceShadow/source/include -I../../../../../Middleware/AWS/IoTJobs/source/include -I../../../../../Middleware/AWS/OTA/source/include -I../../../../../Middleware/AWS/OTA/source/portable/os -I../../../../../Middleware/FreeRTOS/backoffAlgorithm/source/include -I../../../../../Middleware/FreeRTOS/kernel/include -I../../../../../Middleware/FreeRTOS/kernel/portable/GCC/ARM_CM33_NTZ/non_secure -I../../../../../Middleware/FreeRTOS/coreJSON/source/include -I../../../../../Middleware/FreeRTOS/coreMQTT/source/include -I../../../../../Middleware/FreeRTOS/coreMQTT/source/interface -I../../../../../Middleware/FreeRTOS/coreMQTT-Agent/source/include -I../../../../../Middleware/FreeRTOS/corePKCS11/source/include -I../../../../../Middleware/FreeRTOS/corePKCS11/source/portable/os -I../../../../../Middleware/lwip/src/include -I../../../../../Middleware/pkcs11 -I../../../../../Middleware/tinycbor/src -I../../../../../Drivers/CommonIO/include -I../../../../../Drivers/CommonIO/gpio -I../../../../../Drivers/BSP/Components -I../../../../../Middleware/FreeRTOS/FreeRTOS-Libraries-Integration-Tests/src -I../../../../../Middleware/FreeRTOS/FreeRTOS-Libraries-Integration-Tests/src/common -I../../../../../Middleware/FreeRTOS/FreeRTOS-Libraries-Integration-Tests/src/mqtt -I../../../../../Middleware/FreeRTOS/FreeRTOS-Libraries-Integration-Tests/src/ota -I../../../../../Middleware/FreeRTOS/FreeRTOS-Libraries-Integration-Tests/src/pkcs11 -I../../../../../Middleware/FreeRTOS/FreeRTOS-Libraries-Integration-Tests/src/transport_interface -I../../../../../Middleware/Unity/extras/fixture/src -I../../../../../Middleware/Unity/extras/memory/src -I../../../../../Middleware/Unity/src -I../../../../../Drivers/CMSIS/Core/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../../../../../Drivers/STM32H5xx_HAL_Driver/Inc -I../../../../../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../../../../../Drivers/BSP/Components/Common -I../../../../../Drivers/BSP/STM32H573I-DK -Og -ffunction-sections -fdata-sections -mslow-flash-data -Wall -Wmissing-include-dirs -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FreeRTOS-2f-backoffAlgorithm

clean-Middlewares-2f-FreeRTOS-2f-backoffAlgorithm:
	-$(RM) ./Middlewares/FreeRTOS/backoffAlgorithm/backoff_algorithm.cyclo ./Middlewares/FreeRTOS/backoffAlgorithm/backoff_algorithm.d ./Middlewares/FreeRTOS/backoffAlgorithm/backoff_algorithm.o ./Middlewares/FreeRTOS/backoffAlgorithm/backoff_algorithm.su

.PHONY: clean-Middlewares-2f-FreeRTOS-2f-backoffAlgorithm

