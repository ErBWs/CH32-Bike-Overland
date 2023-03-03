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
* 文件名称          zf_driver_dma
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

#ifndef _zf_driver_dma_h_
#define _zf_driver_dma_h_

#include "hal_dma.h"

#include "zf_common_interrupt.h"

// 需要特别注意的是 只有 TIM1/8/5/3 四个定时器支持 TRGI 触发 DMA
// 也就是说 只能用这四个定时器的对应 ETR 通道来采集摄像头 PCLK 信号

// DMA1 通道与对应的外设关系
// DMA1 C1H1 :  ADC1     | UART6_RX | TIM2_CC3    | TIM4_CC1           |             | 
// DMA1 C1H2 :  ADC2     | SPI1_RX  | UART3_TX    | TIM1_CC1           | TIM2_UP     | TIM3_CC3
// DMA1 C1H3 :  SPI1_TX  | UART3_RX | TIM1_CC2    | TIM2_UP/CC3        | TIM3_UP/CC4 | 
// DMA1 C1H4 :  SPI2_RX  | UART1_TX | I2C2_TX     | TIM1_CC4/TRGI/COM  | TIM4_CC2    | 
// DMA1 C1H5 :  SPI2_TX  | UART1_RX | I2C2_RX     | TIM1_UP            | TIM2_CC1    | TIM4_CC3
// DMA1 C1H6 :  UART2_TX | I2C1_TX  | TIM1_CC3    | TIM3_CC1/TRGI      |             | 
// DMA1 C1H7 :  UART2_RX | I2C1_RX  | TIM1_TRGI   | TIM2_CC2/CC4       | TIM4_UP     | 
// DMA1 C1H8 :  UART6_TX | TIM1_COM | TIM2_UP/CC4 | TIM3_CC2           | TIM4_CC4    | FlexCAN1_RX

// DMA2 通道与对应的外设关系
// DMA2 C1H1 :  SPI3_RX    | UART5/7_RX | TIM5_CC4/TRGI | TIM8_UP/CC3       | 
// DMA2 C1H2 :  SPI3_TX    | UART5/7_TX | TIM5_UP/CC3   | TIM8_CC4/TRGI/COM | 
// DMA2 C1H3 :  UART4_RX   | TIM6_UP    | DAC_CH1       | TIM8_CC1          | 
// DMA2 C1H4 :  UART6      | LPUART_TX  | TIM5_CC2      | TIM7_UP           | DAC_CH2
// DMA2 C1H5 :  UART4_TX   | TIM5_CC1   | TIM8_CC2      |                   | 
// DMA2 C1H6 :  UART6_RX   | LPUART_RX  | TIM5/6/7/8_UP | FlexCAN2_RX       | 
// DMA2 C1H7 :  UART4/7_RX | DAC_CH1    | DAC_CH2       | TIM8_TRGI         | 
// DMA2 C1H8 :  UART4/7_TX | TIM8_COM   | QSPI          |                   | 

typedef enum                                                                    // 枚举 DMA 通道  此枚举定义不允许用户修改
{
    DMA1_CHANNEL1 = 0x00,
    DMA1_CHANNEL2,
    DMA1_CHANNEL3,
    DMA1_CHANNEL4,
    DMA1_CHANNEL5,
    DMA1_CHANNEL6,
    DMA1_CHANNEL7,
    DMA1_CHANNEL8,

    DMA2_CHANNEL1 = 0x10,
    DMA2_CHANNEL2,
    DMA2_CHANNEL3,
    DMA2_CHANNEL4,
    DMA2_CHANNEL5,
    DMA2_CHANNEL6,
    DMA2_CHANNEL7,
    DMA2_CHANNEL8,
}dma_channel_enum;


void    dma_set_count      (dma_channel_enum ch, const uint16 transfer_count);
void    dma_enable         (dma_channel_enum ch);
void    dma_disable        (dma_channel_enum ch);
void    dma_camera_init    (dma_channel_enum ch, const uint32 size, const uint32 peripheral_add, const uint32 memory_add);

#endif
