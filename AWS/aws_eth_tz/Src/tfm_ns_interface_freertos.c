/**
  ******************************************************************************
  * @file           : tfm_interface_freertos.c
  * @brief          : PSA IPC dispatch interface implementation for FreeRTOS
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "psa/error.h"
#include "tfm_ns_interface.h"
#include "logging_levels.h"


#define LOG_LEVEL LOG_INFO
#include "logging.h"

//#define LOG_DISPATCH
//#define LOG_DISPATCH_UML

#if defined( LOG_DISPATCH_UML ) && ( LOG_LEVEL < LOG_INFO )
#error "To define LOG_DISPATCH_UML, LOG_LEVEL must be increased to LOG_INFO"
#endif

const char* get_psa_function_name(uint32_t xSignal, veneer_fn fn, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3);

static SemaphoreHandle_t nsIpcMutex = { 0 };
static uint32_t ipc_signal = 0xFFFFFFFF;

void tfm_ns_interface_init( void )
{
    nsIpcMutex = xSemaphoreCreateMutex();
    if(nsIpcMutex == NULL)
    {
        LogError("Failed to create psa IPC mutex.\r\n");
    }
}

int32_t tfm_ns_interface_dispatch(veneer_fn fn,
                                  uint32_t arg0, uint32_t arg1,
                                  uint32_t arg2, uint32_t arg3)
{
    int32_t result;
    result = fn(arg0, arg1, arg2, arg3);

#ifdef LOG_DISPATCH
    const char * function_name = get_psa_function_name( ipc_signal, fn, arg0, arg1, arg2, arg3 );

    if(function_name != NULL)
    {
#ifdef LOG_DISPATCH_UML
      const char * tx_name = ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) ? "Not Thread" : pcTaskGetName( NULL );
      LogInfo("LOG_DISPATCH \"Secure Manager\" <- \"%s\"-- : %s", tx_name, function_name);
      LogInfo("LOG_DISPATCH activate \"Secure Manager\"");
      LogInfo("LOG_DISPATCH \"%s\" <- \"Secure Manager\"-- : %s", tx_name, ( result == PSA_SUCCESS ) ? "PSA_SUCCESS" : "PSA_ERROR");
      LogInfo("LOG_DISPATCH activate \"%s\"\r\n", ((tx_name != NULL) ? (tx_name) : ("Not Thread")));
#else /* LOG_DISPATCH_UML */
      LogInfo("LOG_DISPATCH, psa_api: %s, result %d\r\n", function_name, result);
#endif /* LOG_DISPATCH_UML */
    }
#endif /* LOG_DISPATCH */

    return result;
}

void ns_ipc_seq_begin(const ns_ipc_seq_info_t* info)
{
    /* Lock mutex */
    if(nsIpcMutex != NULL)
    {
        xSemaphoreTake(nsIpcMutex, portMAX_DELAY );
    }

    LogDebug(""ns_ipc_seq_begin (signal %u)", info->signal");

    ipc_signal = info->signal;
}

void ns_ipc_seq_end(const ns_ipc_seq_info_t* info)
{
	ipc_signal = 0xFFFFFFFF;

    /* Unlock mutex */
    if(nsIpcMutex != NULL)
    {
        xSemaphoreGive(nsIpcMutex);
    }
}
