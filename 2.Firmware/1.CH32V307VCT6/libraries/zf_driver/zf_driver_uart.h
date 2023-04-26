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
* 文件名称          zf_driver_uart
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

#ifndef _zf_driver_uart_h
#define _zf_driver_uart_h

#include "ch32v30x.h"
#include "ch32v30x_gpio.h"
#include "ch32v30x_rcc.h"
#include "ch32v30x_usart.h"

#include "zf_common_interrupt.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"

//  此枚举定义不允许用户修改
//  初始化的时候，必须使用同一组引脚例如，UART1_MAP_TX_A9和UART1_MAP_RX_A10是一组引脚
//
typedef enum //  此枚举定义不允许用户修改
{
    // MAP0  默认映射
    // MAP1  重映射
    // MAP2  部分映射
    // MAP3  完全映射

    //----------UART1-----------//
    // 以下为串口1的一组映射引脚，不允许映射引脚混用。
    // 例如：UART1_MAP0_TX_A9与UART1_MAP1_TX_B6不能一起使用。

    // 默认映射
    UART1_MAP0_TX_A9  = 0x0000 | A9 ,
    UART1_MAP0_RX_A10 = 0x0000 | A10,

    // 以下为串口1的一组映射引脚，不允许映射引脚混用。
    // 重映射               
    UART1_MAP1_TX_B6  = 0x0100 | B6 ,
    UART1_MAP1_RX_B7  = 0x0100 | B7 ,

    // 以下为串口1的一组映射引脚，不允许映射引脚混用。
    // 部分映射             
    UART1_MAP2_TX_B15 = 0x0200 | B15,
    UART1_MAP2_RX_A8  = 0x0200 | A8 ,

    // 以下为串口1的一组映射引脚，不允许映射引脚混用。
    // 完全映射             
    UART1_MAP3_TX_A6  = 0x0300 | A6 ,
    UART1_MAP3_RX_A7  = 0x0300 | A7 ,

    //----------UART2-----------//

    // 以下为串口2的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    UART2_MAP0_TX_A2  = 0x1000 | A2 ,
    UART2_MAP0_RX_A3  = 0x1000 | A3 ,

    // 以下为串口2的一组映射引脚，不允许映射引脚混用。
    // 重映射               
    UART2_MAP1_TX_D5  = 0x1100 | D5 ,
    UART2_MAP1_RX_D6  = 0x1100 | D6 ,
                            
    //----------UART3--------------//

    // 以下为串口3的一组映射引脚，不允许映射引脚混用。
    // 默认映射             
    UART3_MAP0_TX_B10 = 0x2000 | B10,               // 下载器串口默认引脚
    UART3_MAP0_RX_B11 = 0x2000 | B11,               // 下载器串口默认引脚

    // 以下为串口3的一组映射引脚，不允许映射引脚混用。
    // 重映射               
    UART3_MAP1_TX_C10 = 0x2100 | C10,
    UART3_MAP1_RX_C11 = 0x2100 | C11,

    // 以下为串口3的一组映射引脚，不允许映射引脚混用。
    // 完全映射             
    UART3_MAP2_TX_D8  = 0x2300 | D8 ,
    UART3_MAP2_RX_D9  = 0x2300 | D9 ,

    //----------UART4-----------//

    // 以下为串口4的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    UART4_MAP0_TX_C10 = 0x3000 | C10,
    UART4_MAP0_RX_C11 = 0x3000 | C11,

    // 以下为串口4的一组映射引脚，不允许映射引脚混用。
    // 重映射               
    UART4_MAP1_TX_B0  = 0x3100 | B0 ,
    UART4_MAP1_RX_B1  = 0x3100 | B1 ,

    // 以下为串口4的一组映射引脚，不允许映射引脚混用。
    // 完全映射             
    UART4_MAP3_TX_E0  = 0x3300 | E0 ,
    UART4_MAP3_RX_E1  = 0x3300 | E1 ,

    //----------UART5-----------//

    // 以下为串口5的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    UART5_MAP0_TX_C12 = 0x4000 | C12,
    UART5_MAP0_RX_D2  = 0x4000 | D2,

    // 以下为串口5的一组映射引脚，不允许映射引脚混用。
    // 重映射                
    UART5_MAP1_TX_B4  = 0x4100 | B4,
    UART5_MAP1_RX_B5  = 0x4100 | B5,

    // 以下为串口5的一组映射引脚，不允许映射引脚混用。
    // 完全映射             
    UART5_MAP3_TX_E8  = 0x4300 | E8,
    UART5_MAP3_RX_E9  = 0x4300 | E9,

    //----------UART6-----------//

    // 以下为串口6的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    UART6_MAP0_TX_C0  = 0x5000 | C0 ,
    UART6_MAP0_RX_C1  = 0x5000 | C1 ,

    // 以下为串口6的一组映射引脚，不允许映射引脚混用。
    // 重映射                
    UART6_MAP1_TX_B8  = 0x5100 | B8 ,
    UART6_MAP1_RX_B9  = 0x5100 | B9 ,

    // 以下为串口6的一组映射引脚，不允许映射引脚混用。
    // 完全映射             
    UART6_MAP3_TX_E10 = 0x5300 | E10,
    UART6_MAP3_RX_E11 = 0x5300 | E11,

    //----------UART7-----------//

    // 以下为串口7的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    UART7_MAP0_TX_C2  = 0x6000 | C2 ,
    UART7_MAP0_RX_C3  = 0x6000 | C3 ,

    // 以下为串口7的一组映射引脚，不允许映射引脚混用。
    // 重映射                
    UART7_MAP1_TX_A6  = 0x6100 | A6 ,
    UART7_MAP1_RX_A7  = 0x6100 | A7 ,

    // 以下为串口7的一组映射引脚，不允许映射引脚混用。
    // 完全映射             
    UART7_MAP3_TX_E12 = 0x6300 | E12,
    UART7_MAP3_RX_E13 = 0x6300 | E13,

    //----------UART8-----------//

    // 以下为串口8的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    UART8_MAP0_TX_C4  = 0x7000 | C4 ,
    UART8_MAP0_RX_C5  = 0x7000 | C5 ,

    // 以下为串口8的一组映射引脚，不允许映射引脚混用。
    // 重映射                
    UART8_MAP1_TX_A14 = 0x7100 | A14,
    UART8_MAP1_RX_A15 = 0x7100 | A15,

    // 以下为串口8的一组映射引脚，不允许映射引脚混用。
    // 完全映射             
    UART8_MAP3_TX_E14 = 0x7300 | E14,
    UART8_MAP3_RX_E15 = 0x7300 | E15,

}uart_pin_enum;


typedef enum//  此枚举定义不允许用户修改
{
    UART_1,
    UART_2,
    UART_3,
    UART_4,
    UART_5,
    UART_6,
    UART_7,
    UART_8,
}uart_index_enum;



extern const uint32 uart_index[];




void    uart_write_byte         (uart_index_enum uart_n, const uint8 dat);
void    uart_write_buffer       (uart_index_enum uart_n, const uint8 *buff, uint32 len);
void    uart_write_string       (uart_index_enum uart_n, const char *str);

uint8   uart_read_byte                      (uart_index_enum uartn);
uint8   uart_query_byte                     (uart_index_enum uartn, uint8 *dat);

void    uart_tx_interrupt       (uart_index_enum uart_n, uint8 status);
void    uart_rx_interrupt       (uart_index_enum uart_n, uint8 status);

void    uart_init               (uart_index_enum uart_n, uint32 baud, uart_pin_enum tx_pin, uart_pin_enum rx_pin);



#endif
