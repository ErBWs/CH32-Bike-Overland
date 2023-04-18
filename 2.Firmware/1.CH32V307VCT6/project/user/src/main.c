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

extern float num_float[8];
void systemInit();
int main (void)
{
    clock_init(SYSTEM_CLOCK_120M);                                              // 初始化芯片时钟 工作频率为 120MHz
    debug_init();                                                               // 初始化默认 Debug UART
    systemInit();
    gps_use.z_angle=0;
    while(1)
    {
//        BlueToothPrintf("delta:%f\n",gps_use.delta);
        BlueToothPrintf("delta:%f\n",gps_use.z_angle);
        BlueToothPrintf("type:%d",gps_data.type);
        EasyUI(20);
    }
}




void systemInit(void)
{

    pidAllInit();
//    kalman_config_v(&kalman_v);
    MenuInit();
    EasyUIInit(1);
    adc_init(BATTERY_ADC_PIN,ADC_12BIT);
    kalmanInit(&carBodyState,&kalmanDistanceX,&kalmanDistanceY,&kalmanVelocity,&imu_data.mag_yaw);
    encoderInit();
    motoInit();
    BlueToothInit();
    imuinit(IMU_ALL);
    Butterworth_Parameter_Init();
#if USE_GPS==1
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

