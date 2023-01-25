/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "menu.h"

// Pages
EasyUIPage_t pageMain, pageSpdPID, pageDirPID, pageThreshold, pageCam, pageElement, pageSetting;

// Items
EasyUIItem_t titleMain, itemSpdPID, itemDirPID, itemThreshold, itemCam, itemEle, itemSetting;
EasyUIItem_t titleSpdPID, itemSpdKp, itemSpdKi, itemSpdKd, itemSpdTarget, itemSpdInMax, itemSpdErrMax, itemSpdErrMin;
EasyUIItem_t titleDirPID, itemDirKp, itemDirKi, itemDirKd, itemDirInMax, itemDirErrMax, itemDirErrMin;
EasyUIItem_t titleSetting, itemColor, itemLoop, itemBuzzer, itemSave, itemReset;


void MenuInit()
{
    EasyUIAddPage(&pageMain, PAGE_LIST);
    EasyUIAddPage(&pageSpdPID, PAGE_LIST);
    EasyUIAddPage(&pageDirPID, PAGE_LIST);
    EasyUIAddPage(&pageThreshold, PAGE_CUSTOM);
    EasyUIAddPage(&pageCam, PAGE_CUSTOM);
    EasyUIAddPage(&pageElement, PAGE_LIST);
    EasyUIAddPage(&pageSetting, PAGE_LIST);

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
    EasyUIAddItem(&pageSetting, &itemReset, "Reset Settings", ITEM_MESSAGE, "Resetting...", EasyUIEventSaveSettings);
}