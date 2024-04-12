/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : TouchGFXHAL.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.21.0. This file is only
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

#include <TouchGFXHAL.hpp>

/* USER CODE BEGIN TouchGFXHAL.cpp */
#include <TouchGFXGeneratedHAL.hpp>
#include <touchgfx/hal/GPIO.hpp>
#include <touchgfx/hal/OSWrappers.hpp>
#include <STM32TouchController.hpp>
#include <KeySampler.hpp>
#include "main.h"
#include "FreeRTOS.h"

volatile bool firstFrameReadyToDisplay = false;
static volatile bool dmaCompleted = true;
static volatile bool refreshRequested = false;
static uint16_t* TFTframebuffer = 0;
extern "C" DMA_HandleTypeDef handle_GPDMA2_Channel6;;
void initLCD(void);

static void DMA_TxCpltCallback(DMA_HandleTypeDef* hdma);
static void DMA_TxErrorCallback(DMA_HandleTypeDef* hdma);


extern "C"
{
    void     LCD_IO_WriteReg(uint8_t Reg);        //defined in TouchGFXGeneratedHAL.cpp
    void     LCD_IO_WriteData(uint16_t RegValue); //defined in TouchGFXGeneratedHAL.cpp
}

using namespace touchgfx;

KeySampler btnctrl;


void TouchGFXHAL::initialize()
{
    initLCD();

    HAL_DMA_RegisterCallback(&handle_GPDMA2_Channel6, HAL_DMA_XFER_CPLT_CB_ID, DMA_TxCpltCallback);
    HAL_DMA_RegisterCallback(&handle_GPDMA2_Channel6, HAL_DMA_XFER_ERROR_CB_ID, DMA_TxErrorCallback);

    instrumentation.init();
    setMCUInstrumentation(&instrumentation);
    enableMCULoadCalculation(true);
    TouchGFXGeneratedHAL::initialize();
    setButtonController(&btnctrl);
}

/**
 * Gets the frame buffer address used by the TFT controller.
 *
 * @return The address of the frame buffer currently being displayed on the TFT.
 */
uint16_t* TouchGFXHAL::getTFTFrameBuffer() const
{
    return TFTframebuffer;
}

/**
 * Sets the frame buffer address used by the TFT controller.
 *
 * @param [in] address New frame buffer address.
 */
void TouchGFXHAL::setTFTFrameBuffer(uint16_t* address)
{
    TFTframebuffer = address;

    TouchGFXGeneratedHAL::setTFTFrameBuffer(address);
}

/**
 * This function is called whenever the framework has performed a partial draw.
 *
 * @param rect The area of the screen that has been drawn, expressed in absolute coordinates.
 *
 * @see flushFrameBuffer().
 */
void TouchGFXHAL::flushFrameBuffer(const touchgfx::Rect& rect)
{
    // Calling parent implementation of flushFrameBuffer(const touchgfx::Rect& rect).
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.
    // Please note, HAL::flushFrameBuffer(const touchgfx::Rect& rect) must
    // be called to notify the touchgfx framework that flush has been performed.
    // To calculate he start adress of rect,
    // use advanceFrameBufferToRect(uint8_t* fbPtr, const touchgfx::Rect& rect)
    // defined in TouchGFXGeneratedHAL.cpp

    TouchGFXGeneratedHAL::flushFrameBuffer(rect);
}

bool TouchGFXHAL::blockCopy(void* RESTRICT dest, const void* RESTRICT src, uint32_t numBytes)
{
    return TouchGFXGeneratedHAL::blockCopy(dest, src, numBytes);
}

/**
 * Configures the interrupts relevant for TouchGFX. This primarily entails setting
 * the interrupt priorities for the DMA and LCD interrupts.
 */
void TouchGFXHAL::configureInterrupts()
{
    // Calling parent implementation of configureInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.



    TouchGFXGeneratedHAL::configureInterrupts();
}

/**
 * Used for enabling interrupts set in configureInterrupts()
 */
void TouchGFXHAL::enableInterrupts()
{
    // Calling parent implementation of enableInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    TouchGFXGeneratedHAL::enableInterrupts();
}

/**
 * Used for disabling interrupts set in configureInterrupts()
 */
void TouchGFXHAL::disableInterrupts()
{
    // Calling parent implementation of disableInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    HAL_NVIC_DisableIRQ(EXTI3_IRQn);

    TouchGFXGeneratedHAL::disableInterrupts();
}

