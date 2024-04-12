/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
extern IWDG_HandleTypeDef hiwdg;
extern TIM_HandleTypeDef htim5;
extern SPI_HandleTypeDef hspi5;
extern DCACHE_HandleTypeDef hdcache1;
extern RNG_HandleTypeDef hrng;
extern XSPI_HandleTypeDef hospi1;
extern UART_HandleTypeDef huart1;
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

#include "iot_gpio_stm32_prv.h"

typedef enum GpioPin
{
    GPIO_MX_FLOW,
    GPIO_MX_RESET,
    GPIO_MX_NSS,
    GPIO_MX_NOTIFY,
    GPIO_LED_RED,
    GPIO_LED_GREEN,
    GPIO_MAX
} GpioPin_t;

extern const IotMappedPin_t xGpioMap[ GPIO_MAX ];

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define WIFI_SPI_HND    hspi5
#define FLASH_OSPI_HND  hospi1
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void MX_GPIO_Init(void);
void MX_RNG_Init(void);
void MX_ICACHE_Init(void);
void MX_DCACHE1_Init(void);
void MX_OCTOSPI1_Init(void);
void MX_TIM5_Init(void);
void MX_USART1_UART_Init(void);
void MX_SPI5_Init(void);
void MX_IWDG_Init(void);

/* USER CODE BEGIN EFP */
void hw_init( void );
void vDoSystemReset( void );
static inline void vPetWatchdog( void )
{
  // (void) HAL_IWDG_Refresh( &hiwdg );
}
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_GREEN_Pin GPIO_PIN_9
#define LED_GREEN_GPIO_Port GPIOI
#define LED_RED_Pin GPIO_PIN_1
#define LED_RED_GPIO_Port GPIOF
#define MXCHIP_FLOW_Pin GPIO_PIN_3
#define MXCHIP_FLOW_GPIO_Port GPIOF
#define MXCHIP_FLOW_EXTI_IRQn EXTI3_IRQn
#define MXCHIP_NSS_Pin GPIO_PIN_6
#define MXCHIP_NSS_GPIO_Port GPIOF
#define MXCHIP_RESET_Pin GPIO_PIN_8
#define MXCHIP_RESET_GPIO_Port GPIOH
#define MXCHIP_NOTIFY_Pin GPIO_PIN_4
#define MXCHIP_NOTIFY_GPIO_Port GPIOH
#define MXCHIP_NOTIFY_EXTI_IRQn EXTI4_IRQn
#define MXCHIP_BOOT_Pin GPIO_PIN_0
#define MXCHIP_BOOT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
