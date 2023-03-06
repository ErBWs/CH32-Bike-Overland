/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "image_process.h"

// loop = 0: infinite loop
paramType runLoop = 2;

paramType threshold = 180, exposure = 300;
bool eleCross = true, eleLeftRoundabout = true, eleRightRoundabout = true;
bool eleBreak = true, eleObstacle = true, eleGarage = true;

uint8_t stopFlag = 0;
uint8_t sideEdges[MT9V03X_H][2] = {0};
uint8_t upDownEdges[2][MT9V03X_W] = {0};


int PixelIsEdge(uint8_t image[MT9V03X_H][MT9V03X_W], uint8_t row, uint8_t col)
{
    if (row == 0)
    {
        zf_assert(0);
        return 2;
    }
    if (row == MT9V03X_H - 1)
    {
        zf_assert(0);
        return 2;
    }
    if (col == 0)
    {
        zf_assert(0);
        return 2;
    }
    if (col == MT9V03X_W - 1)
    {
        zf_assert(0);
        return 2;
    }
//
//    // Difference divided by sum
//    uint8_t temp[5] = {0};
//    temp[0] = 100 * (image[row][col] - image[row + 1][col]) / (image[row][col] + image[row + 1][col]);
//    temp[1] = 100 * (image[row][col] - image[row - 1][col]) / (image[row][col] + image[row - 1][col]);
//    temp[2] = 100 * (image[row][col] - image[row][col + 1]) / (image[row][col] + image[row][col + 1]);
//    temp[3] = 100 * (image[row][col] - image[row][col - 1]) / (image[row][col] + image[row][col - 1]);
//    temp[4] = (temp[0] + temp[1] + temp[2] + temp[3]) / 4;
//    if (temp[4] < threshold)
//        return 1;
//    else
//        return 0;

    if (image[row][col] < threshold)
        return 1;
    else
        return 0;
}


void GetSideLines()
{
    for (int i = 110; i > 0; --i)
    {
        for (int j = 93; j < 186; ++j)
        {
//            if (mt9v03x_image[i][j] < threshold && mt9v03x_image[i][j + 1] < threshold)
                if (PixelIsEdge(mt9v03x_image, i, j) == 1)
            {
                sideEdges[i][1] = j;
                break;
            }
        }
        for (int j = 93; j > 1; --j)
        {
//            if (mt9v03x_image[i][j] < threshold && mt9v03x_image[i][j - 1] < threshold)
                if (PixelIsEdge(mt9v03x_image, i, j) == 1)
            {
                sideEdges[i][0] = j;
                break;
            }
        }
    }
}


void EightNeighborSearch(uint8_t image[MT9V03X_H][MT9V03X_W])
{
    uint8_t startLeft = 1, startRight = MT9V03X_W - 2, breakFlag = 0;
    uint8_t rowLeft, colLeft, rowRight, colRight, map, rowTemp, colTemp;
    static uint8_t mapLeft[8][2] = {{1,  1},
                                    {0,  1},
                                    {-1, 1},
                                    {-1, 0},
                                    {-1, -1},
                                    {0,  -1},
                                    {1,  -1},
                                    {1,  0}};
    static uint8_t mapRight[8][2] = {{-1, 1},
                                     {0,  -1},
                                     {-1, -1},
                                     {-1, 0},
                                     {-1, 1},
                                     {0,  1},
                                     {1,  1},
                                     {1,  0}};

    // Find starting pixels
    for (int i = startLeft; i < 2 * MT9V03X_W / 3; ++i)
    {
        if (PixelIsEdge(image, START_LINE, i) == 1)
            startLeft++;
        else
            break;
    }
    for (int i = startRight; i > MT9V03X_W / 3; --i)
    {
        if (PixelIsEdge(image, START_LINE, i) == 1)
            startRight--;
        else
            break;
    }
//    if (startLeft > MT9V03X_W / 2 && startRight < MT9V03X_W / 2)
//    {
//        stopFlag = 1;
//        return;
//    }
    rowLeft = START_LINE;
    colLeft = startLeft;
    rowRight = START_LINE;
    colRight = startRight;

    while (rowLeft > END_LINE || colLeft < 2 * MT9V03X_W / 3)
    {
        if (breakFlag)
            break;
        if (colLeft < 1 || colLeft > MT9V03X_W - 2)
            break;
        if (rowLeft < 1 || rowLeft > MT9V03X_H - 2)
            break;
        for (map = 0; map < 8; map++)
        {
            rowTemp = rowLeft + mapLeft[map][0];
            colTemp = colLeft + mapLeft[map][1];
            if (colTemp < 1 || colTemp > MT9V03X_W - 2)
            {
                breakFlag = 1;
                break;
            }
            if (rowTemp < 1 || rowTemp > MT9V03X_H - 2)
            {
                breakFlag = 1;
                break;
            }
            if (colLeft == 1 && map == 3)
            {
                rowLeft = rowTemp;
                colLeft = colTemp;
                sideEdges[rowLeft][0] = colLeft;
            }
            if (PixelIsEdge(image, rowTemp, colTemp) == 1)
            {
                rowLeft = rowTemp;
                colLeft = colTemp;
                if (map > 3 && sideEdges[rowLeft][0] != 0)
                    upDownEdges[1][colLeft] = rowLeft;
                else if (map <= 3 && sideEdges[rowLeft][0] != 0)
                    upDownEdges[0][colLeft] = rowLeft;
                else
                    sideEdges[rowLeft][0] = colLeft;
                break;
            }
        }
    }
    while (rowRight > END_LINE || colRight > MT9V03X_W / 3)
    {
        if (breakFlag)
            break;
        if (colRight < 1 || colRight > MT9V03X_W - 2)
            break;
        if (rowRight < 1 || rowRight > MT9V03X_H - 2)
            break;
        for (map = 0; map < 8; map++)
        {
            rowTemp = rowRight + mapRight[map][0];
            colTemp = colRight + mapRight[map][1];
            if (colTemp < 1 || colTemp > MT9V03X_W - 2)
            {
                breakFlag = 1;
                break;
            }
            if (rowTemp < 1 || rowTemp > MT9V03X_H - 2)
            {
                breakFlag = 1;
                break;
            }
            if (colRight == MT9V03X_W - 2 && map == 3)
            {
                rowRight = rowTemp;
                colRight = colTemp;
                sideEdges[rowRight][1] = colRight;
            }
            if (PixelIsEdge(image, rowTemp, colTemp) == 1)
            {
                rowRight = rowTemp;
                colRight = colTemp;
                if (map > 3 && sideEdges[rowRight][1] != 0)
                    upDownEdges[1][colRight] = rowRight;
                else if (map <= 3 && sideEdges[rowRight][1] != 0)
                    upDownEdges[0][colRight] = rowRight;
                else
                    sideEdges[rowRight][1] = colRight;
                break;
            }
        }
    }
}