/**
 * Configure the LCD controller to fire interrupts at VSYNC. Called automatically
 * once TouchGFX initialization has completed.
 */
void TouchGFXHAL::enableLCDControllerInterrupt()
{
    // Calling parent implementation of enableLCDControllerInterrupt().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::enableLCDControllerInterrupt();
}

bool TouchGFXHAL::beginFrame()
{
    refreshRequested = false;

    return TouchGFXGeneratedHAL::beginFrame();
}

void TouchGFXHAL::endFrame()
{
    TouchGFXGeneratedHAL::endFrame();

    if (frameBufferUpdatedThisFrame)
    {
        refreshRequested = true;
    }
}

void setWindow(uint32_t Xpos, uint32_t Ypos, uint32_t Xwidth, uint32_t Ywidth)
{
    // set pixel x pos:
    LCD_IO_WriteReg(ST7789H2_CASET);

    LCD_IO_WriteData(Xpos >> 8);                   /* XS[15:8] */
    LCD_IO_WriteData((uint8_t)Xpos);               /* XS[7:0] */
    LCD_IO_WriteData((Xpos + Xwidth - 1) >> 8);        /* XE[15:8] */
    LCD_IO_WriteData((uint8_t)(Xpos + Xwidth - 1));    /* XE[7:0] */


    // set pixel y pos:
    LCD_IO_WriteReg(ST7789H2_RASET);

    LCD_IO_WriteData(Ypos >> 8);                 /* YS[15:8] */
    LCD_IO_WriteData((uint8_t)Ypos);             /* YS[7:0] */
    LCD_IO_WriteData((Ypos + Ywidth - 1) >> 8);        /* YE[15:8] */
    LCD_IO_WriteData((uint8_t)(Ypos + Ywidth - 1));    /* YE[7:0] */
}

/**
  * @brief  DMA Linked-list Queue configuration
  * @param  None
  * @retval None
  */
__STATIC_INLINE HAL_StatusTypeDef GPDMA_Queue_Config(DMA_QListTypeDef* Queue, uint8_t node_cnt, uint8_t* src, uint8_t* dst, uint32_t data_size)
{
    static DMA_NodeTypeDef  Nodes[(((240 * 240 * 2) / ((64 * 1024) - 2)) + 1)];
    HAL_StatusTypeDef ret = HAL_OK;
    /* DMA node configuration declaration */
    DMA_NodeConfTypeDef pNodeConfig;
    uint8_t i;

    /* Set node configuration ################################################*/
    pNodeConfig.NodeType = DMA_GPDMA_2D_NODE;
    pNodeConfig.Init.Request = DMA_REQUEST_SW;
    pNodeConfig.Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;
    pNodeConfig.Init.Direction = DMA_MEMORY_TO_MEMORY;
    pNodeConfig.Init.SrcInc = DMA_SINC_INCREMENTED;
    pNodeConfig.Init.DestInc = DMA_DINC_FIXED;
    pNodeConfig.Init.SrcDataWidth = DMA_SRC_DATAWIDTH_HALFWORD;
    pNodeConfig.Init.DestDataWidth = DMA_DEST_DATAWIDTH_HALFWORD;
    pNodeConfig.Init.SrcBurstLength = 1;
    pNodeConfig.Init.DestBurstLength = 1;
    pNodeConfig.Init.TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT0 | DMA_DEST_ALLOCATED_PORT0;
    pNodeConfig.Init.TransferEventMode = DMA_TCEM_LAST_LL_ITEM_TRANSFER;
    pNodeConfig.RepeatBlockConfig.RepeatCount = 1;
    pNodeConfig.RepeatBlockConfig.SrcAddrOffset = 0;
    pNodeConfig.RepeatBlockConfig.DestAddrOffset = 0;
    pNodeConfig.RepeatBlockConfig.BlkSrcAddrOffset = 0;
    pNodeConfig.RepeatBlockConfig.BlkDestAddrOffset = 0;
    pNodeConfig.TriggerConfig.TriggerPolarity = DMA_TRIG_POLARITY_MASKED;
    pNodeConfig.DataHandlingConfig.DataExchange = DMA_EXCHANGE_NONE;
    pNodeConfig.DataHandlingConfig.DataAlignment = DMA_DATA_RIGHTALIGN_ZEROPADDED;
    pNodeConfig.SrcAddress = (uint32_t) src;
    pNodeConfig.DstAddress = (uint32_t) dst;
    if (node_cnt > 1)
    {
        pNodeConfig.DataSize = ((64 * 1024) - 2);
    }
    else
    {
        pNodeConfig.DataSize = data_size;
    }

    for (i = 0; ((ret == HAL_OK) && (i < node_cnt)); i++)
    {
        if (i == 0)
        {
            /* Reset The Queue */
            ret = HAL_DMAEx_List_ResetQ(Queue);
            if (ret != HAL_OK)
            {
                return ret;
            }
            /* Build Node first Node */
            ret = HAL_DMAEx_List_BuildNode(&pNodeConfig, &Nodes[i]);
            if (ret != HAL_OK)
            {
                return ret;
            }
            /* Insert Node to Queue */
            ret = HAL_DMAEx_List_InsertNode_Head(Queue, &Nodes[i]);
            if (ret != HAL_OK)
            {
                return ret;
            }
        }
        else
        {
            /* Adjust size of last node */
            if ((node_cnt > 1) && (i == (node_cnt - 1)))
            {
                pNodeConfig.DataSize = (data_size - (i * ((64 * 1024) - 2)));
            }
            /* Build Node Node */
            ret = HAL_DMAEx_List_BuildNode(&pNodeConfig, &Nodes[i]);
            if (ret != HAL_OK)
            {
                return ret;
            }
            /* Insert Node to Queue */
            ret = HAL_DMAEx_List_InsertNode_Tail(Queue, &Nodes[i]);
            if (ret != HAL_OK)
            {
                return ret;
            }
        }
        pNodeConfig.SrcAddress += ((64 * 1024) - 2);
    }

    return ret;
}

