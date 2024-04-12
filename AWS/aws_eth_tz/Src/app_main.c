/*
 * FreeRTOS STM32 Reference Integration
 *
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#include "logging_levels.h"

#define LOG_LEVEL LOG_DEBUG
#include "logging.h"
#include "main.h"
#include "sys_evt.h"
#include "FreeRTOS.h"
#include "task.h"
#include "kvstore.h"
#include "psa/crypto.h"

#include "cli.h"
#include "test_execution_config.h"
#include "semphr.h"
#include "stdlib.h" /* rand() */

/* Definition for Qualification Test */
#if ( DEVICE_ADVISOR_TEST_ENABLED == 1 ) || ( MQTT_TEST_ENABLED == 1 ) || ( TRANSPORT_INTERFACE_TEST_ENABLED == 1 ) || \
    ( OTA_PAL_TEST_ENABLED == 1 ) || ( OTA_E2E_TEST_ENABLED == 1 ) || ( CORE_PKCS11_TEST_ENABLED == 1 )
#define DEMO_QUALIFICATION_TEST    ( 1 )

#else
#define DEMO_QUALIFICATION_TEST    ( 0 )
#endif /* ( DEVICE_ADVISOR_TEST_ENABLED == 1 ) || ( MQTT_TEST_ENABLED == 1 ) || ( TRANSPORT_INTERFACE_TEST_ENABLED == 1 ) || \
        * ( OTA_PAL_TEST_ENABLED == 1 ) || ( OTA_E2E_TEST_ENABLED == 1 ) || ( CORE_PKCS11_TEST_ENABLED == 1 ) */

#define SRAM3_NS_SIZE (128 * 1024)

EventGroupHandle_t xSystemEvents = NULL;

static void vHeartbeatTask( void * pvParameters )
{
    ( void ) pvParameters;

    HAL_GPIO_WritePin( LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET );
    HAL_GPIO_WritePin( LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET );

    while(1)
    {
        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
        HAL_GPIO_TogglePin( LED_GREEN_GPIO_Port, LED_GREEN_Pin );
        HAL_GPIO_TogglePin( LED_RED_GPIO_Port, LED_RED_Pin );
    }
}

extern void net_main( void * pvParameters );
extern void vMQTTAgentTask( void * );
extern void vSensorPublishTask( void * );
extern void vShadowDeviceTask( void * );
extern void vOTAUpdateTask( void * pvParam );
extern void vDefenderAgentTask( void * );
extern void vSensorDataPublishTask( void * pvParameters );
extern void vShadowUpdateTask( void * pvParameters );
#if DEMO_QUALIFICATION_TEST
extern void run_qualification_main( void * );
#endif /* DEMO_QUALIFICATION_TEST */

extern void otaPal_EarlyInit( void );
extern void vPopulateDeviceIdentity( void );
extern void tfm_ns_interface_init( void );

void vInitTask( void * pvArgs )
{
    BaseType_t xResult;

    ( void ) pvArgs;

    /* Initialize PSA crypto api */
    psa_crypto_init();

    KVStore_init();
#ifndef USE_CUSTOM_TLS_KEY
    vPopulateDeviceIdentity();
#endif

    xResult = xTaskCreate( Task_CLI, "cli", 2048, NULL, 10, NULL );
    configASSERT( xResult == pdTRUE );

    xResult = xTaskCreate( vHeartbeatTask, "Heartbeat", 128, NULL, tskIDLE_PRIORITY + 24, NULL );
    configASSERT( xResult == pdTRUE );

    xResult = xTaskCreate( &net_main, "EthNet", 512, NULL, 23, NULL );
    configASSERT( xResult == pdTRUE );

#if DEMO_QUALIFICATION_TEST
    xResult = xTaskCreate( run_qualification_main, "QualTest", 4096, NULL, 10, NULL );
    configASSERT( xResult == pdTRUE );
#else
    xResult = xTaskCreate( vMQTTAgentTask, "MQTTAgent", 1024, NULL, 10, NULL );
    configASSERT( xResult == pdTRUE );

    xResult = xTaskCreate( vOTAUpdateTask, "OTAUpdate", 512, NULL, tskIDLE_PRIORITY + 2, NULL );
    configASSERT( xResult == pdTRUE );

    xResult = xTaskCreate( vSensorPublishTask, "Sense", 512, NULL, 6, NULL );
    configASSERT( xResult == pdTRUE );

    xResult = xTaskCreate( vShadowDeviceTask, "ShadowDevice", 512, NULL, 5, NULL );
    configASSERT( xResult == pdTRUE );

    xResult = xTaskCreate( vDefenderAgentTask, "AWSDefender", 512 , NULL, 5, NULL );
    configASSERT( xResult == pdTRUE );
#endif /* DEMO_QUALIFICATION_TEST */

    while( 1 )
    {
        vTaskSuspend( NULL );
    }
}

static uint32_t ulCsrFlags = 0;

