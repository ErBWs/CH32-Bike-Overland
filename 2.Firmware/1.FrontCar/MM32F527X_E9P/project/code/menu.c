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

void EventSwapColor(EasyUIItem_t *item)
{
    item->param += 0.001;
    IPS114_ClearBuffer();
    EasyUIDisplayFloat(0, 0, item->param, 4, 2);
    IPS114_SendBuffer();
}


void MenuInit()
{
    EasyUIAddPage(&pageMain, PAGE_LIST);
    EasyUIAddPage(&pageSpdPID, PAGE_LIST);
    EasyUIAddPage(&pageServoPID, PAGE_LIST);

    EasyUIAddItem(&pageMain, &titleMain, "[Main]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageMain, &main_itemRun, "Run", ITEM_CALL_FUNCTION, EventSwapColor);
    EasyUIAddItem(&pageMain, &main_itemSpdPID, "Speed PID param", ITEM_JUMP_PAGE, 1);
    EasyUIAddItem(&pageMain, &main_itemServoPID, "Servo PID param", ITEM_JUMP_PAGE, 2);
    EasyUIAddItem(&pageMain, &main_itemThreshold, "Checkbox1", ITEM_CHECKBOX, false);
    EasyUIAddItem(&pageMain, &main_itemImage, "Checkbox2", ITEM_CHECKBOX, true);
    EasyUIAddItem(&pageMain, &main_itemMultiClick, "Radio button1", ITEM_RADIO_BUTTON, false);
    EasyUIAddItem(&pageMain, &main_itemSwapColor, "Radio button2", ITEM_RADIO_BUTTON, false);
    EasyUIAddItem(&pageMain, &main_itemAbout, "Radio button3", ITEM_RADIO_BUTTON, true);
    EasyUIAddItem(&pageMain, &main_itemNone, "Switch1", ITEM_SWITCH, true);
    EasyUIAddItem(&pageMain, &main_itemWhat, "Switch2", ITEM_SWITCH, true);

    EasyUIAddItem(&pageSpdPID, &titleSpdPID, "[Speed PID]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageSpdPID, &spdPID_itemKp, "speed Kp", ITEM_CHANGE_VALUE, (float) 0.93);
    EasyUIAddItem(&pageSpdPID, &spdPID_itemKi, "speed Ki", ITEM_CHANGE_VALUE, (float) -1.90);
    EasyUIAddItem(&pageSpdPID, &spdPID_itemKd, "speed Kd", ITEM_CHANGE_VALUE, (float) 1);

    EasyUIAddItem(&pageServoPID, &titleServoSpd, "[Servo PID]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageServoPID, &servoPID_itemKp, "servo Kp", ITEM_CHANGE_VALUE, (float) 390.29);
    EasyUIAddItem(&pageServoPID, &servoPID_itemKi, "servo Ki", ITEM_CHANGE_VALUE, (float) 0);
    EasyUIAddItem(&pageServoPID, &servoPID_itemKd, "servo Kd", ITEM_CHANGE_VALUE, (float) -9985.90);
}