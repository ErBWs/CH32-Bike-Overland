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
* 文件名称          zf_device_ips350
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
*                   RD                  查看 zf_device_ips350.h 中 IPS350_RD_PIN_PARALLEL8     宏定义
*                   WR                  查看 zf_device_ips350.h 中 IPS350_WR_PIN_PARALLEL8     宏定义
*                   RS                  查看 zf_device_ips350.h 中 IPS350_RS_PIN_PARALLEL8     宏定义
*                   RST                 查看 zf_device_ips350.h 中 IPS350_RST_PIN_PARALLEL8    宏定义
*                   CS                  查看 zf_device_ips350.h 中 IPS350_CS_PIN_PARALLEL8     宏定义
*                   BL                  查看 zf_device_ips350.h 中 IPS350_BL_PIN_PARALLEL8     宏定义
*                   D0-D7               查看 zf_device_ips350.h 中 IPS350_Dx_PIN_PARALLEL8     宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   最大分辨率 320 * 240
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_font.h"
#include "zf_common_function.h"
#include "zf_driver_delay.h"
#include "zf_driver_fsmc.h"
#include "zf_driver_gpio.h"
#include "zf_driver_soft_spi.h"
#include "zf_driver_spi.h"

#include "zf_device_ips350.h"

static uint16                   ips350_pencolor     = IPS350_DEFAULT_PENCOLOR;
static uint16                   ips350_bgcolor      = IPS350_DEFAULT_BGCOLOR;

static ips350_dir_enum          ips350_display_dir  = IPS350_DEFAULT_DISPLAY_DIR;
static ips350_font_size_enum    ips350_display_font = IPS350_DEFAULT_DISPLAY_FONT;

