/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan
 */

#include "easy_ui_user_app.h"

// Pages
EasyUIPage_t pageWelcome, pageMain, pagePreset, pageSpdPID, pageDirPID, pageImage, pageThreshold, pageCam, pageElement, pageSetting, pageAbout;

// Items
EasyUIItem_t titleMain, itemRun, itemPreset, itemSpdPID, itemDirPID, itemImage, itemThreshold, itemCam, itemEle, itemSetting;
EasyUIItem_t titlePreset, itemPr1, itemPr2, itemPr3;
EasyUIItem_t titleSpdPID, itemSpdKp, itemSpdKi, itemSpdKd, itemSpdTarget, itemSpdInMax, itemSpdErrMax, itemSpdErrMin;
EasyUIItem_t titleDirPID, itemDirKp, itemDirKi, itemDirKd, itemDirInMax, itemDirErrMax, itemDirErrMin;
EasyUIItem_t itemExp, itemTh;
EasyUIItem_t titleEle, itemLoop, itemCross, itemLeftR, itemRightR, itemBreak, itemObstacle, itemGarage;
EasyUIItem_t titleSetting, itemColor, itemListLoop, itemBuzzer, itemSave, itemReset, itemAbout;


void EventMainLoop(EasyUIItem_t *item)
{
//    printf("%f\n", Gp2yGetDistance());

    if (opnExit)
    {
        functionIsRunning = false;
        EasyUIBackgroundBlur();
    }
}


void EventChangeBuzzerVolume(EasyUIItem_t *item)
{
    if (opnUp)
    {
        if (*item->param + 10 <= 100)
            *item->param += 10;
        else
            *item->param = 100;
    }
    if (opnDown)
    {
        if (*item->param - 10 >= 0)
            *item->param -= 10;
        else
            *item->param = 0;
    }

    if (opnEnter)
    {
        item->paramBackup = *item->param;
        EasyUIBackgroundBlur();
        functionIsRunning = false;
    }
    if (opnExit)
    {
        *item->param = item->paramBackup;
        EasyUIBackgroundBlur();
        functionIsRunning = false;
    }
}


void PageWelcome(EasyUIPage_t *page)
{
    static uint8_t count = 50;
    static float voltage = 0.0;
    if (count++ >= 50)
    {
        voltage = EasyUIGetBatteryVoltage();
        count = 0;
    }
    IPS096_ShowStr(143, 106, "Battery Voltage:");
    IPS096_ShowFloat(209, 121, voltage, 1, 2);
    IPS096_ShowStr(233, 121, "V");

    IPS096_ShowStr(7, 9, page->itemHead->title);
    uint8_t len = strlen(page->itemHead->title);
    IPS096_SetDrawColor(XOR);
    IPS096_DrawRBox(5, 5, len * FONT_WIDTH + 5, ITEM_HEIGHT, IPS096_penColor, 1);
    IPS096_SetDrawColor(NORMAL);
    IPS096_ShowStr(7, 25, "*1.Press <Center> to run");
    IPS096_ShowStr(7, 41, " 2.Hold <Center> to enter settings");

    if (opnEnter)
    {
        functionIsRunning = true;
        EasyUIDrawMsgBox(page->itemHead->msg);
    }
}


/*!
 * @brief   Custom page of Image
 *
 * @param   page    Useless param
 * @return  void
 */
void PageImage(EasyUIPage_t *page)
{
    if (opnUp)
    {
        if (*page->itemHead->param + 10 <= 500)
            *page->itemHead->param += 10;
        else
            *page->itemHead->param = 500;
    }
    if (opnDown)
    {
        if (*page->itemHead->param - 10 >= 100)
            *page->itemHead->param -= 10;
        else
            *page->itemHead->param = 0;
    }
}


/*!
 * @brief   Custom page of {About}
 *
 * @param   page    EasyUI page struct
 * @return  void
 */
void PageThreshold(EasyUIPage_t *page)
{
    IPS096_ShowStr(7, 9, page->itemHead->title);
    uint8_t len = strlen(page->itemHead->title);
    IPS096_SetDrawColor(XOR);
    IPS096_DrawRBox(5, 5, len * FONT_WIDTH + 5, ITEM_HEIGHT, IPS096_penColor, 1);
    IPS096_SetDrawColor(NORMAL);
    if (opnUp)
    {
        if (*page->itemHead->param + 10 <= 255)
            *page->itemHead->param += 10;
        else
            *page->itemHead->param = 255;
    }
    if (opnDown)
    {
        if (*page->itemHead->param - 10 >= 0)
            *page->itemHead->param -= 10;
        else
            *page->itemHead->param = 0;
    }
    IPS096_ShowFloat(7 + len * FONT_WIDTH + 5, 9, (float) *page->itemHead->param, 3, 2);
}


/*!
 * @brief   Custom page of {About}
 *
 * @param   page    Useless param
 * @return  void
 */
