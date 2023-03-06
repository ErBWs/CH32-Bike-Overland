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

#include "hal_rcc.h"

#include "zf_driver_dma.h"

static DMA_Type *dma_index[2] = {DMA1, DMA2};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     dma 传输数据数量设置
// 参数说明     ch              选择 dma 通道 (详见 zf_driver_dma.h 中枚举 dma_channel_enum 定义)
// 参数说明     size            传输数据数量
// 返回参数     void
// 使用示例     dma_set_count(MT9V03X_DMA_CH, image_size);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void dma_set_count (dma_channel_enum ch, const uint16 transfer_count)
{
    switch(ch & 0xF0)
    {
        case 0x00:  DMA1->CH[ch & 0x0f].CNDTR = DMA_CNDTR_NDT(transfer_count);  break;
        case 0x10:  DMA2->CH[ch & 0x0f].CNDTR = DMA_CNDTR_NDT(transfer_count);  break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     dma 传输使能
// 参数说明     ch              选择 dma 通道 (详见 zf_driver_dma.h 中枚举 dma_channel_enum 定义)
// 返回参数     void
// 使用示例     dma_enable(MT9V03X_DMA_CH);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void dma_enable (dma_channel_enum ch)
{
    switch(ch & 0xF0)
    {
        case 0x00:
        {
            DMA_EnableBurstMode(DMA1, (ch & 0x0f), false);
            DMA_EnableChannel(DMA1, (ch & 0x0f), true);
        }break;
        case 0x10:
        {
            DMA_EnableBurstMode(DMA2, (ch & 0x0f), false);
            DMA_EnableChannel(DMA2, (ch & 0x0f), true);
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     dma 传输禁止
// 参数说明     ch              选择 dma 通道 (详见 zf_driver_dma.h 中枚举 dma_channel_enum 定义)
// 返回参数     void
// 使用示例     dma_disable(MT9V03X_DMA_CH);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void dma_disable (dma_channel_enum ch)
{
    switch(ch & 0xF0)
    {
        case 0x00:
        {
            DMA_EnableBurstMode(DMA1, (ch & 0x0f), false);
            DMA_EnableChannel(DMA1, (ch & 0x0f), false);
        }break;
        case 0x10:
        {
            DMA_EnableBurstMode(DMA2, (ch & 0x0f), false);
            DMA_EnableChannel(DMA2, (ch & 0x0f), false);
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     dma 初始化 摄像头接口
// 参数说明     ch              选择 dma 通道 (详见 zf_driver_dma.h 中枚举 dma_channel_enum 定义)
// 参数说明     size            传输数据数量
// 参数说明     peripheral_add  外设地址 摄像头数据接口的地址
// 参数说明     memory_add      摄像头数据存放地址
// 返回参数     void
// 使用示例     dma_camera_init(MT9V03X_DMA_CH, image_size, (uint32)MT9V03X_DATA_ADD, (uint32)camera_buffer_addr);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void dma_camera_init (dma_channel_enum ch, const uint32 size, const uint32 peripheral_add, const uint32 memory_add)
{
    switch(ch & 0xF0)
    {
        case 0x00:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_DMA1, ZF_ENABLE);    break;
        case 0x10:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_DMA2, ZF_ENABLE);    break;
    }

    DMA_Channel_Init_Type dma_channel_init;
    dma_channel_init.XferMode = DMA_XferMode_PeriphToMemory;
    dma_channel_init.ReloadMode = DMA_ReloadMode_AutoReload;
    dma_channel_init.PeriphAddrIncMode = DMA_AddrIncMode_StayAfterXfer;
    dma_channel_init.MemAddrIncMode = DMA_AddrIncMode_IncAfterXfer;
    dma_channel_init.XferWidth = DMA_XferWidth_8b;
    dma_channel_init.Priority = DMA_Priority_Highest;
    dma_channel_init.XferCount = size;
    dma_channel_init.MemAddr = (uint32_t)memory_add;
    dma_channel_init.PeriphAddr = (uint32_t)peripheral_add;

    switch(ch & 0xF0)
    {
        case 0x00:
        {
            DMA_InitChannel(DMA1, (ch & 0x0f), &dma_channel_init);
            DMA_EnableChannelInterrupts(DMA1, (ch & 0x0f), DMA_CHN_INT_XFER_DONE, true);
        }break;
        case 0x10:
        {
            DMA_InitChannel(DMA2, (ch & 0x0f), &dma_channel_init);
            DMA_EnableChannelInterrupts(DMA2, (ch & 0x0f), DMA_CHN_INT_XFER_DONE, true);
        }break;
    }
    switch(ch)
    {
        case DMA1_CHANNEL1: interrupt_enable(DMA1_CH1_IRQn);    break;
        case DMA1_CHANNEL2: interrupt_enable(DMA1_CH2_IRQn);    break;
        case DMA1_CHANNEL3: interrupt_enable(DMA1_CH3_IRQn);    break;
        case DMA1_CHANNEL4: interrupt_enable(DMA1_CH4_IRQn);    break;
        case DMA1_CHANNEL5: interrupt_enable(DMA1_CH5_IRQn);    break;
        case DMA1_CHANNEL6: interrupt_enable(DMA1_CH6_IRQn);    break;
        case DMA1_CHANNEL7: interrupt_enable(DMA1_CH7_IRQn);    break;
        case DMA1_CHANNEL8: interrupt_enable(DMA1_CH8_IRQn);    break;

        case DMA2_CHANNEL1: interrupt_enable(DMA2_CH1_IRQn);    break;
        case DMA2_CHANNEL2: interrupt_enable(DMA2_CH2_IRQn);    break;
        case DMA2_CHANNEL3: interrupt_enable(DMA2_CH3_IRQn);    break;
        case DMA2_CHANNEL4: interrupt_enable(DMA2_CH4_IRQn);    break;
        case DMA2_CHANNEL5: interrupt_enable(DMA2_CH5_IRQn);    break;
        case DMA2_CHANNEL6: interrupt_enable(DMA2_CH6_IRQn);    break;
        case DMA2_CHANNEL7: interrupt_enable(DMA2_CH7_IRQn);    break;
        case DMA2_CHANNEL8: interrupt_enable(DMA2_CH8_IRQn);    break;
    }
}
