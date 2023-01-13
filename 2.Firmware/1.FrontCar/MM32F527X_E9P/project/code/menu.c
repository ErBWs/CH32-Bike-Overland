/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "menu.h"

EasyUIPage_t pageMain, pageSpdPID, pageServoPID;
EasyUIItem_t main_itemRun, main_itemSpdPID, main_itemServoPID, main_itemThreshold, main_itemImage;
EasyUIItem_t main_itemMultiClick, main_itemSwapColor, main_itemAbout, main_itemNone, main_itemWhat;
EasyUIItem_t spdPID_itemKp, spdPID_itemKi, spdPID_itemKd;
EasyUIItem_t servoPID_itemKp, servoPID_itemKi, servoPID_itemKd;

void MenuInit()
{
    EasyUIAddPage(&pageMain);
    EasyUIAddPage(&pageSpdPID);
    EasyUIAddPage(&pageServoPID);

    EasyUIAddItem(&pageMain, &main_itemRun, "Run", JUMP_PAGE, 4);
    EasyUIAddItem(&pageMain, &main_itemSpdPID, "Speed PID param", JUMP_PAGE, 1);
    EasyUIAddItem(&pageMain, &main_itemServoPID, "Servo PID param", JUMP_PAGE, 2);
    EasyUIAddItem(&pageMain, &main_itemThreshold, "Camera threshold", JUMP_PAGE, 4);
    EasyUIAddItem(&pageMain, &main_itemImage, "Show camera image", JUMP_PAGE, 4);
    EasyUIAddItem(&pageMain, &main_itemMultiClick, "MultiClick switch", JUMP_PAGE, 4);
    EasyUIAddItem(&pageMain, &main_itemSwapColor, "Swap screen color", JUMP_PAGE, 4);
    EasyUIAddItem(&pageMain, &main_itemAbout, "About", JUMP_PAGE, 4);
    EasyUIAddItem(&pageMain, &main_itemNone, "NULL", JUMP_PAGE, 4);
    EasyUIAddItem(&pageMain, &main_itemWhat, "Don't know what to write", JUMP_PAGE, 4);

    EasyUIAddItem(&pageSpdPID, &spdPID_itemKp, "Kp", JUMP_PAGE, 0);
    EasyUIAddItem(&pageSpdPID, &spdPID_itemKi, "Ki", JUMP_PAGE, 0);
    EasyUIAddItem(&pageSpdPID, &spdPID_itemKd, "Kd", JUMP_PAGE, 0);

    EasyUIAddItem(&pageServoPID, &servoPID_itemKp, "Kp", JUMP_PAGE, 0);
    EasyUIAddItem(&pageServoPID, &servoPID_itemKi, "Ki", JUMP_PAGE, 0);
    EasyUIAddItem(&pageServoPID, &servoPID_itemKd, "Kd", JUMP_PAGE, 0);
}