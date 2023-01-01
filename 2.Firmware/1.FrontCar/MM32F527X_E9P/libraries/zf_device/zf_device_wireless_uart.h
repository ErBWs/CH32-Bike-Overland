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
* 文件名称          zf_device_wireless_uart
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
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   RX                  查看 zf_device_wireless_uart.h 中 WIRELESS_UART_RX_PINx 宏定义
*                   TX                  查看 zf_device_wireless_uart.h 中 WIRELESS_UART_TX_PINx 宏定义
*                   RTS                 查看 zf_device_wireless_uart.h 中 WIRELESS_UART_RTS_PINx 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_wireless_uart_h_
#define _zf_device_wireless_uart_h_

#include "zf_common_typedef.h"

#define WIRELESS_UART_INDEX         (UART_6)                                    // 无线串口对应使用的串口号
#define WIRELESS_UART_BUAD_RATE     (115200)                                    // 无线串口对应使用的串口波特率
#define WIRELESS_UART_TX_PIN        (UART6_RX_C7)                               // 无线串口对应模块的 TX 要接到单片机的 RX
#define WIRELESS_UART_RX_PIN        (UART6_TX_C6)                               // 无线串口对应模块的 RX 要接到单片机的 TX
#define WIRELESS_UART_RTS_PIN       (C5 )                                       // 无线串口对应模块的 RTS 引脚

// ------------------------------------ 自动波特率 ------------------------------------
// 注意事项1：无线转串口模块版本是V2.0以下的是无法开启自动波特率的。
// 注意事项2：开启自动波特率务必连接RTS引脚 否则会开启失败。
// 注意事项3：模块自动波特率失败的话 可以尝试断电重启

// 开启自动波特率务必阅读上面两条 注意事项
// 开启自动波特率务必阅读上面两条 注意事项
// 开启自动波特率务必阅读上面两条 注意事项

// 0：关闭自动波特率  
// 1：开启自动波特率 自动波特率的作用是修改 WIRELESS_UART_BAUD 之后不需要对模块进行配置 模块会自动设置为对应的波特率

#define WIRELESS_UART_AUTO_BAUD_RATE    (0)
// ------------------------------------ 自动波特率 ------------------------------------

#define WIRELESS_UART_BUFFER_SIZE       (64  )
#define WIRELESS_UART_TIMEOUT_COUNT     (0x64)

uint32      wireless_uart_send_byte         (const uint8 data);
uint32      wireless_uart_send_buff         (const uint8 *buff, uint32 len);
uint32      wireless_uart_send_string       (const char *str);
void        wireless_uart_send_image        (const uint8 *image_addr, uint32 image_size);

uint32      wireless_uart_read_buff         (uint8 *buff, uint32 len);

void        wireless_uart_callback          (void);

uint8       wireless_uart_init              (void);

#endif
