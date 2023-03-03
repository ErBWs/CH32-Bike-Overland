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

uint8_t sideLines[120][2] = {0};

void GetSideLines()
{
    for (int i = 110; i > 0; --i)
    {
        for (int j = 93; j < 186; ++j)
        {
            if (mt9v03x_image[i][j] < threshold && mt9v03x_image[i][j + 1] < threshold)
            {
                sideLines[i][1] = j;
                break;
            }
        }
        for (int j = 93; j > 1; --j)
        {
            if (mt9v03x_image[i][j] < threshold && mt9v03x_image[i][j - 1] < threshold)
            {
                sideLines[i][0] = j;
                break;
            }
        }
    }
}