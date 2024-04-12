/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.21.4. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
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

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>
#include "main.h"
#include <touchgfx/hal/GPIO.hpp>

extern "C" I2C_HandleTypeDef hi2c4;

uint8_t buf[4];
int32_t xVal;
int32_t yVal;
bool touchReady = false;
void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */

}

bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */

    if (touchReady)
    {
        x = xVal;
        y = yVal;
        touchReady = false;
        return true;
    }
    else
    {
        return false;
    }
}




void readTouchInput()
{
    // Set receive register to P1XH
    uint8_t tReg = 0x03;
    HAL_I2C_Master_Transmit(&hi2c4, 0x70U, &tReg, 1, HAL_MAX_DELAY);
    //Receive P1XH, P1XL, P1YH and P1YL
    HAL_I2C_Master_Receive(&hi2c4, 0x70U, buf, 4, HAL_MAX_DELAY);
    yVal = 239;
    yVal -= (uint16_t)(buf[0] & 0xf) << 8;
    yVal -= buf [1];
    xVal = ((uint16_t)(buf[2]  & 0xf) << 8);
    xVal += buf [3];
    touchReady = true;
}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