static int32_t LCD_IO_SendDataDMA(uint8_t* pData, uint32_t Length)
{
    static DMA_QListTypeDef Queue;
    uint32_t len = Length;
    uint8_t node_cnt = (len / ((64 * 1024) - 2));

    if (len % ((64 * 1024) - 2))
    {
        node_cnt++;
    }

    if ((handle_GPDMA2_Channel6.Mode & DMA_LINKEDLIST) == DMA_LINKEDLIST)
    {
        if (GPDMA_Queue_Config(&Queue, node_cnt, pData, (uint8_t*)FMC_BANK1_MEM, len) != HAL_OK)
        {
            return -1;
        }

        /* Link created queue to DMA channel #######################################*/
        if (HAL_DMAEx_List_LinkQ(&handle_GPDMA2_Channel6, &Queue) != HAL_OK)
        {
            return -1;
        }

        /* Enable All the DMA interrupts */
        if (HAL_DMAEx_List_Start_IT(&handle_GPDMA2_Channel6) != HAL_OK)
        {
            return -1;
        }
    }
    else
    {
        if (node_cnt > 1)
        {
            return -1;
        }

        switch (handle_GPDMA2_Channel6.Init.DestDataWidth)
        {
        case DMA_DEST_DATAWIDTH_WORD :
            len = (Length / 4);
            break;
        case DMA_DEST_DATAWIDTH_BYTE :
            len = Length;
            break;
        default:
        case DMA_DEST_DATAWIDTH_HALFWORD :
            len = (Length / 2);
            break;
        }

        if (HAL_DMA_Start_IT(&handle_GPDMA2_Channel6, (uint32_t)pData, (uint32_t)FMC_BANK1_MEM, len) != HAL_OK)
        {
            /* Transfer Error */
            return -1;
        }
    }

    return 0;
}

/**
  * @brief  Signal Transfer Event.
  * @param  Instance LCD Instance
  * @retval None
  */
void LCD_SignalTransferDone(uint32_t Instance)
{
    if (Instance == 0)
    {
        dmaCompleted = true;
    }
}

/**
  * @brief  DMA transfer complete callback
  * @note   This function is executed when the transfer complete interrupt
  *         is generated
  * @retval None
  */
static void DMA_TxCpltCallback(DMA_HandleTypeDef* hdma)
{
    if (hdma == &handle_GPDMA2_Channel6)
    {
        /* Signal Transfer Done Event */
        LCD_SignalTransferDone(0);
    }
}

/**
  * @brief  DMA transfer error callback
  * @note   This function is executed when the transfer error interrupt
  *         is generated during DMA transfer
  * @retval None
  */
static void DMA_TxErrorCallback(DMA_HandleTypeDef* hdma)
{
    __disable_irq();
    while (1)
    {
    }
}

