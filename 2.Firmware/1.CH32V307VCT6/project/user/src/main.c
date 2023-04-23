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
    clock_init(SYSTEM_CLOCK_120M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 120MHz
    debug_init();                                                               // ��ʼ��Ĭ�� Debug UART
    systemInit();
    INS_init();
    gps_use.z_angle=0;
    uint16 i = 1;
    while(1)
    {
        system_delay_ms(20);
        D_data.data = (float)sinf(i * 60.0 / 360.0);
        uart_write_buffer(DEBUG_UART_INDEX, &D_data.ComInfo, 4);//("%f\r\n",(float)sin(i*60.0/360.0));
        i++;
        if (i > 2000) {
            i = 0;
        }
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
    imuinit(IMU_ALL);
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

