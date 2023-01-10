/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "user_ips114.h"

static uint16                   ips114_pencolor     = IPS114_DEFAULT_PENCOLOR;
static uint16                   ips114_bgcolor      = IPS114_DEFAULT_BGCOLOR;

static ips114_dir_enum          ips114_display_dir  = IPS114_DEFAULT_DISPLAY_DIR;
static ips114_font_size_enum    ips114_display_font = IPS114_DEFAULT_DISPLAY_FONT;
static uint8                    ips114_x_max        = 240;
static uint8                    ips114_y_max        = 135;

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 SPI 写 8bit 数据
// 参数说明     data            数据
// 返回参数     void
// 使用示例     ips114_write_8bit_data(dat);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define ips114_write_8bit_data(data)    (spi_write_8bit(IPS114_SPI, (data)))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 SPI 写 16bit 数据
// 参数说明     data            数据
// 返回参数     void
// 使用示例     ips114_write_16bit_data(x1 + 52);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define ips114_write_16bit_data(data)   (spi_write_16bit(IPS114_SPI, (data)))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     写命令
// 参数说明     dat             数据
// 返回参数     void
// 使用示例     ips114_write_index(0x2a);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void ips114_write_index (const uint8 dat)
{
    IPS114_DC(0);
    ips114_write_8bit_data(dat);
    IPS114_DC(1);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示区域
// 参数说明     x1              起始x轴坐标
// 参数说明     y1              起始y轴坐标
// 参数说明     x2              结束x轴坐标
// 参数说明     y2              结束y轴坐标
// 返回参数     void
// 使用示例     ips114_set_region(0, 0, ips114_x_max - 1, ips114_y_max - 1);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void ips114_set_region (const int16 x1, const int16 y1, const int16 x2, const int16 y2)
{

    if(ips114_display_dir == IPS114_PORTAIT)
    {
        ips114_write_index(0x2a);                                               // 列地址设置
        ips114_write_16bit_data(x1 + 52);
        ips114_write_16bit_data(x2 + 52);
        ips114_write_index(0x2b);                                               // 行地址设置
        ips114_write_16bit_data(y1 + 40);
        ips114_write_16bit_data(y2 + 40);
        ips114_write_index(0x2c);                                               // 储存器写
    }
    else if(ips114_display_dir == IPS114_PORTAIT_180)
    {
        ips114_write_index(0x2a);                                               // 列地址设置
        ips114_write_16bit_data(x1 + 53);
        ips114_write_16bit_data(x2 + 53);
        ips114_write_index(0x2b);                                               // 行地址设置
        ips114_write_16bit_data(y1 + 40);
        ips114_write_16bit_data(y2 + 40);
        ips114_write_index(0x2c);                                               // 储存器写
    }
    else if(ips114_display_dir == IPS114_CROSSWISE)
    {
        ips114_write_index(0x2a);                                               // 列地址设置
        ips114_write_16bit_data(x1 + 40);
        ips114_write_16bit_data(x2 + 40);
        ips114_write_index(0x2b);                                               // 行地址设置
        ips114_write_16bit_data(y1 + 53);
        ips114_write_16bit_data(y2 + 53);
        ips114_write_index(0x2c);                                               // 储存器写
    }
    else
    {
        ips114_write_index(0x2a);                                               // 列地址设置
        ips114_write_16bit_data(x1 + 40);
        ips114_write_16bit_data(x2 + 40);
        ips114_write_index(0x2b);                                               // 行地址设置
        ips114_write_16bit_data(y1 + 52);
        ips114_write_16bit_data(y2 + 52);
        ips114_write_index(0x2c);                                               // 储存器写
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 画点
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips114_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips114_y_max-1]
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips114_draw_point(0, 0, RGB565_RED);            // 坐标 0,0 画一个红色的点
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void IPS114_DrawPoint (int16 x, int16 y, const uint16 color)
{
    IPS114_CS(0);
    ips114_set_region(x, y, x, y);
    ips114_write_16bit_data(color);
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 画线
// 参数说明     x_start         坐标x方向的起点
// 参数说明     y_start         坐标y方向的起点
// 参数说明     x_end           坐标x方向的终点
// 参数说明     y_end           坐标y方向的终点
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips114_draw_line(0, 0, 10, 10, RGB565_RED);     // 坐标 0,0 到 10,10 画一条红色的线
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void IPS114_DrawLine (int16 x_start, int16 y_start, int16 x_end, int16 y_end, const uint16 color)
{
    int16 x_dir = (x_start < x_end ? 1 : -1);
    int16 y_dir = (y_start < y_end ? 1 : -1);
    float temp_rate = 0;
    float temp_b = 0;

    do
    {
        if(x_start != x_end)
        {
            temp_rate = (float)(y_start - y_end) / (float)(x_start - x_end);
            temp_b = (float)y_start - (float)x_start * temp_rate;
        }
        else
        {
            while(y_start != y_end)
            {
                IPS114_DrawPoint(x_start, y_start, color);
                y_start += y_dir;
            }
            break;
        }
        if(func_abs(y_start - y_end) > func_abs(x_start - x_end))
        {
            while(y_start != y_end)
            {
                IPS114_DrawPoint(x_start, y_start, color);
                y_start += y_dir;
                x_start = (int16)(((float)y_start - temp_b) / temp_rate);
            }
        }
        else
        {
            while(x_start != x_end)
            {
                IPS114_DrawPoint(x_start, y_start, color);
                x_start += x_dir;
                y_start = (int16)((float)x_start * temp_rate + temp_b);
            }
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 显示字符
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips114_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips114_y_max-1]
// 参数说明     dat             需要显示的字符
// 返回参数     void
// 使用示例     ips114_show_char(0, 0, 'x');                    // 坐标 0,0 写一个字符 x
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void IPS114_ShowChar (int16 x, int16 y, const char dat)
{
    uint8 i, j;

    IPS114_CS(0);
    switch(ips114_display_font)
    {
        case IPS114_6X8_FONT:
            for(i = 0; i < 6; i ++)
            {
                ips114_set_region(x + i, y, x + i, y + 8);
                // 减 32 因为是取模是从空格开始取得 空格在 ascii 中序号是 32
                uint8 temp_top = ascii_font_6x8[dat - 32][i];
                for(j = 0; j < 8; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        ips114_write_16bit_data(ips114_pencolor);
                    }
                    else
                    {
                        ips114_write_16bit_data(ips114_bgcolor);
                    }
                    temp_top >>= 1;
                }
            }
            break;
        case IPS114_8X16_FONT:
            for(i = 0; i < 8; i ++)
            {
                ips114_set_region(x + i, y, x + i, y + 15);
                // 减 32 因为是取模是从空格开始取得 空格在 ascii 中序号是 32
                uint8 temp_top = ascii_font_8x16[dat - 32][i];
                uint8 temp_bottom = ascii_font_8x16[dat - 32][i + 8];
                for(j = 0; j < 8; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        ips114_write_16bit_data(ips114_pencolor);
                    }
                    else
                    {
                        ips114_write_16bit_data(ips114_bgcolor);
                    }
                    temp_top >>= 1;
                }
                for(j = 0; j < 8; j ++)
                {
                    if(temp_bottom & 0x01)
                    {
                        ips114_write_16bit_data(ips114_pencolor);
                    }
                    else
                    {
                        ips114_write_16bit_data(ips114_bgcolor);
                    }
                    temp_bottom >>= 1;
                }
            }
            break;
        case IPS114_16X16_FONT:
            // 暂不支持
            break;
    }
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 显示字符串
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips114_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips114_y_max-1]
// 参数说明     dat             需要显示的字符串
// 返回参数     void
// 使用示例     ips114_show_string(0, 0, "seekfree");
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void IPS114_ShowStr (int16 x, int16 y, const char dat[])
{
    uint16 j = 0;
    while(dat[j] != '\0')
    {
        switch(ips114_display_font)
        {
            case IPS114_6X8_FONT:
                ips114_show_char(x + 6 * j, y, dat[j]);
                j ++;
                break;
            case IPS114_8X16_FONT:
                ips114_show_char(x + 8 * j, y, dat[j]);
                j ++;
                break;
            case IPS114_16X16_FONT:
                // 暂不支持
                break;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 显示32位有符号 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips114_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips114_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 int32
// 参数说明     num             需要显示的位数 最高10位  不包含正负号
// 返回参数     void
// 使用示例     ips114_show_int(0, 0, x, 3);                    // x 可以为 int32 int16 int8 类型
// 备注信息     负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void IPS114_ShowInt (int16 x, int16 y, const int32 dat, uint8 num)
{
    zf_assert(num > 0);
    zf_assert(num <= 10);

    int32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];

    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num + 1);

    if(num < 10)
    {
        for(; num > 0; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_int_to_str(data_buffer, dat_temp);
    ips114_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 显示32位无符号 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips114_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips114_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 uint32
// 参数说明     num             需要显示的位数 最高10位  不包含正负号
// 返回参数     void
// 使用示例     ips114_show_uint(0, 0, x, 3);                   // x 可以为 uint32 uint16 uint8 类型
// 备注信息     负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void IPS114_ShowUint (int16 x, int16 y, const uint32 dat, uint8 num)
{
    zf_assert(num > 0);
    zf_assert(num <= 10);

    uint32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];
    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num);

    if(num < 10)
    {
        for(; num > 0; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_uint_to_str(data_buffer, dat_temp);
    ips114_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 显示浮点数 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips114_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips114_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 float 或 double
// 参数说明     num             整数位显示长度   最高8位
// 参数说明     pointnum        小数位显示长度   最高6位
// 返回参数     void
// 使用示例     ips114_show_float(0, 0, x, 2, 3);               // 显示浮点数 整数显示 2 位 小数显示 3 位
// 备注信息     特别注意当发现小数部分显示的值与你写入的值不一样的时候，
//              可能是由于浮点数精度丢失问题导致的，这并不是显示函数的问题，
//              有关问题的详情，请自行百度学习   浮点数精度丢失问题。
//              负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void IPS114_ShowFloat (int16 x, int16 y, const float dat, uint8 num, uint8 pointnum)
{
    zf_assert(num > 0);
    zf_assert(num <= 8);
    zf_assert(pointnum > 0);
    zf_assert(pointnum <= 6);

    float dat_temp = dat;
    float offset = 1.0;
    char data_buffer[17];
    memset(data_buffer, 0, 17);
    memset(data_buffer, ' ', num + pointnum + 2);

    if(num < 10)
    {
        for(; num > 0; num --)
        {
            offset *= 10;
        }
        dat_temp = dat_temp - ((int)dat_temp / (int)offset) * offset;
    }
    func_float_to_str(data_buffer, dat_temp, pointnum);
    ips114_show_string(x, y, data_buffer);
}

/*!
 *
 */
void IPS114_DrawRBox(int16_t x, int16_t y, uint16_t width, uint16_t height)
{
    IPS114_CS(0);
    IPS114_DrawLine(x + 1, y, x + width - 1 ,y, ips114_pencolor);
    IPS114_DrawLine(x, y + 1, x ,y + height - 1, ips114_pencolor);
    IPS114_DrawLine(x + 1, y + height - 1, x + width - 1 ,y + height - 1, ips114_pencolor);
    IPS114_DrawLine(x + width - 1, y + 1, x + width - 1 ,y + height - 1, ips114_pencolor);
    IPS114_CS(1);
}

void IPS114_ClearRBox(int16_t x, int16_t y, uint16_t width, uint16_t height)
{
    IPS114_CS(0);
    IPS114_DrawLine(x + 1, y, x + width - 1 ,y, ips114_bgcolor);
    IPS114_DrawLine(x, y + 1, x ,y + height - 1, ips114_bgcolor);
    IPS114_DrawLine(x + 1, y + height - 1, x + width - 1 ,y + height - 1, ips114_bgcolor);
    IPS114_DrawLine(x + width - 1, y + 1, x + width - 1 ,y + height - 1, ips114_bgcolor);
    IPS114_CS(1);
}