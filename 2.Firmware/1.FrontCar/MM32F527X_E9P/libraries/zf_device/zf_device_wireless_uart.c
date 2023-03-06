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

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_fifo.h"
#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"
#include "zf_device_type.h"

#include "zf_device_wireless_uart.h"

static  fifo_struct                                     wireless_uart_fifo;
static  uint8                                           wireless_uart_buffer[WIRELESS_UART_BUFFER_SIZE];

static          uint8                                   wireless_uart_data          = 0;
#if (1 == WIRELESS_UART_AUTO_BAUD_RATE)
static volatile wireless_uart_auto_baudrate_state_enum  wireless_auto_baud_flag     = WIRELESS_UART_AUTO_BAUD_RATE_INIT;
static volatile uint8                                   wireless_auto_baud_data[3]  = {0x00, 0x01, 0x03};
#endif

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     无线转串口模块 发送数据
// 参数说明     data            8bit 数据
// 返回参数     uint32          剩余发送长度
// 使用示例     wireless_uart_send_byte(data);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_uart_send_byte (const uint8 data)
{
    uint16 time_count = WIRELESS_UART_TIMEOUT_COUNT;
    while(time_count)
    {
        if(!gpio_get_level(WIRELESS_UART_RTS_PIN))
        {
            uart_write_byte(WIRELESS_UART_INDEX, data);                         // 发送数据
            break;
        }
        time_count --;
        system_delay_ms(1);
    }
    return (0 < time_count);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     无线转串口模块 发送数据块
// 参数说明     *buff           发送缓冲区
// 参数说明     len             发送数据长度
// 返回参数     uint32          剩余发送长度
// 使用示例     wireless_uart_send_buff(buff, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_uart_send_buff (const uint8 *buff, uint32 len)
{
    zf_assert(NULL != buff);
    uint16 time_count = 0;
    while(0 != len)
    {
        if(!gpio_get_level(WIRELESS_UART_RTS_PIN))                              // 如果RTS为低电平 则继续发送数据
        {
            if(30 <= len)                                                       // 数据分 30byte 每包发送
            {
                uart_write_buffer(WIRELESS_UART_INDEX, buff, 30);               // 发送数据
                buff += 30;                                                     // 地址偏移
                len -= 30;                                                      // 数量
                time_count = 0;
            }
            else                                                                // 不足 30byte 的数据一次性发送完毕
            {
                uart_write_buffer(WIRELESS_UART_INDEX, buff, len);              // 发送数据
                len = 0;
                break;
            }
        }
        else                                                                    // 如果RTS为高电平 则模块忙
        {
            if(WIRELESS_UART_TIMEOUT_COUNT <= (++ time_count))                  // 超出了最大等待时间
            {
                break;                                                          // 退出发送
            }
            system_delay_ms(1);
        }
    }
    return len;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     无线转串口模块 发送字符串
// 参数说明     *str            要发送的字符串地址
// 返回参数     uint32          剩余发送长度
// 使用示例     wireless_uart_send_string("Believe in yourself.");
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_uart_send_string (const char *str)
{
    zf_assert(NULL != str);
    uint16 time_count = 0;
    uint32 len = strlen(str);
    while(0 != len)
    {
        if(!gpio_get_level(WIRELESS_UART_RTS_PIN))                              // 如果RTS为低电平 则继续发送数据
        {
            if(30 <= len)                                                       // 数据分 30byte 每包发送
            {
                uart_write_buffer(WIRELESS_UART_INDEX, (const uint8 *)str, 30); // 发送数据
                str += 30;                                                      // 地址偏移
                len -= 30;                                                      // 数量
                time_count = 0;
            }
            else                                                                // 不足 30byte 的数据一次性发送完毕
            {
                uart_write_buffer(WIRELESS_UART_INDEX, (const uint8 *)str, len);// 发送数据
                len = 0;
                break;
            }
        }
        else                                                                    // 如果RTS为高电平 则模块忙
        {
            if(WIRELESS_UART_TIMEOUT_COUNT <= (++ time_count))                  // 超出了最大等待时间
            {
                break;                                                          // 退出发送
            }
            system_delay_ms(1);
        }
    }
    return len;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     无线转串口模块 发送摄像头图像至上位机查看图像
// 参数说明     *image_addr     需要发送的图像地址
// 参数说明     image_size      图像的大小
// 返回参数     void
// 使用示例     wireless_uart_send_image(&mt9v03x_image[0][0], MT9V03X_IMAGE_SIZE);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart_send_image (const uint8 *image_addr, uint32 image_size)
{
    zf_assert(NULL != image_addr);
    extern uint8 camera_send_image_frame_header[4];
    wireless_uart_send_buff(camera_send_image_frame_header, 4);
    wireless_uart_send_buff((uint8 *)image_addr, image_size);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     无线转串口模块 读取缓冲
// 参数说明     *buff           接收缓冲区
// 参数说明     len             读取数据长度
// 返回参数     uint32          实际读取数据长度
// 使用示例     wireless_uart_read_buff(buff, 32);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_uart_read_buff (uint8 *buff, uint32 len)
{
    zf_assert(NULL != buff);
    uint32 data_len = len;
    fifo_read_buffer(&wireless_uart_fifo, buff, &data_len, FIFO_READ_AND_CLEAN);
    return data_len;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     无线转串口模块 串口中断回调函数
// 参数说明     void
// 返回参数     void
// 使用示例     wireless_uart_callback();
// 备注信息     该函数在 ISR 文件 串口中断程序被调用
//              由串口中断服务函数调用 wireless_module_uart_handler() 函数
//              再由 wireless_module_uart_handler() 函数调用本函数
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart_callback (void)
{
    uart_query_byte(WIRELESS_UART_INDEX, &wireless_uart_data);
    fifo_write_buffer(&wireless_uart_fifo, &wireless_uart_data, 1);
#if WIRELESS_UART_AUTO_BAUD_RATE                                                // 开启自动波特率
    if(WIRELESS_UART_AUTO_BAUD_RATE_START == wireless_auto_baud_flag && 3 == fifo_used(&wireless_uart_fifo))
    {
        uint32 wireless_auto_baud_count = 3;
        wireless_auto_baud_flag = WIRELESS_UART_AUTO_BAUD_RATE_GET_ACK;
        fifo_read_buffer(&wireless_uart_fifo, (uint8 *)wireless_auto_baud_data, (uint32 *)&wireless_auto_baud_count, FIFO_READ_AND_CLEAN);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     无线转串口模块 初始化
// 参数说明     void
// 返回参数     void
// 使用示例     wireless_uart_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 wireless_uart_init (void)
{
    uint8 return_state = 0;
    set_wireless_type(WIRELESS_UART, wireless_uart_callback);

    fifo_init(&wireless_uart_fifo, FIFO_DATA_8BIT, wireless_uart_buffer, WIRELESS_UART_BUFFER_SIZE);
    gpio_init(WIRELESS_UART_RTS_PIN, GPI, GPIO_HIGH, GPI_PULL_UP);
#if(0 == WIRELESS_UART_AUTO_BAUD_RATE)                                          // 关闭自动波特率
    // 本函数使用的波特率为115200 为无线转串口模块的默认波特率 如需其他波特率请自行配置模块并修改串口的波特率
    uart_init (WIRELESS_UART_INDEX, WIRELESS_UART_BUAD_RATE, WIRELESS_UART_RX_PIN, WIRELESS_UART_TX_PIN);   // 初始化串口
    uart_rx_interrupt(WIRELESS_UART_INDEX, 1);
#elif(1 == WIRELESS_UART_AUTO_BAUD_RATE)                                        // 开启自动波特率
    uint8 rts_init_status = 0;
    uint16 time_count = 0;

    wireless_auto_baud_flag = WIRELESS_UART_AUTO_BAUD_RATE_INIT;
    wireless_auto_baud_data[0] = 0;
    wireless_auto_baud_data[1] = 1;
    wireless_auto_baud_data[2] = 3;

    rts_init_status = gpio_get_level(WIRELESS_UART_RTS_PIN);
    gpio_init(WIRELESS_UART_RTS_PIN, GPO, rts_init_status, GPO_PUSH_PULL);      // 初始化流控引脚

    uart_init (WIRELESS_UART_INDEX, WIRELESS_UART_BUAD_RATE, WIRELESS_UART_RX_PIN, WIRELESS_UART_TX_PIN);   // 初始化串口
    uart_rx_interrupt(WIRELESS_UART_INDEX, 1);

    system_delay_ms(5);                                                         // 模块上电之后需要延时等待
    gpio_set_level(WIRELESS_UART_RTS_PIN, !rts_init_status);                    // RTS引脚拉高，进入自动波特率模式
    system_delay_ms(100);                                                       // RTS拉高之后必须延时20ms
    gpio_toggle_level(WIRELESS_UART_RTS_PIN);                                   // RTS引脚取反

    do
    {
        wireless_auto_baud_flag = WIRELESS_UART_AUTO_BAUD_RATE_START;
        uart_write_byte(WIRELESS_UART_INDEX, wireless_auto_baud_data[0]);       // 发送特定数据 用于模块自动判断波特率
        uart_write_byte(WIRELESS_UART_INDEX, wireless_auto_baud_data[1]);       // 发送特定数据 用于模块自动判断波特率
        uart_write_byte(WIRELESS_UART_INDEX, wireless_auto_baud_data[2]);       // 发送特定数据 用于模块自动判断波特率
        system_delay_ms(20);

        if(WIRELESS_UART_AUTO_BAUD_RATE_GET_ACK != wireless_auto_baud_flag)     // 检验自动波特率是否完成
        {
            return_state = 1;                                                   // 如果程序进入到此语句内 说明自动波特率失败了
            break;
        }

        time_count = 0;
        if( 0xa5 != wireless_auto_baud_data[0] &&                               // 检验自动波特率是否正确
            0xff != wireless_auto_baud_data[1] &&                               // 检验自动波特率是否正确
            0xff != wireless_auto_baud_data[2] )                                // 检验自动波特率是否正确
        {
            return_state = 1;                                                   // 如果程序进入到此语句内 说明自动波特率失败了
            break;
        }
        wireless_auto_baud_flag = WIRELESS_UART_AUTO_BAUD_RATE_SUCCESS;

        gpio_init(WIRELESS_UART_RTS_PIN, GPI, 0, GPI_PULL_UP);                  // 初始化流控引脚
        system_delay_ms(10);                                                    // 延时等待 模块准备就绪
    }while(0);
#endif
    return return_state;
}
