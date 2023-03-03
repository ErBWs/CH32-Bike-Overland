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
* 文件名称          zf_driver_uart
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

#ifndef _zf_driver_uart_h_
#define _zf_driver_uart_h_

#include "hal_uart.h"

#include "zf_common_typedef.h"

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // UART 1 TX 引脚
    UART1_TX_A9         = 0x00970,                                               // 0x 009[A9]  7[AF7] 0[UART1]
    UART1_TX_B6         = 0x02670,                                               // 0x 026[B6]  7[AF7] 0[UART1]
    UART1_TX_C4         = 0x04470,                                               // 0x 044[C4]  7[AF7] 0[UART1]

    // UART 2 TX 引脚
    UART2_TX_A2         = 0x00271,                                               // 0x 002[A2]  7[AF7] 1[UART2]
    UART2_TX_D5         = 0x06571,                                               // 0x 065[D5]  7[AF7] 1[UART2]

    // UART 3 TX 引脚
    UART3_TX_B10        = 0x02A72,                                               // 0x 02A[B10] 7[AF7] 2[UART3]
    UART3_TX_C10        = 0x04A72,                                               // 0x 04A[C10] 7[AF7] 2[UART3]
    UART3_TX_D8         = 0x06872,                                               // 0x 068[D8]  7[AF7] 2[UART3]

    // UART 4 TX 引脚
    UART4_TX_A0         = 0x00083,                                               // 0x 000[A0]  8[AF8] 3[UART4]
    UART4_TX_C0         = 0x04083,                                               // 0x 040[C0]  8[AF8] 3[UART4]
    UART4_TX_C10        = 0x04A83,                                               // 0x 04A[C10] 8[AF8] 3[UART4]

    // UART 5 TX 引脚
    UART5_TX_A4         = 0x00484,                                               // 0x 004[A4]  8[AF8] 4[UART5]
    UART5_TX_C12        = 0x04C84,                                               // 0x 04C[C12] 8[AF8] 4[UART5]

    // UART 6 TX 引脚
    UART6_TX_B0         = 0x02085,                                               // 0x 020[B0]  8[AF8] 5[UART6]
    UART6_TX_C6         = 0x04685,                                               // 0x 046[C6]  8[AF8] 5[UART6]
    UART6_TX_G14        = 0x0CE85,                                               // 0x 0CE[G14] 8[AF8] 5[UART6]

    // UART 7 TX 引脚
    UART7_TX_B6         = 0x02686,                                               // 0x 026[B6]  8[AF8] 6[UART7]
    UART7_TX_E8         = 0x08886,                                               // 0x 088[E8]  8[AF8] 6[UART7]
    UART7_TX_F7         = 0x0A786,                                               // 0x 0A7[F7]  8[AF8] 6[UART7]
}uart_tx_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // UART 1 RX 引脚
    UART1_RX_A10        = 0x00A70,                                               // 0x 00A[A10] 7[AF7] 0[UART1]
    UART1_RX_B7         = 0x02770,                                               // 0x 027[B7]  7[AF7] 0[UART1]
    UART1_RX_C5         = 0x04570,                                               // 0x 045[C5]  7[AF7] 0[UART1]

    // UART 2 RX 引脚
    UART2_RX_A3         = 0x00371,                                               // 0x 003[A3]  7[AF7] 1[UART2]
    UART2_RX_D6         = 0x06671,                                               // 0x 066[D6]  7[AF7] 1[UART2]

    // UART 3 RX 引脚
    UART3_RX_B11        = 0x02B72,                                               // 0x 02B[B11] 7[AF7] 2[UART3]
    UART3_RX_C11        = 0x04B72,                                               // 0x 04B[C11] 7[AF7] 2[UART3]
    UART3_RX_D9         = 0x06972,                                               // 0x 069[D9]  7[AF7] 2[UART3]

    // UART 4 RX 引脚
    UART4_RX_A1         = 0x00183,                                               // 0x 001[A1]  8[AF8] 3[UART4]
    UART4_RX_C1         = 0x04183,                                               // 0x 041[C1]  8[AF8] 3[UART4]
    UART4_RX_C11        = 0x04B83,                                               // 0x 04B[C11] 8[AF8] 3[UART4]

    // UART 5 RX 引脚
    UART5_RX_A5         = 0x00584,                                               // 0x 005[A5]  8[AF8] 4[UART5]
    UART5_RX_D2         = 0x06284,                                               // 0x 062[D2]  8[AF8] 4[UART5]

    // UART 6 RX 引脚
    UART6_RX_B1         = 0x02185,                                               // 0x 021[B1]  8[AF8] 5[UART6]
    UART6_RX_C7         = 0x04785,                                               // 0x 047[C7]  8[AF8] 5[UART6]
    UART6_RX_G9         = 0x0C985,                                               // 0x 0C9[G9]  8[AF8] 5[UART6]

    // UART 7 RX 引脚
    UART7_RX_B7         = 0x02786,                                               // 0x 027[B7]  8[AF8] 6[UART7]
    UART7_RX_E7         = 0x08786,                                               // 0x 087[E7]  8[AF8] 6[UART7]
    UART7_RX_F6         = 0x0A686,                                               // 0x 0A6[F6]  8[AF8] 6[UART7]
}uart_rx_pin_enum;

typedef enum                                                                    // 枚举串口号 此枚举定义不允许用户修改
{
    UART_1,
    UART_2,
    UART_3,
    UART_4,
    UART_5,
    UART_6,
    UART_7,
}uart_index_enum;

void    uart_write_byte                     (uart_index_enum uartn, const uint8 dat);
void    uart_write_buffer                   (uart_index_enum uartn, const uint8 *buff, uint32 len);
void    uart_write_string                   (uart_index_enum uartn, const char *str);

uint8   uart_read_byte                      (uart_index_enum uartn);
uint8   uart_query_byte                     (uart_index_enum uartn, uint8 *dat);

void    uart_tx_interrupt                   (uart_index_enum uartn, uint32 status);
void    uart_rx_interrupt                   (uart_index_enum uartn, uint32 status);

void    uart_init                           (uart_index_enum uartn, uint32 baud, uart_tx_pin_enum tx_pin, uart_rx_pin_enum rx_pin);

#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // 兼容旧版本开源库接口名称
#define uart_putchar(uart_n, dat)           (uart_write_byte((uart_n), (dat)))
#define uart_putbuff(uart_n, buff, len)     (uart_write_buffer((uart_n), (buff), (len)))
#define uart_putstr(uart_n, str)            (uart_write_string((uart_n), (str)))

#define uart_getchar(uart_n, dat)           (*(dat) = uart_read_byte((uart_n)))
#define uart_query(uart_n, dat)             (uart_query_byte((uart_n), (dat)))

#define uart_tx_irq(uart_n, status)         (uart_tx_interrupt((uart_n), (status)))
#define uart_rx_irq(uart_n, status)         (uart_rx_interrupt((uart_n), (status)))
#endif

#endif
