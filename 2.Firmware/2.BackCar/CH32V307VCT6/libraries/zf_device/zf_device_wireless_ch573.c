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

#include "zf_common_fifo.h"
#include "zf_device_type.h"
#include "zf_device_wireless_ch573.h"

static  fifo_struct       wireless_ch573_fifo;
static  uint8             wireless_ch573_buffer[WIRELESS_CH573_BUFFER_SIZE];                                // 对应第一个 无线串口 数据存放数组

static  uint8             wireless_ch573_data;

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      CH573无线模块中断回调函数
// 参数说明     void
// 返回参数     void
// Sample usage:
// @note
//-------------------------------------------------------------------------------------------------------------------
void wireless_ch573_callback (void)
{
    uart_query_byte(WIRELESS_CH573_INDEX, &wireless_ch573_data);
    fifo_write_buffer(&wireless_ch573_fifo, &wireless_ch573_data, 1);

}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介      无线转串口模块 发送数据
// 参数说明     data            8bit 数据
// 返回参数     uint32          剩余发送长度
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_ch573_send_byte (const uint8 data)
{
    uint16 time_count = 0;
    while(gpio_get_level(WIRELESS_CH573_RTS_PIN))                                      // 如果RTS为低电平，则继续发送数据
    {
        if(time_count++ > WIRELESS_CH573_TIMEOUT_COUNT)
            return 1;                                                           // 模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
        system_delay_ms(1);
    }
    uart_write_byte(WIRELESS_CH573_INDEX, data);                                 // 发送最后的数据

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      CH573无线模块 串口发送数据
// 参数说明     buff            数据地址
// 参数说明     len             数据长度
// 返回参数     uint32        提示信息
// Sample usage:
// @note
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_ch573_send_buff (const uint8 *buff, uint32 len)
{
    uint16 time_count = 0;
    uint8 pack_len = 62;
    while(len > pack_len)
    {
        time_count = 0;
        while(gpio_get_level(WIRELESS_CH573_RTS_PIN) && time_count++ < WIRELESS_CH573_TIMEOUT_COUNT)  // 如果RTS为低电平，则继续发送数据
            system_delay_ms(1);
        if(time_count >= WIRELESS_CH573_TIMEOUT_COUNT)
            return len;                                                                             // 模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
        uart_write_buffer(WIRELESS_CH573_INDEX, buff, 30);

        buff += pack_len;                                                                           // 地址偏移
        len -= pack_len;                                                                            // 数量
    }

    time_count = 0;
    while(gpio_get_level(WIRELESS_CH573_RTS_PIN) && time_count++ < WIRELESS_CH573_TIMEOUT_COUNT)  // 如果RTS为低电平，则继续发送数据
        system_delay_ms(1);
    if(time_count >= WIRELESS_CH573_TIMEOUT_COUNT)
        return len;                                                                                 // 模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
    uart_write_buffer(WIRELESS_CH573_INDEX, buff, len);                                            // 发送最后的数据

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      CH573无线模块 串口接收数据
// 参数说明     buff            数据地址
// 参数说明     len             数据长度
// 返回参数     void
// Sample usage:
// @note
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_ch573_read_buff (uint8 *buff, uint32 len)
{
    uint32 data_len = len;
    fifo_read_buffer(&wireless_ch573_fifo, buff, &data_len, FIFO_READ_AND_CLEAN);
    return data_len;
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介      无线转串口模块 发送摄像头图像至上位机查看图像
// 参数说明     *image_addr     需要发送的图像地址
// 参数说明     image_size      图像的大小
// 返回参数     void
// 使用示例     wireless_uart_send_image(&mt9v03x_image[0][0], MT9V03X_IMAGE_SIZE);
//-------------------------------------------------------------------------------------------------------------------
void wireless_ch573_send_image (const uint8 *image_addr, uint32 image_size)
{
    extern uint8 camera_send_image_frame_header[4];
    wireless_ch573_send_buff(camera_send_image_frame_header, 4);
    wireless_ch573_send_buff((uint8 *)image_addr, image_size);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      CH573无线模块初始化
// 参数说明     void
// 返回参数     void
// Sample usage:
// @note
//-------------------------------------------------------------------------------------------------------------------
uint8 wireless_ch573_init (void)
{

    set_wireless_type(WIRELESS_CH573, wireless_ch573_callback);



    fifo_init(&wireless_ch573_fifo, FIFO_DATA_8BIT, wireless_ch573_buffer, WIRELESS_CH573_BUFFER_SIZE);
    gpio_init(WIRELESS_CH573_RTS_PIN, GPI, GPIO_HIGH, GPI_PULL_UP);

    uart_init (WIRELESS_CH573_INDEX, WIRELESS_CH573_BUAD_RATE, WIRELESS_CH573_RX_PIN, WIRELESS_CH573_TX_PIN);
    uart_rx_interrupt(WIRELESS_CH573_INDEX, 1);

    return 0;
}



