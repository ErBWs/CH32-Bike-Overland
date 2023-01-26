/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "easy_ui_user_app.h"

// Pages
EasyUIPage_t pageMain, pageSpdPID, pageDirPID, pageImage, pageThreshold, pageCam, pageElement, pageSetting, pageAbout;

// Items
EasyUIItem_t titleMain, itemSpdPID, itemDirPID, itemImage, itemThreshold, itemCam, itemEle, itemSetting;
EasyUIItem_t titleSpdPID, itemSpdKp, itemSpdKi, itemSpdKd, itemSpdTarget, itemSpdInMax, itemSpdErrMax, itemSpdErrMin;
EasyUIItem_t titleDirPID, itemDirKp, itemDirKi, itemDirKd, itemDirInMax, itemDirErrMax, itemDirErrMin;
EasyUIItem_t itemTh;
EasyUIItem_t titleSetting, itemColor, itemLoop, itemBuzzer, itemSave, itemReset, itemAbout;


/*!
 * @brief   Custom page of {About}
 *
 * @param   void
 * @return  void
 */
void PageAbout(EasyUIItem_t *page)
{
    static uint8_t time = 0;
    static float x = SCREEN_WIDTH;
    static float step = (float) (SCREEN_WIDTH - 154) / 5;

    // Display about info
    IPS114_ClearBuffer();
    IPS114_ShowStr(7, 9, "SCEP");
    IPS114_SetDrawColor(XOR);
    IPS114_DrawRBox(5, 5, 4 * FONT_WIDTH + 5, ITEM_HEIGHT, IPS114_penColor);
    IPS114_SetDrawColor(NORMAL);
    IPS114_DrawBox(5, 26, 2, ITEM_HEIGHT * 4, IPS114_penColor);
    IPS114_ShowStr(36, 9, "v1.0");
    IPS114_ShowStr(10, 30, "MCU    : MM32F5");
    IPS114_ShowStr(10, 46, "EasyUI : v1.4");
    IPS114_ShowStr(10, 62, "Flash  : 256KB");
    IPS114_ShowStr(10, 78, "UID    : ");
    IPS114_ShowStr(7, 98, "Powered by:");
    IPS114_ShowStr(7, 114, ">>ErBW_s");

    // Get uid
    static uint32_t *addrBase = (uint32_t *) 0x1FFFF7E0;
    uint64_t uid;
    memcpy(&uid, addrBase, 8);
    char str[13];
    uint64_t uidBackup = uid;
    const char hex_index[16] = {
            '0', '1', '2', '3',
            '4', '5', '6', '7',
            '8', '9', 'A', 'B',
            'C', 'D', 'E', 'F'};
    int8_t data_temp[16];
    uint8_t bit = 0, i = 0;
    while(bit < 16)
    {
        data_temp[bit ++] = (uidBackup & 0xF);
        uidBackup >>= 4;
    }
    for (bit = 12 ; bit > 0; bit --)
    {
        str[i ++] = hex_index[data_temp[bit - 1]];
    }
    str[i] = '\0';
    IPS114_ShowStr(10 + 9 * FONT_WIDTH, 78, str);

    // Display profile photo
    if (time < 5)
    {
        x -= step;
        time++;
    } else
        x = 154;
    EasyUIDisplayBMP((int16_t) x, (SCREEN_HEIGHT - 56) / 2, 58, 56, ErBW_s_5856);
    if (opnExit)
    {
        time = 0;
        x = SCREEN_WIDTH;
    }
}


void PageThreshold(EasyUIItem_t *page)
{

}


void MenuInit()
{
    EasyUIAddPage(&pageMain, PAGE_LIST);
    EasyUIAddPage(&pageSpdPID, PAGE_LIST);
    EasyUIAddPage(&pageDirPID, PAGE_LIST);
    EasyUIAddPage(&pageImage, PAGE_CUSTOM);
    EasyUIAddPage(&pageThreshold, PAGE_CUSTOM, PageThreshold);
    EasyUIAddPage(&pageCam, PAGE_CUSTOM);
    EasyUIAddPage(&pageElement, PAGE_LIST);
    EasyUIAddPage(&pageSetting, PAGE_LIST);
    EasyUIAddPage(&pageAbout, PAGE_CUSTOM, PageAbout);

    // Page Main
    EasyUIAddItem(&pageMain, &titleMain, "[Main]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageMain, &itemSpdPID, "Speed PID", ITEM_JUMP_PAGE, pageSpdPID.id);
    EasyUIAddItem(&pageMain, &itemDirPID, "Direction PID", ITEM_JUMP_PAGE, pageDirPID.id);
    EasyUIAddItem(&pageMain, &itemImage, "Show Image", ITEM_JUMP_PAGE, pageImage.id);
    EasyUIAddItem(&pageMain, &itemThreshold, "Change Threshold", ITEM_JUMP_PAGE, pageThreshold.id);
    EasyUIAddItem(&pageMain, &itemEle, "Select Elements", ITEM_JUMP_PAGE, pageElement.id);
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

    // Page threshold
    EasyUIAddItem(&pageThreshold, &itemTh, "Threshold", ITEM_CHANGE_VALUE, &threshold);

    // Page setting
    EasyUIAddItem(&pageSetting, &titleSetting, "[Settings]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageSetting, &itemColor, "Reversed Color", ITEM_SWITCH, &reversedColor);
    EasyUIAddItem(&pageSetting, &itemLoop, "List Loop", ITEM_SWITCH, &listLoop);
    EasyUIAddItem(&pageSetting, &itemBuzzer, "Buzzer Volume", ITEM_CHANGE_VALUE, &buzzerVolume, EasyUIEventChangeUint);
    EasyUIAddItem(&pageSetting, &itemSave, "Save Settings", ITEM_MESSAGE, "Saving...", EasyUIEventSaveSettings);
    EasyUIAddItem(&pageSetting, &itemReset, "Reset Settings", ITEM_MESSAGE, "Resetting...", EasyUIEventResetSettings);
    EasyUIAddItem(&pageSetting, &itemAbout, "<About>", ITEM_JUMP_PAGE, pageAbout.id);
}