static uint16 ips350_x_max = 320;
static uint16 ips350_y_max = 480;

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 写数据
// 参数说明     dat             数据
// 返回参数     void
// 使用示例     ips350_write_data(x1 >> 8);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
//static void ips350_write_data (const uint16 dat)
//{
//    IPS350_WR(0);
//    *(volatile uint16 *)IPS350_DATA_ADD = dat;
//    IPS350_WR(1);
//}
#define ips350_write_data(x)    (*(volatile uint16 *)IPS350_DATA_ADD = (x & 0xFFFF))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 写命令
// 参数说明     command         命令
// 返回参数     void
// 使用示例     ips350_write_command(0x2a);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void ips350_write_command (const uint8 command)
{
    *(volatile uint16 *)IPS350_CMD_ADD = command & 0xFFFF;
//    IPS350_WR(0);
//    *(volatile uint16 *)IPS350_CMD_ADD = command & 0xFFFF;
//    IPS350_WR(1);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示区域
// 参数说明     x1              起始x轴坐标
// 参数说明     y1              起始y轴坐标
// 参数说明     x2              结束x轴坐标
// 参数说明     y2              结束y轴坐标
// 返回参数     void
// 使用示例     ips350_set_region(0, 0, ips350_x_max - 1, ips350_y_max - 1);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void ips350_set_region (uint16 x1, uint16 y1, uint16 x2, uint16 y2)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    // 检查一下你的显示调用的函数 自己计算一下哪里超过了屏幕显示范围
    zf_assert(x1 < ips350_x_max);
    zf_assert(y1 < ips350_y_max);
    zf_assert(x2 < ips350_x_max);
    zf_assert(y2 < ips350_y_max);

    ips350_write_command(0x2a);
    ips350_write_data(x1 >> 8);
    ips350_write_data(x1 & 0x00FF);
    ips350_write_data(x2 >> 8);
    ips350_write_data(x2 & 0x00FF);
    
    ips350_write_command(0x2b);
    ips350_write_data(y1 >> 8);
    ips350_write_data(y1 & 0x00FF);
    ips350_write_data(y2 >> 8);
    ips350_write_data(y2 & 0x00FF);
    
    ips350_write_command(0x2c);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     2寸 IPS液晶显示DEBUG信息初始化
// 参数说明     void
// 返回参数     void
// 使用示例     ips350_debug_init();
// 备注信息     内部使用
//-------------------------------------------------------------------------------------------------------------------
void ips350_debug_init (void)
{
    debug_output_struct info;
    debug_output_struct_init(&info);

    info.type_index = 1;
    info.display_x_max = ips350_x_max;
    info.display_y_max = ips350_y_max;

    switch(ips350_display_font)
    {
        case IPS350_6X8_FONT:
        {
            info.font_x_size = 6;
            info.font_y_size = 8;
        }break;
        case IPS350_8X16_FONT:
        {
            info.font_x_size = 8;
            info.font_y_size = 16;
        }break;
        case IPS350_16X16_FONT:
        {
            // 暂不支持
        }break;
    }
    info.output_screen = ips350_show_string;
    info.output_screen_clear = ips350_clear;
        
    debug_output_init(&info);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     液晶清屏函数
// 参数说明     void
// 返回参数     void
// 使用示例     ips350_clear();
// 备注信息     将屏幕清空成背景颜色
//-------------------------------------------------------------------------------------------------------------------
void ips350_clear (void)
{
    uint16 i = 0, j = 0;
    ips350_set_region(0, 0, ips350_x_max - 1, ips350_y_max - 1);
    for(i = 0; i < ips350_x_max; i ++)
    {
        for (j = 0; j < ips350_y_max; j ++)
        {
            ips350_write_data(ips350_bgcolor);                 
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     液晶屏幕填充函数
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内常用颜色宏定义
// 返回参数     void
// 使用示例     ips350_full(RGB565_BLACK);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips350_full (const uint16 color)
{
    uint16 i = 0, j = 0;
    ips350_set_region(0, 0, ips350_x_max - 1, ips350_y_max - 1);
    for(i = 0; i < ips350_x_max; i ++)
    {
        for (j = 0; j < ips350_y_max; j ++)
        {
            ips350_write_data(color);                 
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示方向
// 参数说明     dir             显示方向  参照 zf_device_ips350.h 内 ips350_dir_enum 枚举体定义
// 返回参数     void
// 使用示例     ips350_set_dir(IPS350_PORTAIT);
// 备注信息     这个函数只有在初始化屏幕之前调用才生效
//-------------------------------------------------------------------------------------------------------------------
void ips350_set_dir (ips350_dir_enum dir)
{
    ips350_display_dir = dir;
    switch(ips350_display_dir)
    {
        case IPS350_PORTAIT:
        case IPS350_PORTAIT_180:
        {
            ips350_x_max = 320;
            ips350_y_max = 480;
        }break;
        case IPS350_CROSSWISE:
        case IPS350_CROSSWISE_180:
        {
            ips350_x_max = 480;
            ips350_y_max = 320;
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示字体
// 参数说明     dir             显示方向  参照 zf_device_ips350.h 内 ips350_font_size_enum 枚举体定义
// 返回参数     void
// 使用示例     ips350_set_font(IPS350_8x16_FONT);
// 备注信息     这个函数只有在初始化屏幕之前调用才生效
//-------------------------------------------------------------------------------------------------------------------
void ips350_set_font (ips350_font_size_enum font)
{
    ips350_display_font = font;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示颜色
// 参数说明     pen             颜色格式 RGB565 或者可以使用 zf_common_font.h 内常用颜色宏定义
// 参数说明     bgcolor         颜色格式 RGB565 或者可以使用 zf_common_font.h 内常用颜色宏定义
// 返回参数     void
// 使用示例     ips350_set_color(RGB565_RED, RGB565_GRAY);
// 备注信息     字体颜色和背景颜色也可以随时自由设置 设置后生效
//-------------------------------------------------------------------------------------------------------------------
void ips350_set_color (const uint16 pen, const uint16 bgcolor)
{
    ips350_pencolor = pen;
    ips350_bgcolor = bgcolor;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 画点
// 参数说明     x               坐标x方向的起点
// 参数说明     y               坐标y方向的起点
// 参数说明     dat             需要显示的颜色
// 返回参数     void
// 使用示例     ips350_draw_point(0, 0, RGB565_RED);            //坐标0,0画一个红色的点
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips350_draw_point (uint16 x, uint16 y, const uint16 color)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips350_x_max);
    zf_assert(y < ips350_y_max);

    ips350_set_region(x, y, x, y);
    ips350_write_data(color);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 画线
// 参数说明     x_start         坐标x方向的起点
// 参数说明     y_start         坐标y方向的起点
// 参数说明     x_end           坐标x方向的终点
// 参数说明     y_end           坐标y方向的终点
// 参数说明     dat             需要显示的颜色
// 返回参数     void
// 使用示例     ips350_draw_line(0, 0, 10, 10, RGB565_RED);     // 坐标 0,0 到 10,10 画一条红色的线
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips350_draw_line (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x_start < ips350_x_max);
    zf_assert(y_start < ips350_y_max);
    zf_assert(x_end < ips350_x_max);
    zf_assert(y_end < ips350_y_max);

    int16 x_dir = (x_start < x_end ? 1 : -1);
    int16 y_dir = (y_start < y_end ? 1 : -1);
    float temp_rate = 0;
    float temp_b = 0;
    if(x_start != x_end)
    {
        temp_rate = (float)(y_start - y_end) / (float)(x_start - x_end);
        temp_b = (float)y_start - (float)x_start * temp_rate;
    }
    else
    {
        while(y_start != y_end)
        {
            ips350_draw_point(x_start, y_start, color);
            y_start += y_dir;
        }
        return;
    }
    if(func_abs(y_start - y_end) > func_abs(x_start - x_end))
    {
        while(y_start != y_end)
        {
            ips350_draw_point(x_start, y_start, color);
            y_start += y_dir;
            x_start = (int16)(((float)y_start - temp_b) / temp_rate);
        }
    }
    else
    {
        while(x_start != x_end)
        {
            ips350_draw_point(x_start, y_start, color);
            x_start += x_dir;
            y_start = (int16)((float)x_start * temp_rate + temp_b);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 显示字符
// 参数说明     x               坐标x方向的起点 参数范围 0 - (ips350_x_max-1)
// 参数说明     y               坐标y方向的起点 参数范围 0 - (ips350_y_max/16-1)
// 参数说明     dat             需要显示的字符
// 返回参数     void
// 使用示例     ips350_show_char(0, 0, 'x');                     // 坐标0,0写一个字符x
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips350_show_char (uint16 x, uint16 y, const char dat)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips350_x_max);
    zf_assert(y < ips350_y_max);

    uint8 i = 0, j = 0;

    switch(ips350_display_font)
    {
        case IPS350_6X8_FONT:
        {
            for(i = 0; 6 > i; i ++)
            {
                ips350_set_region(x + i, y, x + i, y + 8);
                // 减 32 因为是取模是从空格开始取得 空格在 ascii 中序号是 32
                uint8 temp_top = ascii_font_6x8[dat - 32][i];
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        ips350_write_data(ips350_pencolor);
                    }
                    else
                    {
                        ips350_write_data(ips350_bgcolor);
                    }
                    temp_top >>= 1;
                }
            }
        }break;
        case IPS350_8X16_FONT:
        {
            for(i = 0; 8 > i; i ++)
            {
                ips350_set_region(x + i, y, x + i, y + 15);
                // 减 32 因为是取模是从空格开始取得 空格在 ascii 中序号是 32
                uint8 temp_top = ascii_font_8x16[dat - 32][i];
                uint8 temp_bottom = ascii_font_8x16[dat - 32][i + 8];
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        ips350_write_data(ips350_pencolor);
                    }
                    else
                    {
                        ips350_write_data(ips350_bgcolor);
                    }
                    temp_top >>= 1;
                }
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_bottom & 0x01)
                    {
                        ips350_write_data(ips350_pencolor);
                    }
                    else
                    {
                        ips350_write_data(ips350_bgcolor);
                    }
                    temp_bottom >>= 1;
                }
            }
        }break;
        case IPS350_16X16_FONT:
        {
            // 暂不支持
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 显示字符串
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips350_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips350_y_max-1]
// 参数说明     dat             需要显示的字符串
// 返回参数     void
// 使用示例     ips350_show_string(0, 0, "seekfree");
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips350_show_string (uint16 x, uint16 y, const char dat[])
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips350_x_max);
    zf_assert(y < ips350_y_max);
    
    uint16 j = 0;
    while('\0' != dat[j])
    {
        switch(ips350_display_font)
        {
            case IPS350_6X8_FONT:   ips350_show_char(x + 6 * j, y, dat[j]); break;
            case IPS350_8X16_FONT:  ips350_show_char(x + 8 * j, y, dat[j]); break;
            case IPS350_16X16_FONT: break;                                      // 暂不支持
        }
        j ++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 显示32位有符号 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips350_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips350_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 int32
// 参数说明     num             需要显示的位数 最高10位  不包含正负号
// 返回参数     void
// 使用示例     ips350_show_int(0, 0, x, 3);                    // x 可以为 int32 int16 int8 类型
// 备注信息     负数会显示一个 ‘-’号
//-------------------------------------------------------------------------------------------------------------------
void ips350_show_int (uint16 x, uint16 y, const int32 dat, uint8 num)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips350_x_max);
    zf_assert(y < ips350_y_max);
    zf_assert(0 < num);
    zf_assert(10 >= num);

    int32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];

    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num+1);

    // 用来计算余数显示 123 显示 2 位则应该显示 23
    if(10 > num)
    {
        for(; 0 < num; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_int_to_str(data_buffer, dat_temp);
    ips350_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 显示32位无符号 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips114_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips114_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 uint32
// 参数说明     num             需要显示的位数 最高10位  不包含正负号
// 返回参数     void
// 使用示例     ips350_show_uint(0, 0, x, 3);                   // x 可以为 uint32 uint16 uint8 类型
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips350_show_uint (uint16 x, uint16 y, const uint32 dat, uint8 num)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips350_x_max);
    zf_assert(y < ips350_y_max);
    zf_assert(0 < num);
    zf_assert(10 >= num);

    uint32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];
    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num);

    // 用来计算余数显示 123 显示 2 位则应该显示 23
    if(10 > num)
    {
        for(; 0 < num; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_uint_to_str(data_buffer, dat_temp);
    ips350_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 显示浮点数(去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips350_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips350_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 float
// 参数说明     num             整数位显示长度   最高8位  
// 参数说明     pointnum        小数位显示长度   最高6位
// 返回参数     void
// 使用示例     ips350_show_float(0, 0, x, 2, 3);               // 显示浮点数   整数显示2位   小数显示三位
// 备注信息     特别注意当发现小数部分显示的值与你写入的值不一样的时候，
//              可能是由于浮点数精度丢失问题导致的，这并不是显示函数的问题，
//              有关问题的详情，请自行百度学习   浮点数精度丢失问题。
//              负数会显示一个 ‘-’号
//-------------------------------------------------------------------------------------------------------------------
void ips350_show_float (uint16 x, uint16 y, const float dat, uint8 num, uint8 pointnum)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips350_x_max);
    zf_assert(y < ips350_y_max);
    zf_assert(0 < num);
    zf_assert(8 >= num);
    zf_assert(0 < pointnum);
    zf_assert(6 >= pointnum);

    float dat_temp = dat;
    float offset = 1.0;
    char data_buffer[17];
    memset(data_buffer, 0, 17);
    memset(data_buffer, ' ', num+pointnum+2);

    // 用来计算余数显示 123 显示 2 位则应该显示 23
    for(; 0 < num; num --)
    {
        offset *= 10;
    }
    dat_temp = dat_temp - ((int)dat_temp / (int)offset) * offset;
    func_float_to_str(data_buffer, dat_temp, pointnum);
    ips350_show_string(x, y, data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 显示二值图像 数据每八个点组成一个字节数据
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips350_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips350_y_max-1]
// 参数说明     *image          图像数组指针
// 参数说明     width           图像实际宽度
// 参数说明     height          图像实际高度
// 参数说明     dis_width       图像显示宽度 参数范围 [0, ips350_x_max]
// 参数说明     dis_height      图像显示高度 参数范围 [0, ips350_y_max]
// 返回参数     void
// 使用示例     ips350_show_binary_image(0, 0, ov7725_image_binary[0], OV7725_W, OV7725_H, OV7725_W, OV7725_H);
// 备注信息     用于显示小钻风的未解压的压缩二值化图像
//              这个函数不可以用来直接显示总钻风的未压缩的二值化图像
//              这个函数不可以用来直接显示总钻风的未压缩的二值化图像
//              这个函数不可以用来直接显示总钻风的未压缩的二值化图像
//-------------------------------------------------------------------------------------------------------------------
void ips350_show_binary_image (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips350_x_max);
    zf_assert(y < ips350_y_max);
    zf_assert(NULL != image);

    uint32 i = 0, j = 0;
    uint8 temp = 0;
    uint32 width_index = 0, height_index = 0;

    ips350_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // 设置显示区域

    for(j = 0; j < dis_height; j ++)
    {
        height_index = j * height / dis_height;
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            temp = *(image + height_index * width / 8 + width_index / 8);       // 读取像素点
            if(0x80 & (temp << (width_index % 8)))
            {
                ips350_write_data(RGB565_WHITE);
            }
            else
            {
                ips350_write_data(RGB565_BLACK);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 显示 8bit 灰度图像 带二值化阈值
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips350_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips350_y_max-1]
// 参数说明     *image          图像数组指针
// 参数说明     width           图像实际宽度
// 参数说明     height          图像实际高度
// 参数说明     dis_width       图像显示宽度 参数范围 [0, ips350_x_max]
// 参数说明     dis_height      图像显示高度 参数范围 [0, ips350_y_max]
// 参数说明     threshold       二值化显示阈值 0-不开启二值化
// 返回参数     void
// 使用示例     ips350_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
// 备注信息     用于显示总钻风的图像
//              如果要显示二值化图像 直接修改最后一个参数为需要的二值化阈值即可
//              如果要显示二值化图像 直接修改最后一个参数为需要的二值化阈值即可
//              如果要显示二值化图像 直接修改最后一个参数为需要的二值化阈值即可
//-------------------------------------------------------------------------------------------------------------------
void ips350_show_gray_image (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips350_x_max);
    zf_assert(y < ips350_y_max);
    zf_assert(NULL != image);

    uint32 i = 0, j = 0;
    uint16 color = 0,temp = 0;
    uint32 width_index = 0, height_index = 0;

    ips350_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // 设置显示区域

    for(j = 0; j < dis_height; j ++)
    {
        height_index = j * height / dis_height;
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            temp = *(image + height_index * width + width_index);               // 读取像素点
            if(threshold == 0)
            {
                color = (0x001f & ((temp) >> 3)) << 11;
                color = color | (((0x003f) & ((temp) >> 2)) << 5);
                color = color | (0x001f & ((temp) >> 3));
                ips350_write_data(color);
            }
            else if(temp < threshold)
            {
                ips350_write_data(RGB565_BLACK);
            }
            else
            {
                ips350_write_data(RGB565_WHITE);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 显示 RGB565 彩色图像
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips350_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips350_y_max-1]
// 参数说明     *image          图像数组指针
// 参数说明     width           图像实际宽度
// 参数说明     height          图像实际高度
// 参数说明     dis_width       图像显示宽度 参数范围 [0, ips350_x_max]
// 参数说明     dis_height      图像显示高度 参数范围 [0, ips350_y_max]
// 参数说明     color_mode      色彩模式 0-低位在前 1-高位在前
// 返回参数     void
// 使用示例     ips350_show_rgb565_image(0, 0, scc8660_image[0], SCC8660_W, SCC8660_H, SCC8660_W, SCC8660_H, 1);
// 备注信息     用于显示凌瞳的 RGB565 的图像
//              如果要显示低位在前的其他 RGB565 图像 修改最后一个参数即可
//              如果要显示低位在前的其他 RGB565 图像 修改最后一个参数即可
//              如果要显示低位在前的其他 RGB565 图像 修改最后一个参数即可
//-------------------------------------------------------------------------------------------------------------------
void ips350_show_rgb565_image (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips350_x_max);
    zf_assert(y < ips350_y_max);
    zf_assert(NULL != image);

    uint32 i = 0, j = 0;
    uint16 color = 0;
    uint32 width_index = 0, height_index = 0;

    ips350_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // 设置显示区域

    for(j = 0; j < dis_height; j ++)
    {
        height_index = j * height / dis_height;
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            color = *(image + height_index * width + width_index);              // 读取像素点
            if(color_mode)
            {
                color = ((color & 0xff) << 8) | (color >> 8);
            }
            ips350_write_data(color);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 显示波形
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips350_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips350_y_max-1]
// 参数说明     *wave           波形数组指针
// 参数说明     width           波形实际宽度
// 参数说明     value_max       波形实际最大值
// 参数说明     dis_width       波形显示宽度 参数范围 [0, ips350_x_max]
// 参数说明     dis_value_max   波形显示最大值 参数范围 [0, ips350_y_max]
// 返回参数     void
// 使用示例     ips350_show_wave(0, 0, data, 128, 64, 64, 32);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips350_show_wave (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips350_x_max);
    zf_assert(y < ips350_y_max);
    zf_assert(NULL != wave);

    uint32 i = 0, j = 0;
    uint32 width_index = 0, value_max_index = 0;

    ips350_set_region(x, y, x + dis_width - 1, y + dis_value_max - 1);          // 设置显示区域
    for(i = 0; i < dis_value_max; i ++)
    {
        for(j = 0; j < dis_width; j ++)
        {
            ips350_write_data(ips350_bgcolor); 
        }
    }

    for(i = 0; i < dis_width; i ++)
    {
        width_index = i * width / dis_width;
        value_max_index = *(wave + width_index) * (dis_value_max - 1) / value_max;
        ips350_draw_point(i + x, (dis_value_max - 1) - value_max_index + y, ips350_pencolor);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     汉字显示
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips350_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips350_y_max-1]
// 参数说明     size            取模的时候设置的汉字字体大小 也就是一个汉字占用的点阵长宽为多少个点 取模的时候需要长宽是一样的
// 参数说明     *chinese_buffer 需要显示的汉字数组
// 参数说明     number          需要显示多少位
// 参数说明     color           显示颜色
// 返回参数     void
// 使用示例     ips350_show_chinese(0, 0, 16, chinese_test[0], 4, RGB565_RED);//显示font文件里面的 示例
// 备注信息     使用PCtoLCD2002软件取模           阴码、逐行式、顺向   16*16
//-------------------------------------------------------------------------------------------------------------------
void ips350_show_chinese (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips350_x_max);
    zf_assert(y < ips350_y_max);
    zf_assert(NULL != chinese_buffer);

    int i = 0, j = 0, k = 0; 
    uint8 temp = 0, temp1 = 0, temp2 = 0;
    const uint8 *p_data = chinese_buffer;
    
    temp2 = size / 8;
    
    ips350_set_region(x, y, number * size - 1 + x, y + size - 1);
    
    for(i = 0; i < size; i ++)
    {
        temp1 = number;
        p_data = chinese_buffer + i * temp2;
        while(temp1 --)
        {
            for(k = 0; k < temp2; k ++)
            {
                for(j = 8; 0 < j; j --)
                {
                    temp = (*p_data >> (j - 1)) & 0x01;
                    if(temp)
                    {
                        ips350_write_data(color);
                    }
                    else
                    {
                        ips350_write_data(ips350_bgcolor);
                    }
                }
                p_data ++;
            }
            p_data = p_data - temp2 + temp2 * size;
        }   
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     2寸 IPS液晶初始化
// 参数说明     void
// 返回参数     void
// 使用示例     ips350_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips350_init (void)
{
    ips350_set_dir(ips350_display_dir);
    ips350_set_color(ips350_pencolor, ips350_bgcolor);

    gpio_init(IPS350_RST_PIN_PARALLEL8, GPO, GPIO_LOW, GPO_PUSH_PULL);          // RTS
    gpio_init(IPS350_BL_PIN_PARALLEL8, GPO, GPIO_LOW, GPO_PUSH_PULL);           // BL

//    gpio_init(IPS350_RD_PIN_PARALLEL8, GPO, GPIO_LOW, GPO_PUSH_PULL);           // FSMC_NOE IPS350_RD
//    gpio_init(IPS350_WR_PIN_PARALLEL8, GPO, GPIO_LOW, GPO_PUSH_PULL);           // FSMC_NWE IPS350_WR

    afio_init(IPS350_CS_PIN_PARALLEL8, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);       // FSMC_NE4 IPS350_CS
    afio_init(IPS350_RS_PIN_PARALLEL8, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);       // FSMC_A23 IPS350_RS
    afio_init(IPS350_RD_PIN_PARALLEL8, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);       // FSMC_NOE IPS350_RD
    afio_init(IPS350_WR_PIN_PARALLEL8, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);       // FSMC_NWE IPS350_WR

    afio_init(IPS350_D0_PIN_PARALLEL8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D0 IPS350_D0
    afio_init(IPS350_D1_PIN_PARALLEL8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D1 IPS350_D1
    afio_init(IPS350_D2_PIN_PARALLEL8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D2 IPS350_D2
    afio_init(IPS350_D3_PIN_PARALLEL8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D3 IPS350_D3
    afio_init(IPS350_D4_PIN_PARALLEL8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D4 IPS350_D4
    afio_init(IPS350_D5_PIN_PARALLEL8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D5 IPS350_D5
    afio_init(IPS350_D6_PIN_PARALLEL8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D6 IPS350_D6
    afio_init(IPS350_D7_PIN_PARALLEL8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D7 IPS350_D7
    afio_init(IPS350_D8_PIN_PARALLEL8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D0 IPS350_D8
    afio_init(IPS350_D9_PIN_PARALLEL8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D1 IPS350_D9
    afio_init(IPS350_D10_PIN_PARALLEL8, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D2 IPS350_D10
    afio_init(IPS350_D11_PIN_PARALLEL8, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D3 IPS350_D11
    afio_init(IPS350_D12_PIN_PARALLEL8, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D4 IPS350_D12
    afio_init(IPS350_D13_PIN_PARALLEL8, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D5 IPS350_D13
    afio_init(IPS350_D14_PIN_PARALLEL8, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D6 IPS350_D14
    afio_init(IPS350_D15_PIN_PARALLEL8, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);      // FSMC_D7 IPS350_D15

    fsmc_ips350_init();

    IPS350_BL(1);
    IPS350_RST(0);  
    system_delay_ms(5);
    IPS350_RST(1);      
    system_delay_ms(120);

    //************* Start Initial Sequence **********//
    ips350_write_command(0x11);                                                 // Sleep out 
    system_delay_ms(120);                                                       // Delay 120ms 
    //************* Start Initial Sequence **********// 
    ips350_write_command(0xf0);
    ips350_write_data(0xc3);
    ips350_write_command(0xf0);
    ips350_write_data(0x96);
    ips350_write_command(0x36);                                                 // Memory Access Control 
    
    switch(ips350_display_dir)
    {
        case IPS350_PORTAIT:        ips350_write_data(0x48);    break;
        case IPS350_PORTAIT_180:    ips350_write_data(0x88);    break;
        case IPS350_CROSSWISE:      ips350_write_data(0xE8);    break;
        case IPS350_CROSSWISE_180:  ips350_write_data(0x28);    break;
    }

    ips350_write_command(0x3A);
    ips350_write_data(0x05);

    ips350_write_command(0Xe8);
    ips350_write_data(0x40);
    ips350_write_data(0x82);
    ips350_write_data(0x07);
    ips350_write_data(0x18);
    ips350_write_data(0x27);
    ips350_write_data(0x0a);
    ips350_write_data(0xb6);
    ips350_write_data(0x33);

    ips350_write_command(0Xc5);
    ips350_write_data(0x27);

    ips350_write_command(0Xc2);
    ips350_write_data(0xa7);

    ips350_write_command(0Xe0);
    ips350_write_data(0xf0);
    ips350_write_data(0x01);
    ips350_write_data(0x06);
    ips350_write_data(0x0f);
    ips350_write_data(0x12);
    ips350_write_data(0x1d);
    ips350_write_data(0x36);
    ips350_write_data(0x54);
    ips350_write_data(0x44);
    ips350_write_data(0x0c);
    ips350_write_data(0x18);
    ips350_write_data(0x16);
    ips350_write_data(0x13);
    ips350_write_data(0x15);

    ips350_write_command(0Xe1);
    ips350_write_data(0xf0);
    ips350_write_data(0x01);
    ips350_write_data(0x05);
    ips350_write_data(0x0a);
    ips350_write_data(0x0b);
    ips350_write_data(0x07);
    ips350_write_data(0x32);
    ips350_write_data(0x44);
    ips350_write_data(0x44);
    ips350_write_data(0x0c);
    ips350_write_data(0x18);
    ips350_write_data(0x17);
    ips350_write_data(0x13);
    ips350_write_data(0x16);

    ips350_write_command(0Xf0);
    ips350_write_data(0x3c);

    ips350_write_command(0Xf0);
    ips350_write_data(0x69);

    ips350_write_command(0X29);

    ips350_clear();                                                             // 初始化为白屏
    ips350_debug_init();
}
