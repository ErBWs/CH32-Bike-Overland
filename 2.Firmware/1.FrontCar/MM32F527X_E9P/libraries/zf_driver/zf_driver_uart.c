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

#include "hal_rcc.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "zf_driver_gpio.h"

#include "zf_driver_uart.h"

static  UART_Type   *uart_index[7]          = {UART1, UART2, UART3, UART4, UART5, UART6, UART7};
static  IRQn_Type   uart_irq[7]             = {UART1_IRQn, UART2_IRQn, UART3_IRQn, UART4_IRQn, UART5_IRQn, UART6_IRQn, UART7_IRQn};
static  uint8       uart_interrupt_state[8] = {0, 0, 0, 0, 0, 0, 0, 0};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口字节输出
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     dat             需要发送的字节
// 返回参数     void        
// 使用示例     uart_write_byte(UART_1, 0xA5);                                  // 串口1发送0xA5
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_write_byte (uart_index_enum uart_n, const uint8 dat)
{
    UART_PutData(uart_index[uart_n], dat);                                      // 写入发送数据
    while(!(UART_GetStatus(uart_index[uart_n]) & UART_CSR_TXC(1)));             // 等待发送完成
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送数组
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     *buff           要发送的数组地址
// 参数说明     len             发送长度
// 返回参数     void
// 使用示例     uart_write_buffer(UART_1, &a[0], 5);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_write_buffer (uart_index_enum uart_n, const uint8 *buff, uint32 len)
{
    zf_assert(NULL != buff);
    while(len)                                                                  // 循环到发送完
    {
        UART_PutData(uart_index[uart_n], *buff ++);                             // 写入发送数据
        while(!(UART_GetStatus(uart_index[uart_n]) & UART_CSR_TXC(1)));         // 等待发送完成
        len --;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送字符串
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     *str            要发送的字符串地址
// 返回参数     void
// 使用示例     uart_write_string(UART_1, "seekfree"); 
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_write_string (uart_index_enum uart_n, const char *str)
{
    zf_assert(NULL != str);
    while(*str)                                                                 // 一直循环到结尾
    {
        uart_write_byte(uart_n, *str ++);                                       // 发送数据
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     读取串口接收的数据（whlie等待）
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     *dat            接收数据的地址
// 返回参数     uint8           接收的数据
// 使用示例     uint8 dat = uart_read_byte(UART_1);                             // 接收 UART_1 数据  存在在 dat 变量里
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_read_byte (uart_index_enum uart_n)
{
    while(!(UART_GetStatus(uart_index[uart_n]) & UART_CSR_RXAVL(1)));           // 等待读取到一个数据
    return UART_GetData(uart_index[uart_n]);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     读取串口接收的数据（查询接收）
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     *dat            接收数据的地址
// 返回参数     uint8           1：接收成功   0：未接收到数据
// 使用示例     uint8 dat; uart_query_byte(UART_1, &dat);                       // 接收 UART_1 数据  存在在 dat 变量里
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_query_byte (uart_index_enum uart_n, uint8 *dat)
{
    zf_assert(NULL != dat);
    if(UART_GetStatus(uart_index[uart_n]) & UART_CSR_RXAVL(1))                  // 读取到一个数据
    {
        *dat = UART_GetData(uart_index[uart_n]);                                // 存储一个数据
        return 1;
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送中断设置
// 参数说明     uart_n           串口模块号
// 参数说明     status          1：打开中断   0：关闭中断
// 返回参数     void        
// 使用示例     uart_tx_interrupt(UART_1, 1);                                   // 打开串口1发送完成中断
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_tx_interrupt (uart_index_enum uart_n, uint32 status)
{
    UART_EnableInterrupts(uart_index[uart_n], UART_INT_TX_EMPTY, status);
    if(status)
    {
        uart_interrupt_state[uart_n] |= 0x10;
        interrupt_enable(uart_irq[uart_n]);
    }
    else
    {
        uart_interrupt_state[uart_n] &= 0xEF;
        if(0x00 == uart_interrupt_state[uart_n])
        {
            interrupt_disable(uart_irq[uart_n]);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口接收中断设置
// 参数说明     uart_n           串口模块号
// 参数说明     status          1：打开中断   0：关闭中断
// 返回参数     void        
// 使用示例     uart_rx_interrupt(UART_1, 1);                                   // 打开串口1接收完成中断
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_interrupt (uart_index_enum uart_n, uint32 status)
{
    UART_EnableInterrupts(uart_index[uart_n], UART_INT_RX_DONE, status);
    if(status)
    {
        uart_interrupt_state[uart_n] |= 0x01;
        interrupt_enable(uart_irq[uart_n]);
    }
    else
    {
        uart_interrupt_state[uart_n] &= 0xFE;
        if(0x00 == uart_interrupt_state[uart_n])
        {
            interrupt_disable(uart_irq[uart_n]);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口初始化
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     baud            串口波特率
// 参数说明     tx_pin          串口发送引脚 参照 zf_driver_uart.h 内 uart_tx_pin_enum 枚举体定义
// 参数说明     rx_pin          串口接收引脚 参照 zf_driver_uart.h 内 uart_rx_pin_enum 枚举体定义
// 返回参数     void            
// 使用示例     uart_init(UART_1, 115200, UART1_TX_A09, UART1_RX_A10);          // 初始化串口1 波特率115200 发送引脚使用PA09 接收引脚使用PA10
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_init(uart_index_enum uart_n, uint32 baud, uart_tx_pin_enum tx_pin, uart_rx_pin_enum rx_pin)
{
    afio_init((gpio_pin_enum)((tx_pin & 0xFFF00) >> 8), GPO, (gpio_af_enum)((tx_pin & 0xF0) >> 4), GPO_AF_PUSH_PULL);   // 提取对应IO索引 AF功能编码
    afio_init((gpio_pin_enum)((rx_pin & 0xFFF00) >> 8), GPI, (gpio_af_enum)((rx_pin & 0xF0) >> 4), GPI_FLOATING_IN);    // 提取对应IO索引 AF功能编码

    switch(uart_n)
    {
        case UART_1:    RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_UART1, ZF_ENABLE);   break;
        case UART_2:    RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_UART2, ZF_ENABLE);   break;
        case UART_3:    RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_UART3, ZF_ENABLE);   break;
        case UART_4:    RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_UART4, ZF_ENABLE);   break;
        case UART_5:    RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_UART5, ZF_ENABLE);   break;
        case UART_6:    RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_UART6, ZF_ENABLE);   break;
        case UART_7:    RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_UART7, ZF_ENABLE);   break;
    }

    UART_Init_Type uart_init;
    uart_init.ClockFreqHz   = bus_clock;
    uart_init.BaudRate      = baud;
    uart_init.WordLength    = UART_WordLength_8b;
    uart_init.StopBits      = UART_StopBits_1;
    uart_init.Parity        = UART_Parity_None;
    uart_init.XferMode      = UART_XferMode_RxTx;
    uart_init.HwFlowControl = UART_HwFlowControl_None;

    UART_Init(uart_index[uart_n], &uart_init);
    UART_Enable(uart_index[uart_n], true);
}
