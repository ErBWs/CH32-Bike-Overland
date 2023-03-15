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
* 文件名称          zf_driver_dvp
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

#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_driver_dvp.h"

//vuint32 frame_cnt = 0;
//vuint32 addr_cnt = 0;
//vuint32 href_cnt = 0;

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     dvp接口引脚初始化
// 参数说明     dvp_d0到dvp_d0       摄像头D0-D7引脚
// 参数说明     dvp_pclk            摄像头PCLK引脚
// 参数说明     dvp_vsync           摄像头vysnc引脚
// 参数说明     dvp_herf            摄像头herf引脚
// 返回参数     void
// 使用示例         内部使用，用户无需关心
//-------------------------------------------------------------------------------------------------------------------
void dvp_gpio_init(
        uint8 dvp_d0,uint8 dvp_d1,uint8 dvp_d2,uint8 dvp_d3,
        uint8 dvp_d4,uint8 dvp_d5,uint8 dvp_d6,uint8 dvp_d7,
        uint8 dvp_pclk,uint8 dvp_vsync,uint8 dvp_hsync)
{
    //DVP_D0 到 DVP_ D7
    gpio_init(dvp_d0, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d1, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d2, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d3, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d4, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d5, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d6, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d7, GPI, 0, GPI_PULL_UP);
    //DVP_VSYNC
    gpio_init(dvp_vsync, GPI, 0, GPI_PULL_UP);
    //DVP_PCLK
    gpio_init(dvp_pclk,  GPI, 0, GPI_PULL_UP);
    //DVP_HSYNC
    gpio_init(dvp_hsync, GPI, 0, GPI_PULL_UP);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     dvp接口初始化
// 参数说明     *image0                数据buff0的地址
// 参数说明     *image1                数据buff1的地址
// 参数说明     col_len                列长度
// 参数说明     row_len                行长度
// 返回参数     void
// 使用示例            内部使用，用户无需关心
//-------------------------------------------------------------------------------------------------------------------
void dvp_camera_init(uint32 *image0_addr, uint32 *image1_addr, uint16 col_len, uint16 row_len)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DVP, ENABLE);

    DVP->CR0 &= ~RB_DVP_MSK_DAT_MOD;

    /* VSYNC、HSYNC:High level active */
    DVP->CR0 |= RB_DVP_D8_MOD | RB_DVP_JPEG | RB_DVP_V_POLAR ;
    DVP->CR1 &= ~((RB_DVP_ALL_CLR)| RB_DVP_RCV_CLR);
    DVP->ROW_NUM = row_len;                    // rows行数
    DVP->COL_NUM = col_len;                    // cols列数

    DVP->DMA_BUF0 = (uint32)image0_addr;               //DMA addr0
    DVP->DMA_BUF1 = (uint32)image1_addr;               //DMA addr1


    /* Set frame capture rate */
    DVP->CR1 &= ~RB_DVP_FCRC;
    DVP->CR1 |= DVP_RATE_100P;  //100%

    // 设置为循环采集模式
    // DVP->CR1 |= RB_DVP_CM;



    //Interupt Enable
//    DVP->IER |= RB_DVP_IE_STR_FRM;
//    DVP->IER |= RB_DVP_IE_ROW_DONE;
    DVP->IER |= RB_DVP_IE_FRM_DONE;
//    DVP->IER |= RB_DVP_IE_FIFO_OV;
//    DVP->IER |= RB_DVP_IE_STP_FRM;


    DVP->CR1 |= RB_DVP_DMA_EN;  //enable DMA
    DVP->CR0 |= RB_DVP_ENABLE;  //enable DVP

    interrupt_set_priority(DVP_IRQn, 0x03);
    interrupt_enable(DVP_IRQn);

}

