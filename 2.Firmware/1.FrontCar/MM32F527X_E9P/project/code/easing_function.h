/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef MM32F527X_E9P_EASING_FUNCTION_H
#define MM32F527X_E9P_EASING_FUNCTION_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <math.h>

#define PI          3.1415926

typedef enum
{
    LINEAR,
    IN_QUAD,        OUT_QUAD,       IN_OUT_QUAD,        // Quadratic
    IN_SIN,         OUT_SIN,        IN_OUT_SIN,         // Sinusoidal
    IN_EXP,         OUT_EXP,        IN_OUT_EXP,         // Exponential
    IN_CIRCLE,      OUT_CIRCLE,     IN_OUT_CIRCLE,      // Circular
    IN_CUBIC,       OUT_CUBIC,      IN_OUT_CUBIC,       // Cubic
    IN_QUART,       OUT_QUART,      IN_OUT_QUART,       // Quartic
    IN_QUINT,       OUT_QUINT,      IN_OUT_QUINT,       // Quintic
    IN_ELASTIC,     OUT_ELASTIC,    IN_OUT_ELASTIC,     // Elastic
    IN_BACK,        OUT_BACK,       IN_OUT_BACK,        // Back
    IN_BOUNCE,      OUT_BOUNCE,     IN_OUT_BOUNCE       // Bounce
} EasingFunction_e;

float GetEasingCurves(float currentTime, float start, float end, float totalTime, EasingFunction_e func);

#ifdef __cplusplus
}
#endif

#endif
