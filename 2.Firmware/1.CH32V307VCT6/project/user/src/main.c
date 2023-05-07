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
extern int16_t back_wheel_encode;
int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 120MHz
    debug_init();                                                               // 初始化默认 Debug UART
    systemInit();
    while(1)
    {
//        system_delay_ms(10);
//        BlueToothPrintf("%d\n",back_wheel_encode);
//        BlueToothPrintf("%f\n",backSpdPid.pos_out);
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
    backSpdPid.target[NOW]=3;
//    motoDutySet(MOTOR_BACK_PIN,3000);
//    motoDutySet(MOTOR_FLY_PIN,3000);
//    while(1)
//    {
//        system_delay_ms(50);
//        int16_t back_wheel_encode=0;
//
//        back_wheel_encode = encoder_get_count(ENCODER_BACK_WHEEL_TIM);
//
//        BlueToothPrintf("%d\n",back_wheel_encode);
//
//        encoder_clear_count(ENCODER_BACK_WHEEL_TIM);
//    }
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

