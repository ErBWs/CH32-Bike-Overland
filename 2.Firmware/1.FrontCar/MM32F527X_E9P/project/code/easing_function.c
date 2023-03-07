/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "easing_function.h"

float GetEasingCurves(float currentTime, float start, float end, float totalTime, EasingFunction_e func)
{
    float s = 1.70158f;
    float p = 0;
    float a = end;

    switch (func)
    {
    case LINEAR:
        return end * currentTime / totalTime + start;
    case IN_QUAD:
        currentTime /= totalTime;
        return end * currentTime * currentTime + start;
    case OUT_QUAD:
        currentTime /= totalTime;
        return -end * currentTime * (currentTime - 2) + start;
    case IN_OUT_QUAD:
        if ((currentTime /= totalTime / 2) < 1) return end / 2 * currentTime * currentTime + start;
        currentTime--;
        return -end / 2 * (currentTime * (currentTime - 2) - 1) + start;
    case IN_SIN:
        return -end * (float) cos(currentTime / totalTime * (PI / 2)) + end + start;
    case OUT_SIN:
        return end * (float) sin(currentTime / totalTime * (PI / 2)) + start;
    case IN_OUT_SIN:
        return -end / 2 * (float) (cos(PI * currentTime / totalTime) - 1) + start;
    case IN_EXP:
        return (currentTime == 0) ? start : end * (float) pow(2, 10 * (currentTime / totalTime - 1)) + start;
    case OUT_EXP:
        return (currentTime == totalTime) ? start + end : end * (float) (-pow(2, -10 * currentTime / totalTime) + 1) + start;
    case IN_OUT_EXP:
        if (currentTime == 0) return start;
        if (currentTime == totalTime) return start + end;
        if ((currentTime /= totalTime / 2) < 1) return end / 2 * (float) pow(2, 10 * (currentTime - 1)) + start;
        return end / 2 * (-(float) pow(2, -10 * --currentTime) + 2) + start;
    case IN_CIRCLE:
        currentTime /= totalTime;
        return -end * (sqrtf(1 - currentTime * currentTime) - 1) + start;
    case OUT_CIRCLE:
        currentTime = currentTime / totalTime - 1;
        return end * sqrtf(1 - currentTime * currentTime) + start;
    case IN_OUT_CIRCLE:
        if ((currentTime /= totalTime / 2) < 1) return -end / 2 * (sqrtf(1 - currentTime * currentTime) - 1) + start;
        currentTime -= 2;
        return end / 2 * (sqrtf(1 - currentTime * currentTime) + 1) + start;
    case IN_CUBIC:
        currentTime /= totalTime;
        return end * currentTime * currentTime * currentTime + start;
    case OUT_CUBIC:
        currentTime = currentTime / totalTime - 1;
        return end * (currentTime * currentTime * currentTime + 1) + start;
    case IN_OUT_CUBIC:
        if ((currentTime /= totalTime / 2) < 1) return end / 2 * currentTime * currentTime * currentTime + start;
        currentTime -= 2;
        return end / 2 * (currentTime * currentTime * currentTime + 2) + start;
    case IN_QUART:
        currentTime /= totalTime;
        return end * currentTime * currentTime * currentTime * currentTime + start;
    case OUT_QUART:
        currentTime = currentTime / totalTime - 1;
        return -end * (currentTime * currentTime * currentTime * currentTime - 1) + start;
    case IN_OUT_QUART:
        if ((currentTime /= totalTime / 2) < 1) return end / 2 * currentTime * currentTime * currentTime * currentTime + start;
        currentTime -= 2;
        return -end / 2 * (currentTime * currentTime * currentTime * currentTime - 2) + start;
    case IN_QUINT:
        currentTime /= totalTime;
        return end * currentTime * currentTime * currentTime * currentTime * currentTime + start;
    case OUT_QUINT:
        currentTime = currentTime / totalTime - 1;
        return end * (currentTime * currentTime * currentTime * currentTime * currentTime + 1) + start;
    case IN_OUT_QUINT:
        if ((currentTime /= totalTime / 2) < 1) return end / 2 * currentTime * currentTime * currentTime * currentTime * currentTime + start;
        currentTime -= 2;
        return end / 2 * (currentTime * currentTime * currentTime * currentTime * currentTime + 2) + start;
    case IN_ELASTIC:
        if (currentTime == 0) return start;
        if ((currentTime /= totalTime) == 1) return start + end;
        if (!p)
            p = totalTime * 0.3f;
        if (a < fabsf(end))
        {
            a = end;
            s = p / 4;
        } else s = p / (float) (2 * PI) * asinf(end / a);
        currentTime -= 1;
        return -(a * (float) pow(2, 10 * currentTime) * (float) sin((currentTime * totalTime - s) * (2 * PI) / p)) + start;
    case OUT_ELASTIC:
        if (currentTime == 0) return start;
        if ((currentTime /= totalTime) == 1) return start + end;
        if (!p) p = totalTime * 0.3f;
        if (a < fabsf(end))
        {
            a = end;
            s = p / 4;
        } else s = p / (float) (2 * PI) * asinf(end / a);
        return a * (float) pow(2, -10 * currentTime) * (float) sin((currentTime * totalTime - s) * (2 * PI) / p) + end + start;
    case IN_OUT_ELASTIC:
        if (currentTime == 0) return start;
        if ((currentTime /= totalTime / 2) == 2) return start + end;
        if (!p) p = totalTime * (0.3f * 1.5f);
        if (a < fabsf(end))
        {
            a = end;
            s = p / 4;
        } else s = p / (float) (2 * PI) * asinf(end / a);
        currentTime -= 1;
        if (currentTime < 1)
        {
            return -0.5f * (a * (float) pow(2, 10 * currentTime) * (float) sin((currentTime * totalTime - s) * (2 * PI) / p)) + start;
        }
        return a * (float) pow(2, -10 * currentTime) * (float) sinf((currentTime * totalTime - s) * (float) (2 * PI) / p) * 0.5f + end + start;
    case IN_BACK:
        currentTime /= totalTime;
        return end * currentTime * currentTime * ((s + 1) * currentTime - s) + start;
    case OUT_BACK:
        currentTime = currentTime / totalTime - 1;
        return end * (currentTime * currentTime * ((s + 1) * currentTime + s) + 1) + start;
    case IN_OUT_BACK:
        s *= (1.525f);
        if ((currentTime /= totalTime / 2) < 1) return end / 2 * (currentTime * currentTime * ((s + 1) * currentTime - s)) + start;
        currentTime -= 2;
        return end / 2 * (currentTime * currentTime * ((s + 1) * currentTime + s) + 2) + start;
    case IN_BOUNCE:
        return end - GetEasingCurves(totalTime - currentTime, 0, end, totalTime, OUT_BOUNCE) + start;
    case OUT_BOUNCE:
        if ((currentTime /= totalTime) < (1 / 2.75))
        {
            return end * (7.5625f * currentTime * currentTime) + start;
        } else if (currentTime < (2 / 2.75))
        {
            currentTime -= (1.5f / 2.75f);
            return end * (7.5625f * currentTime * currentTime + 0.75f) + start;
        } else if (currentTime < (2.5 / 2.75))
        {
            currentTime -= (2.25f / 2.75f);
            return end * (7.5625f * currentTime * currentTime + 0.9375f) + start;
        } else
        {
            currentTime -= (2.625f / 2.75f);
            return end * (7.5625f * currentTime * currentTime + 0.984375f) + start;
        case IN_OUT_BOUNCE:
            if (currentTime < totalTime / 2) return GetEasingCurves(currentTime * 2, 0, end, totalTime, IN_BOUNCE) * 0.5f + start;
            return GetEasingCurves(currentTime * 2 - totalTime, 0, end, totalTime, OUT_BOUNCE) * 0.5f + end * 0.5f + start;
        default:
            break;
        }
    }
}