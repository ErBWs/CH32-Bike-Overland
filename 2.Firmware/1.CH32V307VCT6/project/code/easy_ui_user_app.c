/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan
 */

#include "easy_ui_user_app.h"
#include "inc_all.h"
// Pages
EasyUIPage_t pageWelcome, pageMain, pagePreset, pageSpdPID, pageDirPID, pageBackMotorPID, pageThreshold, pageCam, pagePoints, pageNormalPoints, pagePilePoints, pagePathGenerate,pageBasePoints, pageSetting, pageAbout;

// Items
EasyUIItem_t titleMain, itemRun, itemPreset, itemSpdPID, itemDirPID, itemBackMotor, itemThreshold, itemCam, itemGPS, itemSetting;
EasyUIItem_t titleGPS, itemNormalPoints, itemPilePoints, itemBasePoints, itemPathGenerate, itemSavePoints, itemReadPoints;
EasyUIItem_t titleSpdPID, itemSpdKp, itemSpdKi, itemSpdKd, itemAngKp, itemAngKi, itemAngKd, itemAngSpdKp, itemAngSpdKi, itemAngSpdKd, KpitemSpdTarget, itemSpdInMax, itemSpdErrMax, itemSpdErrMin;
EasyUIItem_t titleDirPID, itemDirKp, itemDirKi, itemDirKd, itemDirInMax, itemDirErrMax, itemDirErrMin;
EasyUIItem_t titleBackMotorPID, itemBackMotorKp, itemBackMotorKi, itemBackMotorKd, itemBackMotorInMax, itemBackMotorErrMax, itemBackMotorErrMin;
EasyUIItem_t itemExp, itemTh;
EasyUIItem_t titleEle, itemLoop, itemCross, itemLeftR, itemRightR, itemBreak, itemObstacle, itemGarage;
EasyUIItem_t titleSetting, itemColor, itemListLoop, itemBuzzer, itemSave, itemReset, itemAbout;


void EventMainLoop(EasyUIItem_t *item)
{
#if USE_GPS
    if(Bike_Start ==0)
    {
        stanleyControllerInit(&Global_stanleyController,(float)0.1,(float)0.2,&Global_yaw,&Global_v_now,&Global_current_node);
        stanleyBuffLink(&Global_stanleyController,Global_pd_array,NULL,GlobalGraph.total);
        stanley_GraphRegister(&GlobalGraph,&Global_stanleyController);
        GraphNode_Diff(&GlobalGraph);
        Bike_Start = 1;
    }
    while(1)
    {
        Stanley_Control(&GlobalGraph);
        gps_use.delta = RAD_TO_ANGLE(GlobalGraph.Stanley_controller->theta);
        if(GlobalGraph.is_finish)
        {
            GlobalGraph.is_finish = 0;
            //stagger_flag=1;
            //motoDutySet(MOTOR_FLY_PIN,0);
            functionIsRunning = false;
            beep_time = 70;
            Bike_Start = 0;
            break;
        }
    }
#endif
    if (opnExit)
    {
        Bike_Start = 0;
        opnExit = false;
        functionIsRunning = false;
        EasyUIBackgroundBlur();
    }
}

void EventSavePoints(EasyUIItem_t *item)
{
    if(gps_use.point_count!=0)
    {
        double count = gps_use.point_count;
        GPSSaveToFlashWithConversion(&count);
        for(uint8 k=0;k<gps_use.point_count;k++)
        {
            GPSSaveToFlashWithConversion(&gps_data_array[k].latitude);
            GPSSaveToFlashWithConversion(&gps_data_array[k].longitude);
            double temp = gps_data_array[k].type;
            GPSSaveToFlashWithConversion(&temp);
        }
    }
    gps_data = gps_data_array[0];//获得第一个目标点
    gps_use.use_point_count=1;
    GPSFlashOperationEnd();
    EasyUIDrawMsgBox("Finish...");
    functionIsRunning = false;
    EasyUIBackgroundBlur();
}

