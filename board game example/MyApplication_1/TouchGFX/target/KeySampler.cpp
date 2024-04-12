#include "KeySampler.hpp"
#include "touchgfx/hal/Buttons.hpp"
#include "string.h"
#include "main.h"

using namespace touchgfx;

void KeySampler::init()
{
    previousState = 0;
    Buttons::init();
}

bool KeySampler::sample(uint8_t& key)
{
    static uint32_t last_time = 0;

    if ((HAL_GetTick() - last_time) > 800)
    {
        last_time = HAL_GetTick();
        previousState = 0;
    }

    key = static_cast<uint8_t>(Buttons::sample());

    //User key
    if (key && (key != previousState))
    {
        previousState = key;
        return true;
    }

    return false;
}
