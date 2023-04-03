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
* 文件名称          zf_device_wireless_ch573
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
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   模块管脚                                 单片机管脚
*                   RX                  查看 zf_device_wireless_ch573.h 中 WIRELESS_CH573_RX_PIN  宏定义
*                   TX                  查看 zf_device_wireless_ch573.h 中 WIRELESS_CH573_TX_PIN  宏定义
*                   RTS                 查看 zf_device_wireless_ch573.h 中 WIRELESS_CH573_RTS_PIN 宏定义
*                   VCC                 5V 电源
*                   GND                 电源地
*                   其余引脚悬空
*                   ------------------------------------
*********************************************************************************************************************/


#ifndef _zf_device_wireless_ch573_h_
#define _zf_device_wireless_ch573_


#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"
#include "zf_driver_delay.h"



#define WIRELESS_CH573_NUMBER            1                                           // 定义接入的CH573无线模块的数量 默认最大就三个
#define WIRELESS_CH573_INDEX             UART_2                                      // CH573无线模块1 对应使用的串口号
#define WIRELESS_CH573_BUAD_RATE         115200                                      // CH573无线模块1 对应使用的串口波特率
#define WIRELESS_CH573_TX_PIN            UART2_MAP1_RX_D6                                 // CH573无线模块1 对应模块的 TX 要接到单片机的 RX
#define WIRELESS_CH573_RX_PIN            UART2_MAP1_TX_D5                                 // CH573无线模块1 对应模块的 RX 要接到单片机的 TX
#define WIRELESS_CH573_RTS_PIN           E10                                         // CH573无线模块1 对应模块的 RTS 引脚


#define WIRELESS_CH573_BUFFER_SIZE       64
#define WIRELESS_CH573_TIMEOUT_COUNT     0x64



void        wireless_ch573_callback      (void);
uint32      wireless_ch573_send_byte         (const uint8 data);
uint32      wireless_ch573_send_buff         (const uint8 *buff, uint32 len);
uint32      wireless_ch573_send_string       (const uint8 *str);
void        wireless_ch573_send_image        (const uint8 *image_addr, uint32 image_size);
uint32      wireless_ch573_read_buff     (uint8 *buff, uint32 len);
uint8       wireless_ch573_init          (void);

#endif
