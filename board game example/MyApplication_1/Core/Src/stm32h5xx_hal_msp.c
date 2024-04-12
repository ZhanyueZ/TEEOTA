/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32h5xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  /* System interrupt init*/
  /* PendSV_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
* @brief CRC MSP Initialization
* This function configures the hardware resources used in this example
* @param hcrc: CRC handle pointer
* @retval None
*/
void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc)
{
  if(hcrc->Instance==CRC)
  {
  /* USER CODE BEGIN CRC_MspInit 0 */

  /* USER CODE END CRC_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_CRC_CLK_ENABLE();
  /* USER CODE BEGIN CRC_MspInit 1 */

  /* USER CODE END CRC_MspInit 1 */
  }

}

/**
* @brief CRC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hcrc: CRC handle pointer
* @retval None
*/
void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc)
{
  if(hcrc->Instance==CRC)
  {
  /* USER CODE BEGIN CRC_MspDeInit 0 */

  /* USER CODE END CRC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CRC_CLK_DISABLE();
  /* USER CODE BEGIN CRC_MspDeInit 1 */

  /* USER CODE END CRC_MspDeInit 1 */
  }

}

/**
* @brief I2C MSP Initialization
* This function configures the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hi2c->Instance==I2C4)
  {
  /* USER CODE BEGIN I2C4_MspInit 0 */

  /* USER CODE END I2C4_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C4;
    PeriphClkInitStruct.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PCLK3;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C4 GPIO Configuration
    PB9     ------> I2C4_SDA
    PB8     ------> I2C4_SCL
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_I2C4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_SBS_FASTMODEPLUS_ENABLE(SBS_FASTMODEPLUS_PB9);

    __HAL_SBS_FASTMODEPLUS_ENABLE(SBS_FASTMODEPLUS_PB8);

    /* Peripheral clock enable */
    __HAL_RCC_I2C4_CLK_ENABLE();
  /* USER CODE BEGIN I2C4_MspInit 1 */

  /* USER CODE END I2C4_MspInit 1 */
  }

}

/**
* @brief I2C MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  if(hi2c->Instance==I2C4)
  {
  /* USER CODE BEGIN I2C4_MspDeInit 0 */

  /* USER CODE END I2C4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C4_CLK_DISABLE();

    /**I2C4 GPIO Configuration
    PB9     ------> I2C4_SDA
    PB8     ------> I2C4_SCL
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

  /* USER CODE BEGIN I2C4_MspDeInit 1 */

  /* USER CODE END I2C4_MspDeInit 1 */
  }

}

static uint32_t FMC_Initialized = 0;

static void HAL_FMC_MspInit(void){
  /* USER CODE BEGIN FMC_MspInit 0 */

  /* USER CODE END FMC_MspInit 0 */
  GPIO_InitTypeDef GPIO_InitStruct ={0};
  if (FMC_Initialized) {
    return;
  }
  FMC_Initialized = 1;

  /* Peripheral clock enable */
  __HAL_RCC_FMC_CLK_ENABLE();

  /** FMC GPIO Configuration
  PD7   ------> FMC_NE1
  PD5   ------> FMC_NWE
  PD1   ------> FMC_D3
  PD4   ------> FMC_NOE
  PD0   ------> FMC_D2
  PF0   ------> FMC_A0
  PD15   ------> FMC_D1
  PD10   ------> FMC_D15
  PD14   ------> FMC_D0
  PD9   ------> FMC_D14
  PD8   ------> FMC_D13
  PE9   ------> FMC_D6
  PE14   ------> FMC_D11
  PE15   ------> FMC_D12
  PE8   ------> FMC_D5
  PE11   ------> FMC_D8
  PE13   ------> FMC_D10
  PE7   ------> FMC_D4
  PE10   ------> FMC_D7
  PE12   ------> FMC_D9
  */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_5|GPIO_PIN_1|GPIO_PIN_4
                          |GPIO_PIN_0|GPIO_PIN_15|GPIO_PIN_10|GPIO_PIN_14
                          |GPIO_PIN_9|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_8
                          |GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_7|GPIO_PIN_10
                          |GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* USER CODE BEGIN FMC_MspInit 1 */

  /* USER CODE END FMC_MspInit 1 */
}

void HAL_SRAM_MspInit(SRAM_HandleTypeDef* hsram){
  /* USER CODE BEGIN SRAM_MspInit 0 */

  /* USER CODE END SRAM_MspInit 0 */
  HAL_FMC_MspInit();
  /* USER CODE BEGIN SRAM_MspInit 1 */

  /* USER CODE END SRAM_MspInit 1 */
}

static uint32_t FMC_DeInitialized = 0;

static void HAL_FMC_MspDeInit(void){
  /* USER CODE BEGIN FMC_MspDeInit 0 */

  /* USER CODE END FMC_MspDeInit 0 */
  if (FMC_DeInitialized) {
    return;
  }
  FMC_DeInitialized = 1;
  /* Peripheral clock enable */
  __HAL_RCC_FMC_CLK_DISABLE();

  /** FMC GPIO Configuration
  PD7   ------> FMC_NE1
  PD5   ------> FMC_NWE
  PD1   ------> FMC_D3
  PD4   ------> FMC_NOE
  PD0   ------> FMC_D2
  PF0   ------> FMC_A0
  PD15   ------> FMC_D1
  PD10   ------> FMC_D15
  PD14   ------> FMC_D0
  PD9   ------> FMC_D14
  PD8   ------> FMC_D13
  PE9   ------> FMC_D6
  PE14   ------> FMC_D11
  PE15   ------> FMC_D12
  PE8   ------> FMC_D5
  PE11   ------> FMC_D8
  PE13   ------> FMC_D10
  PE7   ------> FMC_D4
  PE10   ------> FMC_D7
  PE12   ------> FMC_D9
  */
  HAL_GPIO_DeInit(GPIOD, GPIO_PIN_7|GPIO_PIN_5|GPIO_PIN_1|GPIO_PIN_4
                          |GPIO_PIN_0|GPIO_PIN_15|GPIO_PIN_10|GPIO_PIN_14
                          |GPIO_PIN_9|GPIO_PIN_8);

  HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0);

  HAL_GPIO_DeInit(GPIOE, GPIO_PIN_9|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_8
                          |GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_7|GPIO_PIN_10
                          |GPIO_PIN_12);

  /* USER CODE BEGIN FMC_MspDeInit 1 */

  /* USER CODE END FMC_MspDeInit 1 */
}

void HAL_SRAM_MspDeInit(SRAM_HandleTypeDef* hsram){
  /* USER CODE BEGIN SRAM_MspDeInit 0 */

  /* USER CODE END SRAM_MspDeInit 0 */
  HAL_FMC_MspDeInit();
  /* USER CODE BEGIN SRAM_MspDeInit 1 */

  /* USER CODE END SRAM_MspDeInit 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
