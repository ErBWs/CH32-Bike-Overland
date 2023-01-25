/*!
 * Copyright (c) 2022, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan
 */

#ifndef _pid_h
#define _pid_h

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "easy_ui.h"

/*!
 * @brief   Limit the value of 'x'
 *
 * @param   x       Value need to be limited
 * @param   low     The low outputLimit
 * @param   high    The high outputLimit
 * @return  Limited 'x'
 */
#define Limitation(x, low, high) ((x) < (low) ? (low) : ((x) > (high) ? (high) : (x)))


typedef struct
{
    paramType kp;           // Kp
    paramType ki;           // Ki
    paramType kd;           // Kd
    paramType targetVal;    // Target value
    paramType outputLimit;  // Output limitation defined by device
    paramType integralMax;  // Max of PID output which is used to limit integral error
    paramType errMax;       // Error larger than this will separate the integral
    paramType errMin;       // Error larger than this and smaller than errMax will decrease the coefficient of integral

    paramType lastErr;      // Last time error
    paramType preLastErr;   // Last time error of last time
    paramType out;          // Output
} PidParam_t;

paramType ConfigIntegral(paramType error, PidParam_t *pid);

int32_t PidIncControl(PidParam_t *pid, paramType nowData);
int32_t PidPosControl(PidParam_t *pid, paramType nowData);

#endif
