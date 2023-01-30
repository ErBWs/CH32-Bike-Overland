/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "buzzer.h"

// Volume:0 - 100
paramType buzzerVolume = 40;

void Beep()
{
    pwm_set_duty(BUZZER_PIN, (uint32_t)buzzerVolume * 100);
}

void StopBeep()
{
    pwm_set_duty(BUZZER_PIN, 0);
}