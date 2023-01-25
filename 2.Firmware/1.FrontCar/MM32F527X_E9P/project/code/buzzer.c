/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "buzzer.h"

// Volume:0 - 10
paramType buzzerVolume = 4;

void Beep()
{
    if (buzzerVolume > 10)
        buzzerVolume = 10;
    else if (buzzerVolume < 0)
        buzzerVolume = 0;
    pwm_set_duty(BUZZER_PIN, (uint32_t)buzzerVolume * 1000);
}

void StopBeep()
{
    pwm_set_duty(BUZZER_PIN, 0);
}