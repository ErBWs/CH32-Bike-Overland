/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "image_process.h"

// loop = 0: infinite loop
paramType runLoop = 2;

paramType threshold = 180;
bool eleCross = true, eleLeftRoundabout = true, eleRightRoundabout = true;
bool eleBreak = true, eleObstacle = true, eleGarage = true;