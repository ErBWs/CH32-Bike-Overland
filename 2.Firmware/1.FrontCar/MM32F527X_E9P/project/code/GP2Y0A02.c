/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "GP2Y0A02.h"

void Gp2yInit(void)
{
    adc_init(GP2Y_ADC_PIN, ADC_12BIT);
    system_delay_ms(50);
}

float Gp2yGetDistance(void)
{
    uint16_t distanceAdc;
    float distance, voltage;

    distanceAdc = adc_convert(GP2Y_ADC_PIN);
    voltage = 5.0 * distanceAdc / 4096;
    distance = 35.7 / voltage;
    return distance;
}