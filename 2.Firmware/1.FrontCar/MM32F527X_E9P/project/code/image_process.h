/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef MM32F527X_E9P_IMAGE_PROCESS_H
#define MM32F527X_E9P_IMAGE_PROCESS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "easy_ui.h"
#include "zf_device_mt9v03x.h"

extern paramType threshold;
extern paramType runLoop;
extern bool eleCross, eleLeftRoundabout, eleRightRoundabout;
extern bool eleBreak, eleObstacle, eleGarage;

extern uint8_t sideLines[120][2];

void GetSideLines();

#ifdef __cplusplus
}
#endif

#endif
