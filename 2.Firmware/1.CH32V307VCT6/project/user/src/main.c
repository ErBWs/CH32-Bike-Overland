/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library 即（CH32V307VCT6 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是CH32V307VCT6 开源库的一部分
*
* CH32V307VCT6 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                             备注
* 2022-09-15        大W            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "inc_all.h"
/*
 * TIM2 Servo
 * TIM4 FLY_WHEEL AND BACK WHELL
 * TIM9 FLY_ENCODER
 * TIM10 BACK_MOTO_ENCODER
 *
 * TIM8 BEEP_PWM
 * TIM3 BEEP_AND_KEY_PIT
 *
 */
extern uint8 gps_state;


void play_song(void)
{
    TONE_PLAY(MI,20);
    TONE_PLAY(SO,20);
    TONE_PLAY(LA,20);
    TONE_PLAY(NONE,5);
    TONE_PLAY(LA,30);
    TONE_PLAY(NONE,5);
    TONE_PLAY(LA,20);
    TONE_PLAY(TI,20);
    TONE_PLAY(DO1,20);
    TONE_PLAY(NONE,5);
    TONE_PLAY(DO1,30);
    TONE_PLAY(NONE,5);
    TONE_PLAY(DO1,20);
    TONE_PLAY(RE1,20);
    TONE_PLAY(TI,20);
    TONE_PLAY(NONE,5);
    TONE_PLAY(TI,30);
    TONE_PLAY(NONE,5);
    TONE_PLAY(LA,20);
    TONE_PLAY(SO,20);
    TONE_PLAY(NONE,5);
    TONE_PLAY(SO,10);
    TONE_PLAY(LA,20);
    TONE_PLAY(NONE,100);
    TONE_PLAY(DO,50);
    TONE_PLAY(DO1,50);
}
#define USE_GPS 1
//extern double flashBuf[2000];
int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 144MHz
    debug_init();                                                               // 初始化默认 Debug UART
    // 此处编写用户代码 例如外设初始化代码等
    EasyKeyInit(&keyL,E2);
    EasyKeyInit(&keyC,E3);
    EasyKeyInit(&keyR,E4);
    ips096_init();
//    timer_init(TIM_7,TIMER_US);

////    adc_init(ADC1_IN9_B1,ADC_12BIT);
////    double temp=101.22;
////    SaveToFlashWithConversion(&temp);
////    double count;
////    FlashOperationEnd();
////    ReadFlashWithConversion(&count);
////    printf("%f",count);
//
////    while(1)
////    {
////        system_delay_ms(100);
//////        printf("%d\n", adc_convert(ADC2_IN9_B1));
////        ips096_show_int(0,0,adc_convert(ADC1_IN9_B1),4);
////    }
    encoderInit();
    motoInit();
    imuinit(IMU_ALL);
//    ADRC_Init(&ADRC_GYRO_Controller,&ADRC_SPEED_Controller,&ADRC_SPEED_MIN_Controller);//自抗扰控制器初始化
    pidAllInit();
    BlueToothInit();

    Butterworth_Parameter_Init();
    backSpdPid.target[NOW]=2;

//    pwm_set_duty(MOTOR_BACK_PIN,5000);
//    system_delay_ms(1000);
//    pwm_set_duty(SERVO_PIN, GetServoDuty(-20));
//    system_delay_ms(1000);
//    pwm_set_duty(SERVO_PIN, GetServoDuty(20));
//    system_delay_ms(1000);
//    pwm_set_duty(SERVO_PIN, GetServoDuty(0));
//while(1);
#if USE_GPS==1
    GPS_init();
#endif
    // 此处编写用户代码 例如外设初始化代码等
    taskTimAllInit();

    while(1)
    {
#if USE_GPS==1
        if(gps_tau1201_flag==1&&Bike_Start==1)
        {
            uint8 gps_state = gps_data_parse();
            if(gps_state==0)
            {
                uint8 is_finish=0;
                if(gps_tau1201.hpdo<0.75&&pile_state==0)//在绕桩模式下（即pile_state==1）取消自动换点逻辑
                {
                    is_finish = GetPoint(gps_tau1201.latitude, gps_tau1201.longitude,&gps_data);
                    gps_use.delta = yaw_gps_delta(gps_use.points_azimuth, imu_data.mag_yaw);
                }
                pileProcess(gps_tau1201.latitude, gps_tau1201.longitude,&gps_data);
                BlueToothPrintf("\ndelta:%f\n",gps_use.delta);
                BlueToothPrintf("yaw:%f\n",imu_data.mag_yaw);
                BlueToothPrintf("azimuth:%f\n",gps_use.points_azimuth);
//                ips096_show_float(0,0,gps_use.delta,3,3);
//                ips096_show_float(0,8,imu_data.mag_yaw,3,3);
//                printf("dis:%f\n",gps_use.points_distance);
                if(is_finish)
                {
                    stagger_flag=1;
                    motoDutySet(MOTOR_FLY_PIN,0);
                    Bike_Start = 0;
                    play_song();
                    while(1)
                    {
                        printf("Complete!!\n");
                        system_delay_ms(500);
                    }
                    //........//
                }
            }
            gps_tau1201_flag=0;
        }
        if(Bike_Start==0)
        {
            gps_handler();
        }
#endif
        // 此处编写需要循环执行的代码
    }
}

