/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "menu.h"

EasyUIPage_t pageMain, pageSpdPID, pageServoPID;
EasyUIItem_t titleMain, titleSpdPID, titleServoSpd;
EasyUIItem_t main_itemRun, main_itemSpdPID, main_itemServoPID, main_itemThreshold, main_itemImage;
EasyUIItem_t main_itemMultiClick, main_itemSwapColor, main_itemAbout, main_itemNone, main_itemWhat;
EasyUIItem_t spdPID_itemKp, spdPID_itemKi, spdPID_itemKd;
EasyUIItem_t servoPID_itemKp, servoPID_itemKi, servoPID_itemKd;

void EventSwapColor(uint8_t cnt, ...)
{
    uint16_t tmp = IPS114_penColor;
    IPS114_penColor = IPS114_backgroundColor;
    IPS114_backgroundColor = tmp;
}


void MenuInit()
{
    EasyUIAddPage(&pageMain);
    EasyUIAddPage(&pageSpdPID);
    EasyUIAddPage(&pageServoPID);

    EasyUIAddItem(&pageMain, &titleMain, "[Main]", PAGE_DESCRIPTION);
    EasyUIAddItem(&pageMain, &main_itemRun, "Run", JUMP_PAGE, 0);
    EasyUIAddItem(&pageMain, &main_itemSpdPID, "Speed PID param", JUMP_PAGE, 1);
    EasyUIAddItem(&pageMain, &main_itemServoPID, "Servo PID param", JUMP_PAGE, 2);
    EasyUIAddItem(&pageMain, &main_itemThreshold, "Camera threshold", JUMP_PAGE, 0);
    EasyUIAddItem(&pageMain, &main_itemImage, "Show camera image", JUMP_PAGE, 0);
    EasyUIAddItem(&pageMain, &main_itemMultiClick, "MultiClick switch", JUMP_PAGE, 0);
    EasyUIAddItem(&pageMain, &main_itemSwapColor, "Swap screen color", CALL_FUNCTION, EventSwapColor);
    EasyUIAddItem(&pageMain, &main_itemAbout, "About", JUMP_PAGE, 0);
    EasyUIAddItem(&pageMain, &main_itemNone, "NULL", JUMP_PAGE, 0);
    EasyUIAddItem(&pageMain, &main_itemWhat, "Don't know what to write", JUMP_PAGE, 0);

    EasyUIAddItem(&pageSpdPID, &titleSpdPID, "[Speed PID]", PAGE_DESCRIPTION);
    EasyUIAddItem(&pageSpdPID, &spdPID_itemKp, "speed Kp", JUMP_PAGE, 0);
    EasyUIAddItem(&pageSpdPID, &spdPID_itemKi, "speed Ki", JUMP_PAGE, 0);
    EasyUIAddItem(&pageSpdPID, &spdPID_itemKd, "speed Kd", JUMP_PAGE, 0);

    EasyUIAddItem(&pageServoPID, &titleServoSpd, "[Servo PID]", PAGE_DESCRIPTION);
    EasyUIAddItem(&pageServoPID, &servoPID_itemKp, "servo Kp", JUMP_PAGE, 0);
    EasyUIAddItem(&pageServoPID, &servoPID_itemKi, "servo Ki", JUMP_PAGE, 0);
    EasyUIAddItem(&pageServoPID, &servoPID_itemKd, "servo Kd", JUMP_PAGE, 0);
}