/**
* @brief  Signal transfert event.
* @param  Instance LCD Instance
* @param  Line counter
* @retval None
*/
void LCD_SignalTearingEffectEvent(void)
{
    // VSync has occurred, increment TouchGFX engine vsync counter
    HAL::getInstance()->vSync();
    // VSync has occurred, signal TouchGFX engine
    OSWrappers::signalVSync();

    if (!dmaCompleted)
    {
        if (HAL_DMAEx_List_DeInit(&handle_GPDMA2_Channel6) != HAL_OK)
        {
            Error_Handler();
        }
        if (HAL_DMAEx_List_Init(&handle_GPDMA2_Channel6) != HAL_OK)
        {
            Error_Handler();
        }

        HAL_DMA_RegisterCallback(&handle_GPDMA2_Channel6, HAL_DMA_XFER_CPLT_CB_ID, DMA_TxCpltCallback);

        dmaCompleted = true;
    }

    if (refreshRequested)
    {
        // Swap frame buffers immediately instead of waiting for the task to be scheduled in.
        // Note: task will also swap when it wakes up, but that operation is guarded and will not have
        // any effect if already swapped.

        touchgfx::HAL::getInstance()->swapFrameBuffers();

        // Set window, enable display reading to GRAM, transmit buffer using DMA
        setWindow(0, 0, 240, 240);
        LCD_IO_WriteReg(ST7789H2_WRITE_RAM);
        dmaCompleted = false;
        LCD_IO_SendDataDMA((uint8_t*)TFTframebuffer, (240 * 240 * 2));
    }
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == LCD_TE_Pin)
    {
        // Set VSYNC_FREQ GPIO Pin
        GPIO::set(GPIO::VSYNC_FREQ);

        LCD_SignalTearingEffectEvent();
    }
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == TS_INT_Pin)
    {
        // Touch input is read by interrupt based on external pin interrupt from touch controller
        readTouchInput();
    }
    else if (GPIO_Pin == LCD_TE_Pin)
    {
        GPIO::clear(GPIO::VSYNC_FREQ);
    }
}

void initLCD(void)
{
    /* Reset ST7789H2 */
    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
    HAL_Delay(1); /* wait at least 10us according ST7789H2 datasheet */
    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
    HAL_Delay(120); /* wait maximum 120ms according ST7789H2 datasheet */

    /* Init display */
    LCD_IO_WriteReg(ST7789H2_COLOR_MODE);
    LCD_IO_WriteData(ST7789H2_FORMAT_RBG565);
    LCD_IO_WriteReg(ST7789H2_DISPLAY_INVERSION_ON);

    /* Voltage Gamma Control */
    const uint8_t arrayLength = 14;
    const uint16_t PVparameters[arrayLength] = {0x00D0, 0x0008, 0x0011, 0x0008, 0x000C, 0x0015, 0x0039, 0x0033, 0x0050, 0x0036, 0x0013, 0x0014, 0x0029, 0x002D};
    const uint16_t NVparameters[arrayLength] = {0x00D0, 0x0008, 0x0010, 0x0008, 0x0006, 0x0006, 0x0039, 0x0044, 0x0051, 0x000B, 0x0016, 0x0014, 0x002F, 0x0031};
    LCD_IO_WriteReg(ST7789H2_PV_GAMMA_CTRL);
    for (uint32_t i = 0; i < arrayLength; i++)
    {
        LCD_IO_WriteData(PVparameters[i]);
    }
    LCD_IO_WriteReg(ST7789H2_NV_GAMMA_CTRL);
    for (uint32_t i = 0; i < arrayLength; i++)
    {
        LCD_IO_WriteData(NVparameters[i]);
    }

    /* Fill with black pixels */
    LCD_IO_WriteReg(ST7789H2_WRITE_RAM);
    for (uint32_t i = 0; i < 240 * 240; i++)
    {
        LCD_IO_WriteData(0x0000);
    }

    /* Display on */
    LCD_IO_WriteReg(ST7789H2_DISPLAY_ON);
    LCD_IO_WriteReg(ST7789H2_SLEEP_OUT);

    /* Tearing effect line on */
    LCD_IO_WriteReg(ST7789H2_TE_LINE_ON);
    LCD_IO_WriteData(0x00); // TE Mode 1
}

extern "C"
{
    portBASE_TYPE IdleTaskHook(void* p)
    {
        if ((int)p) //idle task sched out
        {
            touchgfx::HAL::getInstance()->setMCUActive(true);
        }
        else //idle task sched in
        {
            touchgfx::HAL::getInstance()->setMCUActive(false);
        }
        return pdTRUE;
    }
}

/* USER CODE END TouchGFXHAL.cpp */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
