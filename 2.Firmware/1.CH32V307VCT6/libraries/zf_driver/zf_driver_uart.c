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
#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"

// 该数组禁止修改，内部使用用户无需关心
const uint8 uart_irq[] = {USART1_IRQn, USART2_IRQn, USART3_IRQn, UART4_IRQn, UART5_IRQn, UART6_IRQn, UART7_IRQn, UART8_IRQn};
const uint32 uart_index[] = {USART1_BASE, USART2_BASE, USART3_BASE, UART4_BASE, UART5_BASE, UART6_BASE, UART7_BASE, UART8_BASE};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送一个字节
// 参数说明     uartn       串口通道
// 参数说明     dat         串口数据
// 返回参数     void
// 使用示例     uart_write_byte(UART_1, 0x43);        //串口1发送0x43。
//-------------------------------------------------------------------------------------------------------------------
void uart_write_byte(uart_index_enum uartn, const uint8 dat)
{
    while((((USART_TypeDef*)uart_index[uartn])->STATR & USART_FLAG_TXE)==0);
    ((USART_TypeDef*)uart_index[uartn])->DATAR = dat;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送数组
// 参数说明     uartn       串口通道
// 参数说明     buff        要发送的数组地址
// 参数说明     len         数据长度
// 返回参数     void
// 使用示例     uart_write_buffer(UART_1, buff, 10);     //串口1发送10个buff数组。
//-------------------------------------------------------------------------------------------------------------------
void uart_write_buffer(uart_index_enum uartn, const uint8 *buff, uint32 len)
{
    zf_assert(buff != NULL);
    while(len--)
        uart_write_byte(uartn, *buff++);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送字符串
// 参数说明     uartn       串口通道
// 参数说明     str         字符串首地址
// 返回参数     void
// 使用示例     uart_putstr(UART_1, (uint8 *)"12345")   //串口1发送12345这个字符串
//-------------------------------------------------------------------------------------------------------------------
void uart_write_string(uart_index_enum uartn, const char *str)
{
    zf_assert(str != NULL);
    while(*str)                                                                 // 一直循环到结尾
    {
        uart_write_byte(uartn, *str++);
    }
}



//-------------------------------------------------------------------------------------------------------------------
// 函数简介     打开串口接收中断
// 参数说明     uartn       串口通道
// 参数说明     status      使能或者失能
// 返回参数     void
// 使用示例     uart_rx_irq(UART_1, ENABLE);        //打开串口1接收中断
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_interrupt(uart_index_enum uartn, uint8 status)
{
    USART_ITConfig(((USART_TypeDef*)uart_index[uartn]), USART_IT_RXNE, status);

    // 设置中断优先级
    interrupt_set_priority((uint32)((IRQn_Type)uart_irq[uartn]), 0);

    if(status)  interrupt_enable((IRQn_Type)uart_irq[uartn]);
    else        interrupt_disable((IRQn_Type)uart_irq[uartn]);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     打开串口发送中断
// 参数说明     uartn       串口通道
// 参数说明     status      使能或者失能
// 返回参数     void
// 使用示例     uart_tx_irq(UART_1, DISABLE);       //关闭串口1发送 中断
//-------------------------------------------------------------------------------------------------------------------
void uart_tx_interrupt(uart_index_enum uartn, uint8 status)
{
    USART_ITConfig(((USART_TypeDef*)uart_index[uartn]), USART_IT_TXE, status);

    // 设置中断优先级
    interrupt_set_priority((uint32)((IRQn_Type)uart_irq[uartn]), 0);

    if(status)  interrupt_enable((IRQn_Type)uart_irq[uartn]);
    else        interrupt_disable((IRQn_Type)uart_irq[uartn]);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     读取串口接收的数据（whlie等待）
// 参数说明     uartn           串口模块号(UART_1 - UART_8)
// 参数说明     *dat            接收数据的地址
// 返回参数     void
// 使用示例     uint8 dat; uart_read_byte(USART_1,&dat);       // 接收串口1数据  存在在dat变量里
//-------------------------------------------------------------------------------------------------------------------
void uart_read_byte(uart_index_enum uartn, uint8 *dat)
{
    while((((USART_TypeDef*)uart_index[uartn])->STATR & USART_FLAG_RXNE) == 0);
    *dat = (uint16)(((USART_TypeDef*)uart_index[uartn])->DATAR & (uint16)0xFF);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     读取串口接收的数据（查询接收）
// 参数说明     uartn           串口模块号(UART_1 - UART_8)
// 参数说明     *dat            接收数据的地址
// 返回参数     uint8           1：接收成功   0：未接收到数据
// 使用示例     uint8 dat; uart_query_byte(USART_1,&dat);       // 接收串口1数据  存在在dat变量里
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_query_byte(uart_index_enum uartn, uint8 *dat)
{
    if((((USART_TypeDef*)uart_index[uartn])->STATR & USART_FLAG_RXNE) != 0)
    {
        *dat = (((USART_TypeDef*)uart_index[uartn])->DATAR & 0xFF);
        return 1;
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口初始化
// 参数说明     uartn       串口通道
// 参数说明     baud        波特率
// 参数说明     tx_pin      串口发送引脚号
// 参数说明     rx_pin      串口接收引脚号
// 返回参数     void
// 使用示例     uart_init(UART_1, 115200, UART1_TX_A9, UART1_RX_A10); //串口1初始化引脚号,TX为A9,RX为A10
//-------------------------------------------------------------------------------------------------------------------
void uart_init(uart_index_enum uart_n, uint32 baud, uart_pin_enum tx_pin, uart_pin_enum rx_pin)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // RX和TX引脚需要传入同一组映射引脚，如果不同就会进断言
    zf_assert((tx_pin & (uart_n << 12)) == (rx_pin & (uart_n << 12)));      // tx_pin 与 rx_pin 必须与 uart_n 匹配
    zf_assert((tx_pin >> 8) == (rx_pin >> 8));                              // tx_pin 与 rx_pin 必须成组传入

    gpio_init(tx_pin & 0xFF, GPO, 0, GPO_AF_PUSH_PULL);
    gpio_init(rx_pin & 0xFF, GPI, 0, GPI_PULL_UP);

    // AFIO总线开启
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    switch(tx_pin & 0xFFFF)
    {
        case UART1_MAP1_TX_B6:
           AFIO->PCFR2 &= ~(0x01<<26);
           AFIO->PCFR1 &= ~(0x01<<2);
           AFIO->PCFR1 |=  (0x01<<2);
           break;
        case UART1_MAP2_TX_B15:
            AFIO->PCFR2 &= ~(0x01<<26);
            AFIO->PCFR2 |=  (0x01<<26);
            AFIO->PCFR1 &= ~(0x01<<2);
           break;
        case UART1_MAP3_TX_A6:
            AFIO->PCFR2 &= ~(0x01<<26);
            AFIO->PCFR2 |=  (0x01<<26);
            AFIO->PCFR1 &= ~(0x01<<2);
            AFIO->PCFR1 |=  (0x01<<2);
           break;

        case UART2_MAP1_TX_D5:
            AFIO->PCFR1 &= ~(0x01<<3);
            AFIO->PCFR1 |=  (0x01<<3);
           break;

        case UART3_MAP1_TX_C10:
            AFIO->PCFR1 &= ~(0x03<<3);
            AFIO->PCFR1 |=  (0x01<<3);
           break;

        case UART3_MAP2_TX_D8:
            AFIO->PCFR1 &= ~(0x03<<3);
            AFIO->PCFR1 |=  (0x03<<3);
           break;

        case UART4_MAP1_TX_B0:
            AFIO->PCFR2 &= ~(0x03<<16);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 16);
           break;

        case UART4_MAP3_TX_E0:
            AFIO->PCFR2 &= ~(0x03<<16);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 16);
           break;

        case UART5_MAP1_TX_B4:
            AFIO->PCFR2 &= ~(0x03<<18);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 18);
           break;

        case UART5_MAP3_TX_E8:
            AFIO->PCFR2 &= ~(0x03<<18);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 18);
           break;

        case UART6_MAP1_TX_B8:
            AFIO->PCFR2 &= ~(0x03<<20);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 20);
           break;

        case UART6_MAP3_TX_E10:
            AFIO->PCFR2 &= ~(0x03<<20);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 20);
           break;

        case UART7_MAP1_TX_A6:
            AFIO->PCFR2 &= ~(0x03<<22);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 22);
           break;

        case UART7_MAP3_TX_E12:
            AFIO->PCFR2 &= ~(0x03<<22);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 22);
           break;

        case UART8_MAP1_TX_A14:
            AFIO->PCFR2 &= ~(0x03<<24);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 24);
           break;

        case UART8_MAP3_TX_E14:
            AFIO->PCFR2 &= ~(0x03<<24);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 24);
           break;
    }


    // 串口总线使能
    if(UART_1 == uart_n)        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    else if(UART_2 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    else if(UART_3 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    else if(UART_4 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,  ENABLE);
    else if(UART_5 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,  ENABLE);
    else if(UART_6 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART6,  ENABLE);
    else if(UART_7 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7,  ENABLE);
    else if(UART_8 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8,  ENABLE);

    // 串口参数配置
    USART_InitTypeDef USART_InitStructure = {0};
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    // 使能串口
    USART_Init((USART_TypeDef*)uart_index[uart_n], &USART_InitStructure);
    USART_Cmd((USART_TypeDef*)uart_index[uart_n], ENABLE);

}




