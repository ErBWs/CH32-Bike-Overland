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

int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 144MHz
    debug_init();                                                               // 初始化默认 Debug UART

    EasyUIInit(1);
    MenuInit();
//    gps_init();
//    imu660ra_init();
//    pwm_init(TIM8_PWM_MAP1_CH4_C13, 1000, 5000);  // Buzzer
    timer_init(TIM_2, TIMER_US);
    pit_ms_init(TIM1_PIT, 20);
    system_delay_ms(500);
//    pwm_init(TIM2_PWM_MAP1_CH1_A15, 50, 800);     // Servo
    EasyUITransitionAnim();

    while(1)
    {
//        if (gps_tau1201_flag)
//        {
//            if (!gps_data_parse())
//            {
//                printf("%d\n", gps_tau1201.state);
//                printf("%d\n", gps_tau1201.satellite_used);
//                printf("%lf\n", gps_tau1201.longitude);
//                printf("%lf\n", gps_tau1201.latitude);
//            }
//            gps_tau1201_flag = 0;
//        }
//        GetEasingCurves(0, 1, 4, 10, IN_BOUNCE);
//        IPS096_ClearBuffer();
//        IPS096_ShowBMP(0, 0, 58 ,56 ,ErBW_s_5856);
//        EasyUITransitionAnim();
//        IPS096_ShowInt(0, 60, time, 5);
        timer_start(TIM_2);
        timer_stop(TIM_2);
//        IPS096_ShowInt(0, 0, timer_get(TIM_2), 5);
        timer_clear(TIM_2);

        EasyUI(20);
        system_delay_ms(20);
    }
}

