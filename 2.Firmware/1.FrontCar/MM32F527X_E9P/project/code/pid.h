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

/*!
 * @brief   Limit the value of 'x'
 *
 * @param   x       Value need to be limited
 * @param   low     The low outputLimit
 * @param   high    The high outputLimit
 * @return  Limited 'x'
 */
#define Limitation(x, low, high) ((x) < (low) ? (low) : ((x) > (high) ? (high) : (x)))

#ifdef FPU
typedef     double      pidParamType;
#else
typedef     int32_t     pidParamType;
#endif


typedef struct
{
    pidParamType kp;           // Kp
    pidParamType ki;           // Ki
    pidParamType kd;           // Kd
    pidParamType targetVal;    // Target value
    pidParamType outputLimit;  // Output limitation defined by device
    pidParamType integralMax;  // Max of PID output which is used to limit integral error
    pidParamType errMax;       // Error larger than this will separate the integral
    pidParamType errMin;       // Error larger than this and smaller than errMax will decrease the coefficient of integral

    pidParamType lastErr;      // Last time error
    pidParamType preLastErr;   // Last time error of last time
    pidParamType out;          // Output
} PidParam_t;

pidParamType ConfigIntegral(pidParamType error, PidParam_t *pid);

int32_t PidIncControl(PidParam_t *pid, pidParamType nowData);
int32_t PidPosControl(PidParam_t *pid, pidParamType nowData);

#endif
