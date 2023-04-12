/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "buzzer.h"

// Volume:0 - 100
paramType buzzerVolume = 40;
int16_t beepTime = 0;

void BuzzerInit()
{
    pwm_init(BUZZER_PIN, 3000, 0);
}

void Beep()
{
    if (beepTime <= 0)
    {
        pwm_set_duty(BUZZER_PIN, 0);
        return;
    }

    pwm_set_duty(BUZZER_PIN, (uint32_t)buzzerVolume * 100);
    beepTime -= BUZZER_TRIGGER_TIME_MS;
}