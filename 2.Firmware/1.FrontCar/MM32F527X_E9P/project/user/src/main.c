/*********************************************************************************************************************
* MM32F527X-E9P Opensourec Library 即（MM32F527X-E9P 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 MM32F527X-E9P 开源库的一部分
* 
* MM32F527X-E9P 开源库 是免费软件
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
* 开发环境          MDK 5.37
* 适用平台          MM32F527X_E9P
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-08-10        Teternal            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"

int main (void)
{
    clock_init(SYSTEM_CLOCK_120M);                                        // 初始化芯片时钟 工作频率为 120MHz
    debug_init();                                                               // 初始化默认 Debug UART

    // User initializations
    MenuInit();
    EasyUIInit(1);

    mt9v03x_init();
    adc_init(ADC1_CH12_C2, ADC_12BIT);
    timer_init(TIM_8, TIMER_US);
    Gp2yInit();
    MotorInit();
    pit_ms_init(TIM6_PIT, 10);
    interrupt_set_priority(TIM6_IRQn, 7);
    pit_ms_init(TIM7_PIT, 5);
    interrupt_set_priority(TIM6_IRQn, 6);

    EasyUITransitionAnim();

    while(1)
    {
        IPS114_ClearBuffer();
//        if (mt9v03x_finish_flag)
//        {
            GetSideLines();
//            EightNeighborSearch(mt9v03x_image);
            mt9v03x_finish_flag = 0;
//        }
//        IPS114_ShowGrayImage(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H,
//                             MT9V03X_W, MT9V03X_H, 0);
//        for (int16_t i = 0; i < MT9V03X_H; ++i)
//        {
//            IPS114_DrawPoint(sideEdges[i][0], i, RGB565_RED);
//            IPS114_DrawPoint(sideEdges[i][1], i, RGB565_BLUE);
//        }
//        for (int16_t i = 0; i < MT9V03X_W; ++i)
//        {
//            IPS114_DrawPoint(i, upDownEdges[0][i], RGB565_GREEN);
//            IPS114_DrawPoint(i, upDownEdges[1][i], RGB565_YELLOW);
//        }
//        IPS114_SendBuffer();
//        memset(sideEdges, 0, sizeof(sideEdges));
//        memset(upDownEdges, 0, sizeof(upDownEdges));
    }
}