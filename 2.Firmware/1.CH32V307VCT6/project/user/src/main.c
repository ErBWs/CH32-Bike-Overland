#include "zf_common_headfile.h"
#include "inc_all.h"

/*
 * TIM2 Servo
 * TIM4 FLY_WHEEL AND BACK WHELL
 * TIM9 FLY_ENCODER
 * TIM10 BACK_MOTO_ENCODER
 * TIM8 BEEP_PWM
 * TIM3 BEEP_AND_KEY_PIT
 */

//union
//{
//    struct
//    {
//        uint8 com[4];
//    }ComInfo;
//    float data;
//}D_data;
extern gps_report_t gpsReport;
void systemInit();
int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 120MHz
    debug_init();                                                               // 初始化默认 Debug UART
    systemInit();
    while(1)
    {
//        system_delay_ms(50);
//        BlueToothPrintf("%f,%f\n",INS_Y.INS_Out.x_R,INS_Y.INS_Out.y_R);
//        BlueToothPrintf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
//                        INS_U.GPS_uBlox.lat,
//                        INS_U.GPS_uBlox.lon,
//                        INS_U.GPS_uBlox.velN,
//                        INS_U.GPS_uBlox.velE,
//                        INS_U.GPS_uBlox.velD,
//                        INS_U.GPS_uBlox.fixType,
//                        INS_U.GPS_uBlox.hAcc,
//                        INS_U.GPS_uBlox.vAcc,
//                        INS_U.GPS_uBlox.sAcc,
//                        INS_U.GPS_uBlox.numSV
//        );
        EasyUI(20);

    }
}


void systemInit(void)
{
    pidAllInit();
    MenuInit();
    EasyUIInit(1);
    adc_init(BATTERY_ADC_PIN,ADC_12BIT);
    BuzzerInit();
    encoderInit();
    motoInit();
    BlueToothInit();
    imuinit(IMU_ALL);
    Butterworth_Parameter_Init();
#if USE_GPS
    gps_ubx_init();
    IST8310Init();
#endif
    INS_init();
    EasyUITransitionAnim();
    backSpdPid.target[NOW]=2;
    taskTimAllInit();
}
float GetBatteryVoltage()
{
    float batVoltageAdc;
    float batVoltage;
    batVoltageAdc = adc_mean_filter_convert(BATTERY_ADC_PIN, 10);
    batVoltage = 37.35f * batVoltageAdc / 4096;
//    vofaData[5] = batVoltage;
    return batVoltage;
}

