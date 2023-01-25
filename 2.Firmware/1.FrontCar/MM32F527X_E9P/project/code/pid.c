/*!
 * Copyright (c) 2022, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan
 */

#include "pid.h"

/*!
 * @brief       Change the coefficient of integral
 *
 * @param       error       Error
 * @param       pid         PID struct
 * @return      Coefficient of integral
 *
 * @note        Modify this part to implement different function
 */
paramType ConfigIntegral(paramType error, PidParam_t *pid)
{
    paramType coeffi;

    // Get linear integration coefficient
#ifdef FPU
    if (fabs(error) <= pid->errMin)
        coeffi = 1;
    else if (fabs(error) >= pid->errMax)
        coeffi = 0;
    else
        coeffi = (pid->errMax - fabs(error)) / (pid->errMax - pid->errMin);
#else
    if (abs(error) <= pid->errMin)
        coeffi = 1;
    else if (abs(error) >= pid->errMax)
        coeffi = 0;
    else
        coeffi = (pid->errMax - abs(error)) / (pid->errMax - pid->errMin);
#endif

    return coeffi;
}


/*!
 * @brief       Incremental pid control
 *
 * @param       pid             PID struct
 * @param       nowData         Current data
 * @return      PID output
 */
int32_t PidIncControl(PidParam_t *pid, paramType nowData)
{
    static paramType coeffi = 0;     // Coefficient of integration
    static paramType delta = 0;
    static paramType pErr = 0, iErr = 0, dErr = 0;

    // Get coefficient of Integration;
    paramType thisErr = pid->targetVal - nowData;
    coeffi = ConfigIntegral(thisErr, pid);

    // Trapezoidal integration
    paramType preI = (thisErr + pid->lastErr) / 2;
    pErr = thisErr - pid->lastErr;
    dErr = thisErr - 2 * (pid->lastErr) + pid->preLastErr;

    // Integration limitation
    if (pid->out > pid->integralMax)
    {
        if (preI <= 0)
            iErr = preI;
    } else if (pid->out < (-pid->integralMax))
    {
        if (preI >= 0)
            iErr = preI;
    } else
    {
        iErr = preI;
    }

    // Calculate
    delta = pid->kp * pErr
            + coeffi * pid->ki * iErr
            + pid->kd * dErr;

    // Save errors for next calculation
    pid->preLastErr = pid->lastErr;
    pid->lastErr = thisErr;
    pid->out += delta;

    pid->out = Limitation(pid->out, -pid->outputLimit, pid->outputLimit);
    return (int32_t) pid->out;
}


/*!
 * @brief       Position pid control
 *
 * @param       pid             PID struct
 * @param       nowData         Current data
 * @return      PID output
 */
int32_t PidPosControl(PidParam_t *pid, paramType nowData)
{
    static paramType coeffi = 0;     // Coefficient of integration
    static paramType delta = 0;
    static paramType pErr = 0, iErr = 0, dErr = 0;

    // Get coefficient of Integration;
    paramType thisErr = pid->targetVal - nowData;
    coeffi = ConfigIntegral(thisErr, pid);

    // Trapezoidal integration
    paramType preI = (thisErr + pid->lastErr) / 2;
    pErr = thisErr;
    dErr = thisErr - pid->lastErr;

    // Integration limitation
    if (pid->out > pid->integralMax)
    {
        if (preI <= 0)
            iErr += preI;
    } else if (pid->out < (-pid->integralMax))
    {
        if (preI >= 0)
            iErr += preI;
    } else
    {
        iErr += preI;
    }

    // Calculate
    pid->out = pid->kp * pErr
               + coeffi * pid->ki * iErr
               + pid->kd * dErr;

    // Save error for next calculate
    pid->lastErr = thisErr;

    pid->out = Limitation(pid->out, -pid->outputLimit, pid->outputLimit);
    return (int32_t) pid->out;
}