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

#define START_LINE      (MT9V03X_H - 11)
#define END_LINE        9

extern paramType threshold, exposure;
extern paramType runLoop;
extern bool eleCross, eleLeftRoundabout, eleRightRoundabout;
extern bool eleBreak, eleObstacle, eleGarage;

extern uint8_t sideEdges[MT9V03X_H][2];
extern uint8_t upDownEdges[2][MT9V03X_W];
extern uint8_t stopFlag;

void GetSideLines();
void EightNeighborSearch(uint8_t image[MT9V03X_H][MT9V03X_W]);

#ifdef __cplusplus
}
#endif

#endif