void PageAbout(EasyUIItem_t *page)
{
    static uint8_t time = 0;
    static float x = SCREEN_WIDTH;
    static float step = (float) (SCREEN_WIDTH - 154) / 5;

    // Display about info
    IPS096_ClearBuffer();
    IPS096_ShowStr(7, 9, "SCEP");
    IPS096_SetDrawColor(XOR);
    IPS096_DrawRBox(5, 5, 4 * FONT_WIDTH + 5, ITEM_HEIGHT, IPS096_penColor, 1);
    IPS096_SetDrawColor(NORMAL);
    IPS096_DrawBox(5, 26, 2, ITEM_HEIGHT * 4, IPS096_penColor);
    IPS096_ShowStr(36, 9, "v1.0");
    IPS096_ShowStr(10, 30, "MCU    : MM32F5");
    IPS096_ShowStr(10, 46, "EasyUI : ");
    IPS096_ShowStr(10 + 9 * FONT_WIDTH, 46, EasyUIVersion);
    IPS096_ShowStr(10, 62, "Flash  : 256KB");
    IPS096_ShowStr(10, 78, "UID    : ");
    IPS096_ShowStr(7, 98, "Powered by:");
    IPS096_ShowStr(7, 114, ">>ErBW_s");

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
    while (bit < 16)
    {
        data_temp[bit++] = (uidBackup & 0xF);
        uidBackup >>= 4;
    }
    for (bit = 12; bit > 0; bit--)
    {
        str[i++] = hex_index[data_temp[bit - 1]];
    }
    str[i] = '\0';
    IPS096_ShowStr(10 + 9 * FONT_WIDTH, 78, str);

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


void MenuInit()
{
//    EasyUIAddPage(&pageWelcome, PAGE_CUSTOM, PageWelcome);
    EasyUIAddPage(&pageMain, PAGE_LIST);
    EasyUIAddPage(&pagePreset, PAGE_LIST);
    EasyUIAddPage(&pageSpdPID, PAGE_LIST);
    EasyUIAddPage(&pageDirPID, PAGE_LIST);
    EasyUIAddPage(&pageImage, PAGE_CUSTOM, PageImage);
    EasyUIAddPage(&pageThreshold, PAGE_CUSTOM, PageThreshold);
    EasyUIAddPage(&pageCam, PAGE_CUSTOM);
    EasyUIAddPage(&pageElement, PAGE_LIST);
    EasyUIAddPage(&pageSetting, PAGE_LIST);
    EasyUIAddPage(&pageAbout, PAGE_CUSTOM, PageAbout);

    // Page Welcome
    EasyUIAddItem(&pageWelcome, &itemRun, "Welcome!", ITEM_MESSAGE, "Running...", EventMainLoop);

    // Page Main
    EasyUIAddItem(&pageMain, &titleMain, "[Main]", ITEM_PAGE_DESCRIPTION);
//    EasyUIAddItem(&pageMain, &itemRun, "Run", ITEM_MESSAGE, "Running...", EventMainLoop);
    EasyUIAddItem(&pageMain, &itemPreset, "Param Presets", ITEM_JUMP_PAGE, pagePreset.id);
    EasyUIAddItem(&pageMain, &itemSpdPID, "Speed PID", ITEM_JUMP_PAGE, pageSpdPID.id);
    EasyUIAddItem(&pageMain, &itemDirPID, "Direction PID", ITEM_JUMP_PAGE, pageDirPID.id);
    EasyUIAddItem(&pageMain, &itemImage, "Show Image", ITEM_JUMP_PAGE, pageImage.id);
    EasyUIAddItem(&pageMain, &itemThreshold, "Change Threshold", ITEM_JUMP_PAGE, pageThreshold.id);
    EasyUIAddItem(&pageMain, &itemEle, "Select Elements", ITEM_JUMP_PAGE, pageElement.id);
    EasyUIAddItem(&pageMain, &itemSetting, "Settings", ITEM_JUMP_PAGE, pageSetting.id);

    // Page speed pid
    EasyUIAddItem(&pageSpdPID, &titleSpdPID, "[Speed PID]", ITEM_PAGE_DESCRIPTION);

    // Page direction pid
    EasyUIAddItem(&pageDirPID, &titleDirPID, "[Direction PID]", ITEM_PAGE_DESCRIPTION);

    // Page elements
    EasyUIAddItem(&pageElement, &titleEle, "[Select Elements]", ITEM_PAGE_DESCRIPTION);
    // Page setting
    EasyUIAddItem(&pageSetting, &titleSetting, "[Settings]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageSetting, &itemColor, "Reversed Color", ITEM_SWITCH, &reversedColor);
    EasyUIAddItem(&pageSetting, &itemListLoop, "List Loop", ITEM_SWITCH, &listLoop);
//    EasyUIAddItem(&pageSetting, &itemBuzzer, "Buzzer Volume", ITEM_PROGRESS_BAR, &buzzerVolume, EventChangeBuzzerVolume);
    EasyUIAddItem(&pageSetting, &itemSave, "Save Settings", ITEM_MESSAGE, "Saving...", EasyUIEventSaveSettings);
    EasyUIAddItem(&pageSetting, &itemReset, "Reset Settings", ITEM_MESSAGE, "Resetting...", EasyUIEventResetSettings);
    EasyUIAddItem(&pageSetting, &itemAbout, "<About>", ITEM_JUMP_PAGE, pageAbout.id);
}