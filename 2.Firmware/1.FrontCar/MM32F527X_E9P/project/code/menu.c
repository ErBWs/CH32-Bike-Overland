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
    ips114_show_float(0, 0, -12345678.23, 8, 2);
}


void MenuInit()
{
    EasyUIAddPage(&pageMain, PAGE_LIST);
    EasyUIAddPage(&pageSpdPID, PAGE_LIST);
    EasyUIAddPage(&pageServoPID, PAGE_LIST);

    EasyUIAddItem(&pageMain, &titleMain, "[Main]", ITEM_PAGE_DESCRIPTION);
//    EasyUIAddItem(&pageMain, &main_itemRun, "Run", ITEM_CALL_FUNCTION, EventSwapColor);
    EasyUIAddItem(&pageMain, &main_itemSpdPID, "Change Value", ITEM_JUMP_PAGE, pageSpdPID.id);
    EasyUIAddItem(&pageMain, &main_itemThreshold, "Checkbox1", ITEM_CHECKBOX, false);
    EasyUIAddItem(&pageMain, &main_itemImage, "Checkbox2", ITEM_CHECKBOX, true);
    EasyUIAddItem(&pageMain, &main_itemMultiClick, "Radio button1", ITEM_RADIO_BUTTON, false);
    EasyUIAddItem(&pageMain, &main_itemSwapColor, "Radio button2", ITEM_RADIO_BUTTON, false);
    EasyUIAddItem(&pageMain, &main_itemAbout, "Radio button3", ITEM_RADIO_BUTTON, true);
    EasyUIAddItem(&pageMain, &main_itemNone, "Switch1", ITEM_SWITCH, true);
    EasyUIAddItem(&pageMain, &main_itemWhat, "Switch2", ITEM_SWITCH, true);

    EasyUIAddItem(&pageSpdPID, &titleSpdPID, "[Change Value]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageSpdPID, &spdPID_itemKp, "Test float", ITEM_CHANGE_VALUE, 0.73, EasyUIEventChangeFloat);
    EasyUIAddItem(&pageSpdPID, &spdPID_itemKi, "Test int", ITEM_CHANGE_VALUE, 3.0, EasyUIEventChangeInt);
    EasyUIAddItem(&pageSpdPID, &spdPID_itemKd, "Test unsigned int", ITEM_CHANGE_VALUE, 14.0, EasyUIEventChangeUint);
}