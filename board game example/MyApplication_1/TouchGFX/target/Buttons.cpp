#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/Buttons.hpp>

#include "main.h"

using namespace touchgfx;

/**
 * @brief JOYSTICK Types Definition
 */
typedef enum
{
    BUTTON_NONE  = 0xFF,
    BUTTON_USER  = '5',
} JOYState_TypeDef;

void Buttons::init()
{
}

unsigned int Buttons::sample()
{
    unsigned int buttonValue = BUTTON_NONE;

    if (HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin) == GPIO_PIN_SET)
    {
        buttonValue = BUTTON_USER;
    }

    if (buttonValue == BUTTON_NONE)
    {
        return 0;
    }

    return static_cast<unsigned int>(buttonValue);
}
