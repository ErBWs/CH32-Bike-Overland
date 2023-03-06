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
* 文件名称          isr
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

#include "isr.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIM1 的定时器更新中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(TIM1_UP_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void TIM1_UP_IRQHandler (void)
{
    // 此处编写用户代码

    // 此处编写用户代码
    TIM_ClearInterruptStatus((TIM_Type *)TIM1, TIM_GetInterruptStatus((TIM_Type *)TIM1));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIM2 的定时器中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(TIM2_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void TIM2_IRQHandler (void)
{
    // 此处编写用户代码

    // 此处编写用户代码
    TIM_ClearInterruptStatus((TIM_Type *)TIM2, TIM_GetInterruptStatus((TIM_Type *)TIM2));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIM3 的定时器中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(TIM3_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void TIM3_IRQHandler (void)
{
    // 此处编写用户代码

    // 此处编写用户代码
    TIM_ClearInterruptStatus((TIM_Type *)TIM3, TIM_GetInterruptStatus((TIM_Type *)TIM3));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIM4 的定时器中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(TIM4_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void TIM4_IRQHandler (void)
{
    // 此处编写用户代码

    // 此处编写用户代码
    TIM_ClearInterruptStatus((TIM_Type *)TIM4, TIM_GetInterruptStatus((TIM_Type *)TIM4));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIM5 的定时器中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(TIM5_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void TIM5_IRQHandler (void)
{
    // 此处编写用户代码

    // 此处编写用户代码
    TIM_ClearInterruptStatus((TIM_Type *)TIM5, TIM_GetInterruptStatus((TIM_Type *)TIM5));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIM6 的定时器中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(TIM6_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void TIM6_IRQHandler (void)
{
    // 此处编写用户代码
    EasyKeyHandler(10);
    EasyUI(10);
    // 此处编写用户代码
    TIM_ClearInterruptStatus((TIM_Type *)TIM6, TIM_GetInterruptStatus((TIM_Type *)TIM6));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIM7 的定时器中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(TIM7_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void TIM7_IRQHandler (void)
{
    // 此处编写用户代码
    SpeedControl();
    VofaBigEndianSendFrame();
    // 此处编写用户代码
    TIM_ClearInterruptStatus((TIM_Type *)TIM7, TIM_GetInterruptStatus((TIM_Type *)TIM7));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIM8 的定时器更新中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(TIM8_UP_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void TIM8_UP_IRQHandler (void)
{
    // 此处编写用户代码

    // 此处编写用户代码
    TIM_ClearInterruptStatus((TIM_Type *)TIM8, TIM_GetInterruptStatus((TIM_Type *)TIM8));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     UART1 的串口中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(UART1_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void UART1_IRQHandler (void)
{
    if(UART_INT_TX_EMPTY & UART_GetInterruptStatus(UART1))                      // 串口发送缓冲空中断
    {
        // 此处编写用户代码
        // 务必填写数据或者关闭中断 否则会一直触发串口发送中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART1, UART_INT_TX_EMPTY);                    // 清除中断标志位
    }
    if(UART_INT_RX_DONE & UART_GetInterruptStatus(UART1))                       // 串口接收缓冲中断
    {
        // -----------------* Debug UART 预置中断处理函数 *-----------------
#if DEBUG_UART_USE_INTERRUPT                                                    // 如果开启 debug 串口中断
        debug_interrupr_handler();                                              // 调用 debug 串口接收处理函数 数据会被 debug 环形缓冲区读取
#endif                                                                          // 如果修改了 DEBUG_UART_INDEX 那这段代码需要放到对应的串口中断去
        // -----------------* Debug UART 预置中断处理函数 *-----------------
        // 此处编写用户代码
        // 务必读取数据或者关闭中断 否则会一直触发串口接收中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART1, UART_INT_RX_DONE);                     // 清除中断标志位
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     UART2 的串口中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(UART2_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void UART2_IRQHandler (void)
{
    if(UART_INT_TX_EMPTY & UART_GetInterruptStatus(UART2))                      // 串口发送缓冲空中断
    {
        // 此处编写用户代码
        // 务必填写数据或者关闭中断 否则会一直触发串口发送中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART2, UART_INT_TX_EMPTY);                    // 清除中断标志位
    }
    if(UART_INT_RX_DONE & UART_GetInterruptStatus(UART2))                       // 串口接收缓冲中断
    {
        // 此处编写用户代码
        // 务必读取数据或者关闭中断 否则会一直触发串口接收中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART2, UART_INT_RX_DONE);                     // 清除中断标志位
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     UART3 的串口中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(UART3_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void UART3_IRQHandler (void)
{
    if(UART_INT_TX_EMPTY & UART_GetInterruptStatus(UART3))                      // 串口发送缓冲空中断
    {
        // 此处编写用户代码
        // 务必填写数据或者关闭中断 否则会一直触发串口发送中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART3, UART_INT_TX_EMPTY);                    // 清除中断标志位
    }
    if(UART_INT_RX_DONE & UART_GetInterruptStatus(UART3))                       // 串口接收缓冲中断
    {
        // 此处编写用户代码
        // 务必读取数据或者关闭中断 否则会一直触发串口接收中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART3, UART_INT_RX_DONE);                     // 清除中断标志位
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     UART4 的串口中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(UART4_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void UART4_IRQHandler (void)
{
    if(UART_INT_TX_EMPTY & UART_GetInterruptStatus(UART4))                      // 串口发送缓冲空中断
    {
        // 此处编写用户代码
        // 务必填写数据或者关闭中断 否则会一直触发串口发送中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART4, UART_INT_TX_EMPTY);                    // 清除中断标志位
    }
    if(UART_INT_RX_DONE & UART_GetInterruptStatus(UART4))                       // 串口接收缓冲中断
    {
        // -----------------* GPS 预置中断处理函数 *-----------------
        gps_uart_callback();
        // -----------------* GPS 预置中断处理函数 *-----------------
        // 此处编写用户代码
        // 务必读取数据或者关闭中断 否则会一直触发串口接收中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART4, UART_INT_RX_DONE);                     // 清除中断标志位
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     UART5 的串口中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(UART5_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void UART5_IRQHandler (void)
{
    if(UART_INT_TX_EMPTY & UART_GetInterruptStatus(UART5))                      // 串口发送缓冲空中断
    {
        // 此处编写用户代码
        // 务必填写数据或者关闭中断 否则会一直触发串口发送中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART5, UART_INT_TX_EMPTY);                    // 清除中断标志位
    }
    if(UART_INT_RX_DONE & UART_GetInterruptStatus(UART5))                       // 串口接收缓冲中断
    {
        // -----------------* 摄像头初始化 串口 预置中断处理函数 *-----------------
        camera_uart_handler();
        // -----------------* 摄像头初始化 串口 预置中断处理函数 *-----------------
        // 此处编写用户代码
        // 务必读取数据或者关闭中断 否则会一直触发串口接收中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART5, UART_INT_RX_DONE);                     // 清除中断标志位
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     UART6 的串口中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(UART6_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void UART6_IRQHandler (void)
{
    if(UART_INT_TX_EMPTY & UART_GetInterruptStatus(UART6))                      // 串口发送缓冲空中断
    {
        // 此处编写用户代码
        // 务必填写数据或者关闭中断 否则会一直触发串口发送中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART6, UART_INT_TX_EMPTY);                    // 清除中断标志位
    }
    if(UART_INT_RX_DONE & UART_GetInterruptStatus(UART6))                       // 串口接收缓冲中断
    {
        // -----------------* 无线模块 串口 预置中断处理函数 *-----------------
        wireless_module_uart_handler();
        // -----------------* 无线模块 串口 预置中断处理函数 *-----------------
        // 此处编写用户代码
        // 务必读取数据或者关闭中断 否则会一直触发串口接收中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART6, UART_INT_RX_DONE);                     // 清除中断标志位
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     UART7 的串口中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(UART7_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void UART7_IRQHandler (void)
{
    if(UART_INT_TX_EMPTY & UART_GetInterruptStatus(UART7))                      // 串口发送缓冲空中断
    {
        // 此处编写用户代码
        // 务必填写数据或者关闭中断 否则会一直触发串口发送中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART7, UART_INT_TX_EMPTY);                    // 清除中断标志位
    }
    if(UART_INT_RX_DONE & UART_GetInterruptStatus(UART7))                       // 串口接收缓冲中断
    {
        // 此处编写用户代码
        // 务必读取数据或者关闭中断 否则会一直触发串口接收中断

        // 此处编写用户代码
        UART_ClearInterruptStatus(UART7, UART_INT_RX_DONE);                     // 清除中断标志位
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     外部中断 EXTI0 线 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(EXTI0_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void EXTI0_IRQHandler (void)
{
    // 此处编写用户代码 (A0/B0..I0) 引脚触发

    // 此处编写用户代码 (A0/B0..I0) 引脚触发
    EXTI_ClearLineStatus(EXTI, EXTI_LINE_0);                                    // 清除 line0 触发标志
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     外部中断 EXTI1 线 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(EXTI1_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void EXTI1_IRQHandler (void)
{
    // 此处编写用户代码 (A1/B1..I1) 引脚触发

    // 此处编写用户代码 (A1/B1..I1) 引脚触发
    EXTI_ClearLineStatus(EXTI, EXTI_LINE_1);                                    // 清除 line1 触发标志
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     外部中断 EXTI2 线 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(EXTI2_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void EXTI2_IRQHandler (void)
{
    // 此处编写用户代码 (A2/B2..H2) 引脚触发

    // 此处编写用户代码 (A2/B2..H2) 引脚触发
    EXTI_ClearLineStatus(EXTI, EXTI_LINE_2);                                    // 清除 line2 触发标志
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     外部中断 EXTI3 线 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(EXTI3_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void EXTI3_IRQHandler (void)
{
    // 此处编写用户代码 (A3/B3..H3) 引脚触发

    // 此处编写用户代码 (A3/B3..H3) 引脚触发
    EXTI_ClearLineStatus(EXTI, EXTI_LINE_3);                                    // 清除 line3 触发标志
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     外部中断 EXTI4 线 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(EXTI4_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void EXTI4_IRQHandler (void)
{
    // 此处编写用户代码 (A4/B4..G4) 引脚触发

    // 此处编写用户代码 (A4/B4..G4) 引脚触发
    EXTI_ClearLineStatus(EXTI, EXTI_LINE_4);                                    // 清除 line4 触发标志
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     外部中断 EXTI9-5 线 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(EXTI9_5_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void EXTI9_5_IRQHandler (void)
{
    if(EXTI_LINE_5 & EXTI_GetLineStatus(EXTI))                                  // line5 触发
    {
        // 此处编写用户代码 (A5/B5..G5) 引脚触发

        // 此处编写用户代码 (A5/B5..G5) 引脚触发
        EXTI_ClearLineStatus(EXTI, EXTI_LINE_5);                                // 清除 line5 触发标志
    }
    if(EXTI_LINE_6 & EXTI_GetLineStatus(EXTI))                                  // line6 触发
    {
        // 此处编写用户代码 (A6/B6..G6) 引脚触发

        // 此处编写用户代码 (A6/B6..G6) 引脚触发
        EXTI_ClearLineStatus(EXTI, EXTI_LINE_6);                                // 清除 line6 触发标志
    }
    if(EXTI_LINE_7 & EXTI_GetLineStatus(EXTI))                                  // line7 触发
    {
        // 此处编写用户代码 (A7/B7..G7) 引脚触发

        // 此处编写用户代码 (A7/B7..G7) 引脚触发
        EXTI_ClearLineStatus(EXTI, EXTI_LINE_7);                                // 清除 line7 触发标志
    }
    if(EXTI_LINE_8 & EXTI_GetLineStatus(EXTI))                                  // line8 触发
    {
        // -----------------* 摄像头 VSY 场中断 预置中断处理函数 *-----------------
        camera_vsync_handler();
        // -----------------* 摄像头 VSY 场中断 预置中断处理函数 *-----------------
        // 此处编写用户代码 (A8/B8..G8) 引脚触发

        // 此处编写用户代码 (A8/B8..G8) 引脚触发
        EXTI_ClearLineStatus(EXTI, EXTI_LINE_8);                                // 清除 line8 触发标志
    }
    if(EXTI_LINE_9 & EXTI_GetLineStatus(EXTI))                                  // line9 触发
    {
        // 此处编写用户代码 (A9/B9..G9) 引脚触发

        // 此处编写用户代码 (A9/B9..G9) 引脚触发
        EXTI_ClearLineStatus(EXTI, EXTI_LINE_9);                                // 清除 line9 触发标志
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     外部中断 EXTI15-10(A15-10/B15-10..G15-10) 线 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(EXTI15_10_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void EXTI15_10_IRQHandler (void)
{
    if(EXTI_LINE_10 & EXTI_GetLineStatus(EXTI))                                 // line10 触发
    {
        // -----------------* DM1XA 声/反馈信号 预置中断处理函数 *-----------------
        dm1xa_sound_callback();
        // -----------------* DM1XA 声/反馈信号 预置中断处理函数 *-----------------
        // 此处编写用户代码 (A10/B10..G10) 引脚触发

        // 此处编写用户代码 (A10/B10..G10) 引脚触发
        EXTI_ClearLineStatus(EXTI, EXTI_LINE_10);                               // 清除 line10 触发标志
    }
    if(EXTI_LINE_11 & EXTI_GetLineStatus(EXTI))                                 // line11 触发
    {
        // -----------------* DM1XA 光信号 预置中断处理函数 *-----------------
        dm1xa_light_callback();
        // -----------------* DM1XA 光信号 预置中断处理函数 *-----------------
        // 此处编写用户代码 (A11/B11..G11) 引脚触发

        // 此处编写用户代码 (A11/B11..G11) 引脚触发
        EXTI_ClearLineStatus(EXTI, EXTI_LINE_11);                               // 清除 line11 触发标志
    }
    if(EXTI_LINE_12 & EXTI_GetLineStatus(EXTI))                                 // line12 触发
    {
        // 此处编写用户代码 (A12/B12..G12) 引脚触发

        // 此处编写用户代码 (A12/B12..G12) 引脚触发
        EXTI_ClearLineStatus(EXTI, EXTI_LINE_12);                               // 清除 line12 触发标志
    }
    if(EXTI_LINE_13 & EXTI_GetLineStatus(EXTI))                                 // line13 触发
    {
        // 此处编写用户代码 (A13/B13..G13) 引脚触发

        // 此处编写用户代码 (A13/B13..G13) 引脚触发
        EXTI_ClearLineStatus(EXTI, EXTI_LINE_13);                               // 清除 line13 触发标志
    }
    if(EXTI_LINE_14 & EXTI_GetLineStatus(EXTI))                                 // line14 触发
    {
        // 此处编写用户代码 (A14/B14..G14) 引脚触发

        // 此处编写用户代码 (A14/B14..G14) 引脚触发
        EXTI_ClearLineStatus(EXTI, EXTI_LINE_14);                               // 清除 line14 触发标志
    }
    if(EXTI_LINE_15 & EXTI_GetLineStatus(EXTI))                                 // line15 触发
    {
        // 此处编写用户代码 (A15/B15..G15) 引脚触发

        // 此处编写用户代码 (A15/B15..G15) 引脚触发
        EXTI_ClearLineStatus(EXTI, EXTI_LINE_15);                               // 清除 line15 触发标志
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA1 通道 1 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA1_CH1_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA1_CH1_IRQHandler (void)
{
    uint32 channel_index = (DMA1_CHANNEL1 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA1 通道 2 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA1_CH2_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA1_CH2_IRQHandler (void)
{
    uint32 channel_index = (DMA1_CHANNEL2 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA1 通道 3 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA1_CH3_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA1_CH3_IRQHandler (void)
{
    uint32 channel_index = (DMA1_CHANNEL3 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA1 通道 4 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA1_CH4_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA1_CH4_IRQHandler (void)
{
    uint32 channel_index = (DMA1_CHANNEL4 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // -----------------* 摄像头 DMA 完成 预置中断处理函数 *-----------------
        camera_dma_handler();
        // -----------------* 摄像头 DMA 完成 预置中断处理函数 *-----------------
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA1 通道 5 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA1_CH5_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA1_CH5_IRQHandler (void)
{
    uint32 channel_index = (DMA1_CHANNEL5 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA1 通道 6 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA1_CH6_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA1_CH6_IRQHandler (void)
{
    uint32 channel_index = (DMA1_CHANNEL6 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA1 通道 7 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA1_CH7_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA1_CH7_IRQHandler (void)
{
    uint32 channel_index = (DMA1_CHANNEL7 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA1 通道 8 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA1_CH8_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA1_CH8_IRQHandler (void)
{
    uint32 channel_index = (DMA1_CHANNEL8 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA1, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA1, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA2 通道 1 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA2_CH1_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA2_CH1_IRQHandler (void)
{
    uint32 channel_index = (DMA2_CHANNEL1 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA2 通道 2 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA2_CH2_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA2_CH2_IRQHandler (void)
{
    uint32 channel_index = (DMA2_CHANNEL2 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA2 通道 3 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA2_CH3_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA2_CH3_IRQHandler (void)
{
    uint32 channel_index = (DMA2_CHANNEL3 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA2 通道 4 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA2_CH4_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA2_CH4_IRQHandler (void)
{
    uint32 channel_index = (DMA2_CHANNEL4 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA2 通道 5 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA2_CH5_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA2_CH5_IRQHandler (void)
{
    uint32 channel_index = (DMA2_CHANNEL5 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA2 通道 6 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA2_CH6_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA2_CH6_IRQHandler (void)
{
    uint32 channel_index = (DMA2_CHANNEL6 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA2 通道 7 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA2_CH7_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA2_CH7_IRQHandler (void)
{
    uint32 channel_index = (DMA2_CHANNEL7 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DMA2 通道 8 的中断服务函数 启动 .s 文件定义 不允许修改函数名称
//              默认优先级 修改优先级使用 interrupt_set_priority(DMA2_CH8_IRQn, 1);
//-------------------------------------------------------------------------------------------------------------------
void DMA2_CH8_IRQHandler (void)
{
    uint32 channel_index = (DMA2_CHANNEL8 & 0x0F);
    // DMA 完成中断
    if(DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 完成中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_DONE);
    }
    // DMA 半传输中断
    if(DMA_CHN_INT_XFER_HALF_DONE & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 半传输中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_HALF_DONE);
    }
    // DMA 传输出错中断
    if(DMA_CHN_INT_XFER_ERR & DMA_GetChannelInterruptStatus(DMA2, channel_index))
    {
        // 此处编写用户代码

        // 此处编写用户代码
        // 清除 传输出错中断 标志位
        DMA_ClearChannelInterruptStatus(DMA2, channel_index, DMA_CHN_INT_XFER_ERR);
    }
}