static void vDetermineResetSource()
{
    const char * pcResetSource = NULL;

    ulCsrFlags &= ( RCC_RSR_PINRSTF |
    		RCC_RSR_BORRSTF | RCC_RSR_SFTRSTF |
			RCC_RSR_IWDGRSTF | RCC_RSR_WWDGRSTF |
			RCC_RSR_LPWRRSTF );

    if( ulCsrFlags & RCC_RSR_PINRSTF )
    {
        pcResetSource = "PINRSTF: pin reset";
    }

    if( ulCsrFlags & RCC_RSR_BORRSTF )
    {
        pcResetSource = ( pcResetSource == NULL ) ? "BORRSTF: BOR" : "BORRSTF: BOR with pin reset";
    }
    else if( ulCsrFlags & RCC_RSR_SFTRSTF )
    {
        pcResetSource = ( pcResetSource == NULL ) ? "SFTRSTF: software system reset" : "SFTRSTF: software system reset with pin reset";
    }
    else if( ulCsrFlags & RCC_RSR_IWDGRSTF )
    {
        pcResetSource = ( pcResetSource == NULL ) ? "IWDGRSTF: independent watchdog" : "IWDGRSTF: independent watchdog with pin reset";
    }
    else if( ulCsrFlags & RCC_RSR_WWDGRSTF )
    {
        pcResetSource = ( pcResetSource == NULL ) ? "WWDGRSTF: window watchdog" : "WWDGRSTF: window watchdog with pin reset";
    }
    else if( ulCsrFlags & RCC_RSR_LPWRRSTF )
    {
        pcResetSource = ( pcResetSource == NULL ) ? "LPWRRSTF: Low-power" : "LPWRRSTF: Low-power with pin reset";
    }

    if( pcResetSource == NULL )
    {
        pcResetSource = "Unknown";
    }

    LogSys( "Reset Source: 0x%x : %s.", ulCsrFlags, pcResetSource );
}

uint32_t ulGetResetSource( void )
{
    return ulCsrFlags;
}

static void prvInitializeHeap( void )
{
	static uint8_t ucHeap1[ configTOTAL_HEAP_SIZE - SRAM3_NS_SIZE ];
	static uint8_t ucHeap2[ SRAM3_NS_SIZE ] __attribute__((section(".ucHeapSection")));

    HeapRegion_t xHeapRegions[] =
    {
        { ( unsigned char * ) ucHeap1, sizeof( ucHeap1 ) },
        { ( unsigned char * ) ucHeap2, sizeof( ucHeap2 ) },
        { NULL,                                        0 }
    };

    vPortDefineHeapRegions( xHeapRegions );
}

int main( void )
{
    ulCsrFlags = RCC->RSR;

    __HAL_RCC_CLEAR_RESET_FLAGS();

    hw_init();

    prvInitializeHeap();

    vLoggingInit();

    vDetermineResetSource();

    LogInfo( "HW Init Complete." );

    xSystemEvents = xEventGroupCreate();

    tfm_ns_interface_init();

    xTaskCreate( vInitTask, "Init", 512, NULL, 8, NULL );

    /* Start scheduler */
    vTaskStartScheduler();

    /* Initialize threads */

    LogError( "Kernel start returned." );

    /* This loop should be inaccessible.*/
    while( 1 )
    {
        __NOP();
    }
}

UBaseType_t uxRand( void )
{
    UBaseType_t uxRandVal = 0;

    if( psa_generate_random( ( uint8_t * ) ( &uxRandVal ), sizeof( UBaseType_t ) ) != PSA_SUCCESS )
    {
        configASSERT_CONTINUE( 0 );
    }

    return uxRandVal;
}

/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
    /* If the buffers to be provided to the Idle task are declared inside this
     * function then they must be declared static - otherwise they will be allocated on
     * the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
     * state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
 * application must provide an implementation of vApplicationGetTimerTaskMemory()
 * to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize )
{
    /* If the buffers to be provided to the Timer task are declared inside this
     * function then they must be declared static - otherwise they will be allocated on
     * the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
     * task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

/*-----------------------------------------------------------*/

#if configUSE_IDLE_HOOK == 1
void vApplicationIdleHook( void )
{
    vPetWatchdog();
}
#endif /* configUSE_IDLE_HOOK == 1 */

/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
    LogError( "Malloc failed" );

    while( 1 )
    {
        __NOP();
    }
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    char * pcTaskName )

{
    volatile uint32_t ulSetToZeroToStepOut = 1UL;

    taskENTER_CRITICAL();

    LogSys( "Stack overflow in %s", pcTaskName );
    ( void ) xTask;

    while( ulSetToZeroToStepOut != 0 )
    {
        __NOP();
    }

    taskEXIT_CRITICAL();
}

void vDoSystemReset( void )
{
    /*TODO: Disconnect MQTT */
    /*TODO: Disconnect from WiFi */

    vPetWatchdog();

    if( xTaskGetSchedulerState() == taskSCHEDULER_RUNNING )
    {
        vTaskSuspendAll();
    }

    LogSys( "System Reset in progress." );

    /* Drain log buffers */
    vDyingGasp();

    NVIC_SystemReset();
}


