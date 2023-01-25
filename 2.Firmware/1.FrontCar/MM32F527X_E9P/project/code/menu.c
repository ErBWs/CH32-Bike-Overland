/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "menu.h"

// Pages
EasyUIPage_t pageMain, pageSpdPID, pageDirPID, pageThreshold, pageCam, pageElement, pageSetting, pageAbout;

// Items
EasyUIItem_t titleMain, itemSpdPID, itemDirPID, itemThreshold, itemCam, itemEle, itemSetting;
EasyUIItem_t titleSpdPID, itemSpdKp, itemSpdKi, itemSpdKd, itemSpdTarget, itemSpdInMax, itemSpdErrMax, itemSpdErrMin;
EasyUIItem_t titleDirPID, itemDirKp, itemDirKi, itemDirKd, itemDirInMax, itemDirErrMax, itemDirErrMin;
EasyUIItem_t titleSetting, itemColor, itemLoop, itemBuzzer, itemSave, itemReset, itemAbout;

void PageAbout(EasyUIItem_t *page)
{
    static uint8_t time = 0;
    static float x = SCREEN_WIDTH;
    static float step = (float) (SCREEN_WIDTH - 138) / 5;
    IPS114_ClearBuffer();
    IPS114_ShowStr(7, 9, "SCEP");
    IPS114_SetDrawColor(XOR);
    IPS114_DrawRBox(5, 5, 4 * FONT_WIDTH + 5, ITEM_HEIGHT, IPS114_penColor);
    IPS114_SetDrawColor(NORMAL);
    IPS114_DrawBox(5, 26, 2, ITEM_HEIGHT * 3, IPS114_penColor);
    IPS114_ShowStr(36, 9, "v1.0");
    IPS114_ShowStr(10, 30, "MCU   : MM32F5");
    IPS114_ShowStr(10, 46, "FW    : v1.3");
    IPS114_ShowStr(10, 62, "Flash : 256KB");
    IPS114_ShowStr(7, 92, "Powered by:");
    IPS114_ShowStr(7, 108, ">>ErBW_s");
    if (time < 5)
    {
        x -= step;
        time++;
    }
    else
        x = 138;
    EasyUIDisplayBMP((int16_t) x, (SCREEN_HEIGHT - 56) / 2, 58, 56, ErBW_s_5856);
    if (opnExit)
    {
        time = 0;
        x = SCREEN_WIDTH;
    }
}

void MenuInit()
{
    EasyUIAddPage(&pageMain, PAGE_LIST);
    EasyUIAddPage(&pageSpdPID, PAGE_LIST);
    EasyUIAddPage(&pageDirPID, PAGE_LIST);
    EasyUIAddPage(&pageThreshold, PAGE_CUSTOM);
    EasyUIAddPage(&pageCam, PAGE_CUSTOM);
    EasyUIAddPage(&pageElement, PAGE_LIST);
    EasyUIAddPage(&pageSetting, PAGE_LIST);
    EasyUIAddPage(&pageAbout, PAGE_CUSTOM, PageAbout);

    // Page Main
    EasyUIAddItem(&pageMain, &titleMain, "[Main]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageMain, &itemSpdPID, "Speed PID", ITEM_JUMP_PAGE, pageSpdPID.id);
    EasyUIAddItem(&pageMain, &itemDirPID, "Direction PID", ITEM_JUMP_PAGE, pageDirPID.id);
    EasyUIAddItem(&pageMain, &itemSetting, "Settings", ITEM_JUMP_PAGE, pageSetting.id);

    // Page speed pid
    EasyUIAddItem(&pageSpdPID, &titleSpdPID, "[Speed PID]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageSpdPID, &itemSpdKp, "Kp", ITEM_CHANGE_VALUE, &spdParam.kp, EasyUIEventChangeFloat);
    EasyUIAddItem(&pageSpdPID, &itemSpdKi, "Ki", ITEM_CHANGE_VALUE, &spdParam.ki, EasyUIEventChangeFloat);
    EasyUIAddItem(&pageSpdPID, &itemSpdKd, "Kd", ITEM_CHANGE_VALUE, &spdParam.kd, EasyUIEventChangeFloat);
    EasyUIAddItem(&pageSpdPID, &itemSpdTarget, "Target Speed", ITEM_CHANGE_VALUE, &spdParam.targetVal,
                  EasyUIEventChangeFloat);
    EasyUIAddItem(&pageSpdPID, &itemSpdInMax, "Max Integral", ITEM_CHANGE_VALUE, &spdParam.integralMax,
                  EasyUIEventChangeUint);
    EasyUIAddItem(&pageSpdPID, &itemSpdErrMax, "Max Error", ITEM_CHANGE_VALUE, &spdParam.errMax,
                  EasyUIEventChangeUint);
    EasyUIAddItem(&pageSpdPID, &itemSpdErrMin, "Min Error", ITEM_CHANGE_VALUE, &spdParam.errMin,
                  EasyUIEventChangeUint);

    // Page direction pid
    EasyUIAddItem(&pageDirPID, &titleDirPID, "[Direction PID]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageDirPID, &itemDirKp, "Kp", ITEM_CHANGE_VALUE, &dirParam.kp, EasyUIEventChangeFloat);
    EasyUIAddItem(&pageDirPID, &itemDirKi, "Ki", ITEM_CHANGE_VALUE, &dirParam.ki, EasyUIEventChangeFloat);
    EasyUIAddItem(&pageDirPID, &itemDirKd, "Kd", ITEM_CHANGE_VALUE, &dirParam.kd, EasyUIEventChangeFloat);
    EasyUIAddItem(&pageDirPID, &itemDirInMax, "Max Integral", ITEM_CHANGE_VALUE, &dirParam.integralMax,
                  EasyUIEventChangeUint);
    EasyUIAddItem(&pageDirPID, &itemDirErrMax, "Max Error", ITEM_CHANGE_VALUE, &dirParam.errMax,
                  EasyUIEventChangeUint);
    EasyUIAddItem(&pageDirPID, &itemDirErrMin, "Min Error", ITEM_CHANGE_VALUE, &dirParam.errMin,
                  EasyUIEventChangeUint);

    // Page setting
    EasyUIAddItem(&pageSetting, &titleSetting, "[Settings]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageSetting, &itemColor, "Reversed Color", ITEM_SWITCH, &reversedColor);
    EasyUIAddItem(&pageSetting, &itemLoop, "List Loop", ITEM_SWITCH, &listLoop);
    EasyUIAddItem(&pageSetting, &itemBuzzer, "Buzzer Volume", ITEM_CHANGE_VALUE, &buzzerVolume, EasyUIEventChangeUint);
    EasyUIAddItem(&pageSetting, &itemSave, "Save Settings", ITEM_MESSAGE, "Saving...", EasyUIEventSaveSettings);
    EasyUIAddItem(&pageSetting, &itemReset, "Reset Settings", ITEM_MESSAGE, "Resetting...", EasyUIEventResetSettings);
    EasyUIAddItem(&pageSetting, &itemAbout, "<About>", ITEM_JUMP_PAGE, pageAbout.id);
}