void EventReadPoints(EasyUIPage_t *item)
{
    GPSFlashOperationEnd();
    memset(gps_data_array, 0, sizeof(_gps_st) * GPS_MAX_POINT);//清空数组准备录入新的数据
    memset(&gps_use, 0, sizeof(_gps_use_st));//清空记录信息准备录入新的数据
    double count;
    GPSReadFlashWithConversion(&count);//写完点后取消读点模式，以便下一次随时进入写点模式。
    gps_use.point_count = (uint8) count;
    for (uint8 k = 0; k < gps_use.point_count; k++) {
        GPSReadFlashWithConversion(&gps_data_array[k].latitude);
        GPSReadFlashWithConversion(&gps_data_array[k].longitude);
        GPSReadFlashWithConversion((double *)&gps_data_array[k].type);
    }
    gps_data = gps_data_array[0];//获得第一个目标点
    gps_use.use_point_count = 1;

    functionIsRunning = false;
    EasyUIBackgroundBlur();
}
#define PATH_TOTAL_COUNTS 100
#if PATH_TOTAL_COUNTS > GRAPH_NODE_TOTAL
#error Too Many Points!
#endif
void PagePathGenerate(EasyUIPage_t *item)
{
    if(gps_use.point_count<=1)
    {
        EasyUIDrawMsgBox("Points Not Enough!");
        return;
    }
    if(gps_use.point_count > B_REFER_POINT_COUNTS_MAX)
    {
        EasyUIDrawMsgBox("B_Buff Not Enough!");
        return;
    }
    if(gps_use.point_count > GRAPH_NODE_TOTAL)
    {
        EasyUIDrawMsgBox("G_Buff Not Enough!");
        return;
    }
    GraphInit(&GlobalGraph, GlobalGraph_NodeBuffer, &GlobalBase_GPS_data, PATH_TOTAL_COUNTS);
    B_ConstructorInit(&Global_B_Constructor, gps_use.point_count, B_ORDER);
    B_ConstructorBuffLink(&Global_B_Constructor, GlobalNodeVector, GlobalNipFactorVector, GlobalRefNodeList);
    B_GraphRegister(&GlobalGraph, &Global_B_Constructor);
    GraphReferNodeConvertInput(&GlobalGraph,(gpsDataLink_typedef)gps_data_array,gps_use.point_count);
    GraphPathGenerate(&GlobalGraph);

    EasyUIDrawMsgBox("Finish!");
    functionIsRunning = false;
    EasyUIBackgroundBlur();
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
void MessegeShowFun(void)
{
    IPS096_ShowStr(0,2,"latitude:");
    IPS096_ShowStr(0, 14, "longitude:");
    IPS096_ShowStr(0, 26, "hdop:");
    IPS096_ShowStr(0, 38, "time:  :  ");
    IPS096_ShowStr(0, 38+12, "satellite_used:");
    IPS096_ShowStr(0, 38+12+12, "yaw:");
    IPS096_ShowFloat(54, 2, gps_tau1201.latitude,3,6);
    IPS096_ShowFloat(60, 14, gps_tau1201.longitude,3,6);
    IPS096_ShowFloat(30, 26, gps_tau1201.hdop,2,2);
    IPS096_ShowUint(30, 38, gps_tau1201.time.minute,2);
    IPS096_ShowUint(50, 38, gps_tau1201.time.second,2);
    IPS096_ShowUint(92, 38+12, gps_tau1201.satellite_used,2);
    IPS096_ShowFloat(4*8, 38+12+12, imu_data.mag_yaw,3,3);
}
void PageNormalPoints(EasyUIPage_t *page)
{
    gpsState pointStatus = COMMON;
    MessegeShowFun();
    gps_handler(pointStatus);
}

void PagePilePoints(EasyUIPage_t *page)
{
    gpsState pointStatus = PILE;
    MessegeShowFun();
    gps_handler(pointStatus);
}

void PageBasePoints(EasyUIPage_t *page)
{
    gpsState pointStatus = BASE;
    MessegeShowFun();
    gps_handler(pointStatus);
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
    static float step = (float) (SCREEN_WIDTH - 115) / 5;

    // Display about info
    IPS096_ClearBuffer();
    IPS096_ShowStr(3, 4, "SCEP");
    IPS096_SetDrawColor(XOR);
    IPS096_DrawRBox(1, 1, 4 * FONT_WIDTH + 5, ITEM_HEIGHT, IPS096_penColor, 1);
    IPS096_SetDrawColor(NORMAL);
    IPS096_DrawBox(2, 16, 2, ITEM_HEIGHT * 5, IPS096_penColor);
    IPS096_ShowStr(36, 4, "v1.2");
    IPS096_ShowStr(8, 18, "MCU    : CH32V3");
    IPS096_ShowStr(8, 30, "EasyUI : ");
    IPS096_ShowStr(8 + 9 * FONT_WIDTH, 30, EasyUIVersion);
    IPS096_ShowStr(8, 42, "Flash  : 256KB");
    IPS096_ShowStr(8, 54, "UID    : ");
    IPS096_ShowStr(8, 66, ">> Powered by: ErBW_s");

    // Get uid
    static uint32_t *addrBase = (uint32_t *) 0x1FFFF7E8;
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
    IPS096_ShowStr(8 + 9 * FONT_WIDTH, 54, str);

    // Display profile photo
    if (time < 5)
    {
        x -= step;
        time++;
    } else
        x = 115;
    EasyUIDisplayBMP((int16_t) x, (SCREEN_HEIGHT - 56) / 2, 29, 28, ErBW_s_2928);
    if (opnExit)
    {
        time = 0;
        x = SCREEN_WIDTH;
    }
}


void MenuInit()
{
    EasyUIAddPage(&pageMain, PAGE_LIST);
    EasyUIAddPage(&pagePoints, PAGE_LIST);
    EasyUIAddPage(&pageSpdPID, PAGE_LIST);
    EasyUIAddPage(&pageDirPID, PAGE_LIST);
    EasyUIAddPage(&pageBackMotorPID, PAGE_LIST);
    EasyUIAddPage(&pageBasePoints, PAGE_CUSTOM, PageBasePoints);
    EasyUIAddPage(&pageNormalPoints, PAGE_CUSTOM, PageNormalPoints);
    EasyUIAddPage(&pagePilePoints, PAGE_CUSTOM, PagePilePoints);
    EasyUIAddPage(&pagePathGenerate, PAGE_CUSTOM, PagePathGenerate);
    EasyUIAddPage(&pageSetting, PAGE_LIST);
    EasyUIAddPage(&pageAbout, PAGE_CUSTOM, PageAbout);

    // Page Main
    EasyUIAddItem(&pageMain, &titleMain, "[Main]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageMain, &itemRun, "Run", ITEM_MESSAGE, "Running...", EventMainLoop);
    EasyUIAddItem(&pageMain, &itemGPS, "GPS Points", ITEM_JUMP_PAGE, pagePoints.id);
    EasyUIAddItem(&pageMain, &itemSpdPID, "Speed PID", ITEM_JUMP_PAGE, pageSpdPID.id);
    EasyUIAddItem(&pageMain, &itemDirPID, "Direction PID", ITEM_JUMP_PAGE, pageDirPID.id);
    EasyUIAddItem(&pageMain, &itemBackMotor, "BackMotor PID", ITEM_JUMP_PAGE, pageBackMotorPID.id);
    EasyUIAddItem(&pageMain, &itemSetting, "Settings", ITEM_JUMP_PAGE, pageSetting.id);

    // Page GPS points
    EasyUIAddItem(&pagePoints, &titleGPS, "[GPS Points]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pagePoints, &itemBasePoints, "Base Points", ITEM_JUMP_PAGE, pageBasePoints.id);
    EasyUIAddItem(&pagePoints, &itemNormalPoints, "Normal Points", ITEM_JUMP_PAGE, pageNormalPoints.id);
    EasyUIAddItem(&pagePoints, &itemPilePoints, "Pile Points", ITEM_JUMP_PAGE, pagePilePoints.id);
    EasyUIAddItem(&pagePoints, &itemPathGenerate, "Path Generate", ITEM_JUMP_PAGE, pagePathGenerate.id);

    EasyUIAddItem(&pagePoints, &itemSavePoints, "Save", ITEM_MESSAGE, "Saving...", EventSavePoints);
    EasyUIAddItem(&pagePoints, &itemReadPoints, "Read", ITEM_MESSAGE, "Reading...", EventReadPoints);
    
    // Page Fly speed pid
    EasyUIAddItem(&pageSpdPID, &titleSpdPID, "[Fly Speed PID]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageSpdPID, &itemSpdKp, "FlySpeed Kp", ITEM_CHANGE_VALUE, &flySpdPid.Kp, EasyUIEventChangeFloat);
//    EasyUIAddItem(&pageSpdPID, &itemSpdKi, "FlySpeed Ki", ITEM_CHANGE_VALUE, &flySpdPid.Ki, EasyUIEventChangeFloat);
//    EasyUIAddItem(&pageSpdPID, &itemSpdKd, "FlySpeed Kd", ITEM_CHANGE_VALUE, &flySpdPid.Kd, EasyUIEventChangeFloat);
    EasyUIAddItem(&pageSpdPID, &itemAngKp, "FlyAngle Kp", ITEM_CHANGE_VALUE, &flyAnglePid.Kp, EasyUIEventChangeFloat);
//    EasyUIAddItem(&pageSpdPID, &itemAngKi, "FlyAngle Ki", ITEM_CHANGE_VALUE, &flyAnglePid.Ki, EasyUIEventChangeFloat);
//    EasyUIAddItem(&pageSpdPID, &itemAngKd, "FlyAngle Kd", ITEM_CHANGE_VALUE, &flyAnglePid.Kd, EasyUIEventChangeFloat);
    EasyUIAddItem(&pageSpdPID, &itemAngSpdKp, "FlyAngleSpd Kp", ITEM_CHANGE_VALUE, &flyAngleSpdPid.Kp, EasyUIEventChangeFloat);
    EasyUIAddItem(&pageSpdPID, &itemAngSpdKi, "FlyAngleSpd Ki", ITEM_CHANGE_VALUE, &flyAngleSpdPid.Ki, EasyUIEventChangeFloat);
//    EasyUIAddItem(&pageSpdPID, &itemAngSpdKd, "FlyAngleSpd Kd", ITEM_CHANGE_VALUE, &flyAngleSpdPid.Kd, EasyUIEventChangeFloat);
    
    // Page direction pid
    EasyUIAddItem(&pageDirPID, &titleDirPID, "[Direction PID]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageDirPID, &itemDirKp, "Dir Kp", ITEM_CHANGE_VALUE, &dirPid.Kp, EasyUIEventChangeFloat);
    EasyUIAddItem(&pageDirPID, &itemDirKd, "Dir Kd", ITEM_CHANGE_VALUE, &dirPid.Kd, EasyUIEventChangeFloat);
    
    //Page BackMotor pid
    EasyUIAddItem(&pageBackMotorPID, &titleBackMotorPID, "[BackMotor PID]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageBackMotorPID, &itemBackMotorKp, "BackMotor Kp", ITEM_CHANGE_VALUE, &backSpdPid.Kp, EasyUIEventChangeFloat);
    EasyUIAddItem(&pageBackMotorPID, &itemBackMotorKi, "BackMotor Ki", ITEM_CHANGE_VALUE, &backSpdPid.Ki, EasyUIEventChangeFloat);

    
    

    // Page setting
    EasyUIAddItem(&pageSetting, &titleSetting, "[Settings]", ITEM_PAGE_DESCRIPTION);
    EasyUIAddItem(&pageSetting, &itemColor, "Reversed Color", ITEM_SWITCH, &reversedColor);
    EasyUIAddItem(&pageSetting, &itemListLoop, "List Loop", ITEM_SWITCH, &listLoop);
    
//    EasyUIAddItem(&pageSetting, &itemBuzzer, "Buzzer Volume", ITEM_PROGRESS_BAR, &buzzerVolume, EventChangeBuzzerVolume);
    EasyUIAddItem(&pageSetting, &itemSave, "Save Settings", ITEM_MESSAGE, "Saving...", EasyUIEventSaveSettings);
    EasyUIAddItem(&pageSetting, &itemReset, "Reset Settings", ITEM_MESSAGE, "Resetting...", EasyUIEventResetSettings);
    EasyUIAddItem(&pageSetting, &itemAbout, "<About>", ITEM_JUMP_PAGE, pageAbout.id);
}
