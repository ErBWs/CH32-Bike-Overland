/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "ips096.h"

static uint16_t                  ips096_pencolor     = IPS096_DEFAULT_PENCOLOR;
static uint16_t                 ips096_bgcolor      = IPS096_DEFAULT_BGCOLOR;

static ips096_dir_enum          ips096_display_dir  = IPS096_DEFAULT_DISPLAY_DIR;
static ips096_font_size_enum    ips096_display_font = IPS096_DEFAULT_DISPLAY_FONT;
static uint8                    ips096_x_max        = 160;
static uint8                    ips096_y_max        = 80;

#define ips096_write_8bit_data(data)    (spi_write_8bit(IPS096_SPI, (data)))
#define ips096_write_16bit_data(data)   (spi_write_16bit(IPS096_SPI, (data)))
static void ips096_write_index (const uint8 dat)
{
    IPS096_DC(0);
    ips096_write_8bit_data(dat);
    IPS096_DC(1);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示区域
// 参数说明     x1              起始x轴坐标
// 参数说明     y1              起始y轴坐标
// 参数说明     x2              结束x轴坐标
// 参数说明     y2              结束y轴坐标
// 返回参数     void
// 使用示例     ips096_set_region(0, 0, ips096_x_max - 1, ips096_y_max - 1);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void ips096_set_region (const uint16 x1, const uint16 y1, const uint16 x2, const uint16 y2)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    // 检查一下你的显示调用的函数 自己计算一下哪里超过了屏幕显示范围
    zf_assert(x1 < ips096_x_max);
    zf_assert(y1 < ips096_y_max);
    zf_assert(x2 < ips096_x_max);
    zf_assert(y2 < ips096_y_max);

    if(ips096_display_dir == IPS096_PORTRAIT)
    {
        ips096_write_index(0x2a);                                               // 列地址设置
        ips096_write_16bit_data(x1 + 24);
        ips096_write_16bit_data(x2 + 24);
        ips096_write_index(0x2b);                                               // 行地址设置
        ips096_write_16bit_data(y1);
        ips096_write_16bit_data(y2);
        ips096_write_index(0x2c);                                               // 储存器写
    }
    else if(ips096_display_dir == IPS096_PORTRAIT_180)
    {
        ips096_write_index(0x2a);                                               // 列地址设置
        ips096_write_16bit_data(x1 + 24);
        ips096_write_16bit_data(x2 + 24);
        ips096_write_index(0x2b);                                               // 行地址设置
        ips096_write_16bit_data(y1);
        ips096_write_16bit_data(y2);
        ips096_write_index(0x2c);                                               // 储存器写
    }
    else if(ips096_display_dir == IPS096_CROSSWISE)
    {
        ips096_write_index(0x2a);                                               // 列地址设置
        ips096_write_16bit_data(x1);
        ips096_write_16bit_data(x2);
        ips096_write_index(0x2b);                                               // 行地址设置
        ips096_write_16bit_data(y1 + 24);
        ips096_write_16bit_data(y2 + 24);
        ips096_write_index(0x2c);                                               // 储存器写
    }
    else
    {
        ips096_write_index(0x2a);                                               // 列地址设置
        ips096_write_16bit_data(x1);
        ips096_write_16bit_data(x2);
        ips096_write_index(0x2b);                                               // 行地址设置
        ips096_write_16bit_data(y1 + 24);
        ips096_write_16bit_data(y2 + 24);
        ips096_write_index(0x2c);                                               // 储存器写
    }
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS096 清屏函数
// 参数说明     void
// 返回参数     void
// 使用示例     ips096_clear();
// 备注信息     将屏幕清空成背景颜色
//-------------------------------------------------------------------------------------------------------------------
void ips096_clear (void)
{
    uint32 i = ips096_x_max * ips096_y_max;

    IPS096_CS(0);
    ips096_set_region(0, 0, ips096_x_max - 1, ips096_y_max - 1);
    for( ; i > 0; i --)
    {
        ips096_write_16bit_data(ips096_bgcolor);
    }
    IPS096_CS(1);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS096 屏幕填充函数
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips096_full(RGB565_BLACK);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void ips096_full (const uint16 color)
{
    uint32 i = ips096_x_max * ips096_y_max;

    IPS096_CS(0);
    ips096_set_region(0, 0, ips096_x_max - 1, ips096_y_max - 1);
    for( ; i > 0; i --)
    {
        ips096_write_16bit_data(color);
    }
    IPS096_CS(1);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示方向
// 参数说明     dir             显示方向  参照 zf_device_ips096.h 内 ips096_dir_enum 枚举体定义
// 返回参数     void
// 使用示例     ips096_set_dir(IPS096_CROSSWISE);
// 备注信息     这个函数只有在初始化屏幕之前调用才生效
//-------------------------------------------------------------------------------------------------------------------
void ips096_set_dir (ips096_dir_enum dir)
{
    ips096_display_dir = dir;
    if(dir < 2)
    {
        ips096_x_max = 135;
        ips096_y_max = 240;
    }
    else
    {
        ips096_x_max = 240;
        ips096_y_max = 135;
    }
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示字体
// 参数说明     dir             显示方向  参照 zf_device_ips096.h 内 ips096_font_size_enum 枚举体定义
// 返回参数     void
// 使用示例     ips096_set_font(IPS096_8x16_FONT);
// 备注信息     字体可以随时自由设置 设置后生效 后续显示就是新的字体大小
//-------------------------------------------------------------------------------------------------------------------
void ips096_set_font (ips096_font_size_enum font)
{
    ips096_display_font = font;
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示颜色
// 参数说明     pen             颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 参数说明     bgcolor         颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips096_set_color(RGB565_WHITE, RGB565_BLACK);
// 备注信息     字体颜色和背景颜色也可以随时自由设置 设置后生效
//-------------------------------------------------------------------------------------------------------------------
void ips096_set_color (const uint16 pen, const uint16 bgcolor)
{
    ips096_pencolor = pen;
    ips096_bgcolor = bgcolor;
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS096 画点
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips096_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips096_y_max-1]
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips096_draw_point(0, 0, RGB565_RED);            // 坐标 0,0 画一个红色的点
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void ips096_draw_point (uint16 x, uint16 y, const uint16 color)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);

    IPS096_CS(0);
    ips096_set_region(x, y, x, y);
    ips096_write_16bit_data(color);
    IPS096_CS(1);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS096 画线
// 参数说明     x_start         坐标x方向的起点
// 参数说明     y_start         坐标y方向的起点
// 参数说明     x_end           坐标x方向的终点
// 参数说明     y_end           坐标y方向的终点
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips096_draw_line(0, 0, 10, 10, RGB565_RED);     // 坐标 0,0 到 10,10 画一条红色的线
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void ips096_draw_line (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x_start < ips096_x_max);
    zf_assert(y_start < ips096_y_max);
    zf_assert(x_end < ips096_x_max);
    zf_assert(y_end < ips096_y_max);

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
                ips096_draw_point(x_start, y_start, color);
                y_start += y_dir;
            }
            break;
        }
        if(func_abs(y_start - y_end) > func_abs(x_start - x_end))
        {
            while(y_start != y_end)
            {
                ips096_draw_point(x_start, y_start, color);
                y_start += y_dir;
                x_start = (int16)(((float)y_start - temp_b) / temp_rate);
            }
        }
        else
        {
            while(x_start != x_end)
            {
                ips096_draw_point(x_start, y_start, color);
                x_start += x_dir;
                y_start = (int16)((float)x_start * temp_rate + temp_b);
            }
        }
    }while(0);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS096 显示字符
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips096_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips096_y_max-1]
// 参数说明     dat             需要显示的字符
// 返回参数     void
// 使用示例     ips096_show_char(0, 0, 'x');                    // 坐标 0,0 写一个字符 x
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_char (uint16 x, uint16 y, const char dat)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);

    uint8 i, j;

    IPS096_CS(0);
    switch(ips096_display_font)
    {
    case IPS096_6X8_FONT:
        for(i = 0; i < 6; i ++)
        {
            ips096_set_region(x + i, y, x + i, y + 8);
            // 减 32 因为是取模是从空格开始取得 空格在 ascii 中序号是 32
            uint8 temp_top = ascii_font_6x8[dat - 32][i];
            for(j = 0; j < 8; j ++)
            {
                if(temp_top & 0x01)
                {
                    ips096_write_16bit_data(ips096_pencolor);
                }
                else
                {
                    ips096_write_16bit_data(ips096_bgcolor);
                }
                temp_top >>= 1;
            }
        }
        break;
    case IPS096_8X16_FONT:
        for(i = 0; i < 8; i ++)
        {
            ips096_set_region(x + i, y, x + i, y + 15);
            // 减 32 因为是取模是从空格开始取得 空格在 ascii 中序号是 32
            uint8 temp_top = ascii_font_8x16[dat - 32][i];
            uint8 temp_bottom = ascii_font_8x16[dat - 32][i + 8];
            for(j = 0; j < 8; j ++)
            {
                if(temp_top & 0x01)
                {
                    ips096_write_16bit_data(ips096_pencolor);
                }
                else
                {
                    ips096_write_16bit_data(ips096_bgcolor);
                }
                temp_top >>= 1;
            }
            for(j = 0; j < 8; j ++)
            {
                if(temp_bottom & 0x01)
                {
                    ips096_write_16bit_data(ips096_pencolor);
                }
                else
                {
                    ips096_write_16bit_data(ips096_bgcolor);
                }
                temp_bottom >>= 1;
            }
        }
        break;
    }
    IPS096_CS(1);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS096 显示字符串
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips096_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips096_y_max-1]
// 参数说明     dat             需要显示的字符串
// 返回参数     void
// 使用示例     ips096_show_string(0, 0, "seekfree");
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_string (uint16 x, uint16 y, const char dat[])
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);

    uint16 j = 0;
    while(dat[j] != '\0')
    {
        switch(ips096_display_font)
        {
        case IPS096_6X8_FONT:
            ips096_show_char(x + 6 * j, y, dat[j]);
            j ++;
            break;
        case IPS096_8X16_FONT:
            ips096_show_char(x + 8 * j, y, dat[j]);
            j ++;
            break;
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS096 显示32位有符号 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips096_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips096_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 int32
// 参数说明     num             需要显示的位数 最高10位  不包含正负号
// 返回参数     void
// 使用示例     ips096_show_int(0, 0, x, 3);                    // x 可以为 int32 int16 int8 类型
// 备注信息     负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_int (uint16 x, uint16 y, const int32 dat, uint8 num)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);
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
    ips096_show_string(x, y, (const char *)&data_buffer);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS096 显示32位无符号 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips096_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips096_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 uint32
// 参数说明     num             需要显示的位数 最高10位  不包含正负号
// 返回参数     void
// 使用示例     ips096_show_uint(0, 0, x, 3);                   // x 可以为 uint32 uint16 uint8 类型
// 备注信息     负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_uint (uint16 x, uint16 y, const uint32 dat, uint8 num)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);
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
    ips096_show_string(x, y, (const char *)&data_buffer);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS096 显示浮点数 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips096_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips096_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 float 或 double
// 参数说明     num             整数位显示长度   最高10位
// 参数说明     pointnum        小数位显示长度   最高6位
// 返回参数     void
// 使用示例     ips096_show_float(0, 0, x, 2, 3);               // 显示浮点数 整数显示 2 位 小数显示 3 位
// 备注信息     特别注意当发现小数部分显示的值与你写入的值不一样的时候，
//              可能是由于浮点数精度丢失问题导致的，这并不是显示函数的问题，
//              有关问题的详情，请自行百度学习   浮点数精度丢失问题。
//              负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_float (uint16 x, uint16 y, const float dat, uint8 num, uint8 pointnum)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);
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
    ips096_show_string(x, y, data_buffer);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS096 显示二值图像 数据每八个点组成一个字节数据
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips096_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips096_y_max-1]
// 参数说明     *image          图像数组指针
// 参数说明     width           图像实际宽度
// 参数说明     height          图像实际高度
// 参数说明     dis_width       图像显示宽度 参数范围 [0, ips096_x_max]
// 参数说明     dis_height      图像显示高度 参数范围 [0, ips096_y_max]
// 返回参数     void
// 使用示例     ips096_show_binary_image(0, 0, ov7725_image_binary[0], OV7725_W, OV7725_H, OV7725_W, OV7725_H);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_binary_image (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);
    zf_assert(image != NULL);

    uint32 i = 0, j = 0;
    uint8 temp = 0;
    uint32 width_index = 0, height_index = 0;

    IPS096_CS(0);
    ips096_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // 设置显示区域

    for(j = 0; j < dis_height; j ++)
    {
        height_index = j * height / dis_height;
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            temp = *(image + height_index * width / 8 + width_index / 8);       // 读取像素点
            if(0x80 & (temp << (width_index % 8)))
            {
                ips096_write_16bit_data(RGB565_WHITE);
            }
            else
            {
                ips096_write_16bit_data(RGB565_BLACK);
            }
        }
    }
    IPS096_CS(1);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS096 显示 8bit 灰度图像 带二值化阈值
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips096_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips096_y_max-1]
// 参数说明     *image          图像数组指针
// 参数说明     width           图像实际宽度
// 参数说明     height          图像实际高度
// 参数说明     dis_width       图像显示宽度 参数范围 [0, ips096_x_max]
// 参数说明     dis_height      图像显示高度 参数范围 [0, ips096_y_max]
// 参数说明     threshold       二值化显示阈值 0-不开启二值化
// 返回参数     void
// 使用示例     ips096_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_gray_image (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);
    zf_assert(image != NULL);

    uint32 i = 0, j = 0;
    uint16 color = 0,temp = 0;
    uint32 width_index = 0, height_index = 0;

    IPS096_CS(0);
    ips096_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // 设置显示区域

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
                ips096_write_16bit_data(color);
            }
            else if(temp < threshold)
            {
                ips096_write_16bit_data(RGB565_BLACK);
            }
            else
            {
                ips096_write_16bit_data(RGB565_WHITE);
            }
        }
    }
    IPS096_CS(1);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS096 显示波形
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips096_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips096_y_max-1]
// 参数说明     *wave           波形数组指针
// 参数说明     width           波形实际宽度
// 参数说明     value_max       波形实际最大值
// 参数说明     dis_width       波形显示宽度 参数范围 [0, ips096_x_max]
// 参数说明     dis_value_max   波形显示最大值 参数范围 [0, ips096_y_max]
// 返回参数     void
// 使用示例     ips096_show_wave(56,35,data,128,64,128,64);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_wave (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);
    zf_assert(wave != NULL);

    uint32 i = 0, j = 0;
    uint32 width_index = 0, value_max_index = 0;

    IPS096_CS(0);
    ips096_set_region(x, y, x + dis_width - 1, y + dis_value_max - 1);          // 设置显示区域
    for(i = 0; i < dis_value_max; i ++)
    {
        for(j = 0; j < dis_width; j ++)
        {
            ips096_write_16bit_data(ips096_bgcolor);
        }
    }
    IPS096_CS(1);

    for(i = 0; i < dis_width; i ++)
    {
        width_index = i * width / dis_width;
        value_max_index = *(wave + width_index) * (dis_value_max - 1) / value_max;
        ips096_draw_point(i + x, (dis_value_max - 1) - value_max_index + y, ips096_pencolor);
    }
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     1.14寸 IPS 液晶显示DEBUG信息初始化
// 参数说明     void
// 返回参数     void
// 使用示例     ips096_debug_init();
// 备注信息     内部使用
//-------------------------------------------------------------------------------------------------------------------
static void ips096_debug_init (void)
{
    debug_output_struct info;
    debug_output_struct_init(&info);

    info.type_index = 1;
    info.display_x_max = ips096_x_max;
    info.display_y_max = ips096_y_max;

    switch(ips096_display_font)
    {
    case IPS096_6X8_FONT:
        info.font_x_size = 6;
        info.font_y_size = 8;
        break;
    case IPS096_8X16_FONT:
        info.font_x_size = 8;
        info.font_y_size = 16;
        break;
    }
    info.output_screen = ips096_show_string;
    info.output_screen_clear = ips096_clear;

    debug_output_init(&info);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     1.14寸 IPS液晶初始化
// 参数说明     void
// 返回参数     void
// 使用示例     ips096_init();
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void ips096_init (void)
{
#if IPS096_USE_SOFT_SPI
    soft_spi_init(&ips096_spi, 0, IPS096_SOFT_SPI_DELAY, IPS096_SCL_PIN, IPS096_SDA_PIN, SOFT_SPI_PIN_NULL, SOFT_SPI_PIN_NULL);
#else
    spi_init(IPS096_SPI, SPI_MODE0, IPS096_SPI_SPEED, IPS096_SCL_PIN, IPS096_SDA_PIN, SPI_MISO_NULL, SPI_CS_NULL);
#endif

    gpio_init(IPS096_DC_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(IPS096_RST_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(IPS096_CS_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(IPS096_BLK_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    ips096_set_dir(ips096_display_dir);
    ips096_set_color(ips096_pencolor, ips096_bgcolor);
    ips096_debug_init();

    IPS096_RST(0);
    system_delay_ms(200);

    IPS096_RST(1);
    system_delay_ms(100);

    ips096_write_index(0x11);//Sleep exit 
    system_delay_ms(120);                //Delay 120ms
    ips096_write_index(0xB1);
    ips096_write_8bit_data(0x05);
    ips096_write_8bit_data(0x3C);
    ips096_write_8bit_data(0x3C);

    ips096_write_index(0xB2);
    ips096_write_8bit_data(0x05);
    ips096_write_8bit_data(0x3C);
    ips096_write_8bit_data(0x3C);

    ips096_write_index(0xB3);
    ips096_write_8bit_data(0x05);
    ips096_write_8bit_data(0x3C);
    ips096_write_8bit_data(0x3C);
    ips096_write_8bit_data(0x05);
    ips096_write_8bit_data(0x3C);
    ips096_write_8bit_data(0x3C);

    ips096_write_index(0xB4);     //Dot inversion
    ips096_write_8bit_data(0x03);

    ips096_write_index(0xC0);
    ips096_write_8bit_data(0x0E);
    ips096_write_8bit_data(0x0E);
    ips096_write_8bit_data(0x04);

    ips096_write_index(0xC1);
    ips096_write_8bit_data(0xC5);

    ips096_write_index(0xC2);
    ips096_write_8bit_data(0x0d);
    ips096_write_8bit_data(0x00);

    ips096_write_index(0xC3);
    ips096_write_8bit_data(0x8D);
    ips096_write_8bit_data(0x2A);

    ips096_write_index(0xC4);
    ips096_write_8bit_data(0x8D);
    ips096_write_8bit_data(0xEE);

    ips096_write_index(0xC5);     //VCOM
    ips096_write_8bit_data(0x06); //1D  .06


    ips096_write_index(0x36);     //MX, MY, RGB mode
    if(ips096_display_dir == 0)
        ips096_write_8bit_data(0x08);
    else if(ips096_display_dir == 1)
        ips096_write_8bit_data(0xC8);
    else if(ips096_display_dir == 2)
        ips096_write_8bit_data(0x78);
    else
        ips096_write_8bit_data(0xA8);

    ips096_write_index(0x3A);
    ips096_write_8bit_data(0x55);

    ips096_write_index(0xE0);
    ips096_write_8bit_data(0x0b);
    ips096_write_8bit_data(0x17);
    ips096_write_8bit_data(0x0a);
    ips096_write_8bit_data(0x0d);
    ips096_write_8bit_data(0x1a);
    ips096_write_8bit_data(0x19);
    ips096_write_8bit_data(0x16);
    ips096_write_8bit_data(0x1d);
    ips096_write_8bit_data(0x21);
    ips096_write_8bit_data(0x26);
    ips096_write_8bit_data(0x37);
    ips096_write_8bit_data(0x3c);
    ips096_write_8bit_data(0x00);
    ips096_write_8bit_data(0x09);
    ips096_write_8bit_data(0x05);
    ips096_write_8bit_data(0x10);

    ips096_write_index(0xE1);
    ips096_write_8bit_data(0x0c);
    ips096_write_8bit_data(0x19);
    ips096_write_8bit_data(0x09);
    ips096_write_8bit_data(0x0d);
    ips096_write_8bit_data(0x1b);
    ips096_write_8bit_data(0x19);
    ips096_write_8bit_data(0x15);
    ips096_write_8bit_data(0x1d);
    ips096_write_8bit_data(0x21);
    ips096_write_8bit_data(0x26);
    ips096_write_8bit_data(0x39);
    ips096_write_8bit_data(0x3E);
    ips096_write_8bit_data(0x00);
    ips096_write_8bit_data(0x09);
    ips096_write_8bit_data(0x05);
    ips096_write_8bit_data(0x10);

    system_delay_ms(120);
    ips096_write_index(0x29);     //Display on

    ips096_clear();
}