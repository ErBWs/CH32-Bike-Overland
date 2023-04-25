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

union
{
    struct
    {
        uint8 com[4];
    }ComInfo;
    float data;
}D_data;

void systemInit();
int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 120MHz
    debug_init();                                                               // 初始化默认 Debug UART
    systemInit();
    INS_init();
    gps_ubx_init();
    gps_use.z_angle=0;
    uint16 i = 1;
    INS_U.GPS_uBlox.velE = 1000;
    INS_U.GPS_uBlox.lat = 888;
    while(1)
    {
        system_delay_ms(20);
        BlueToothPrintf("%d\n%d\n",INS_U.GPS_uBlox.velE,INS_U.GPS_uBlox.lat);
//        BlueToothPrintf("%d\n",INS_U.GPS_uBlox.lon);
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
    kalmanInit(&carBodyState,&kalmanDistanceX,&kalmanDistanceY,&kalmanVelocity,&imu_data.mag_yaw);
    encoderInit();
    motoInit();
    BlueToothInit();
//    imuinit(IMU_ALL);
    Butterworth_Parameter_Init();
#if USE_GPS
    GPS_init();
#endif
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
    vofaData[0] = batVoltage;
    return batVoltage;
}

