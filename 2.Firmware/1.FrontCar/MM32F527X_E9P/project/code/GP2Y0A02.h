/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef MM32F527X_E9P_GP2Y0A02_H
#define MM32F527X_E9P_GP2Y0A02_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <math.h>
#include "zf_driver_adc.h"
#include "zf_driver_delay.h"

#define GP2Y_ADC_PIN        ADC1_CH13_C3

void Gp2yInit(void);
float Gp2yGetDistance(void);

#ifdef __cplusplus
}
#endif

#endif
