/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "user_ips114.h"

uint16_t IPS114_penColor = IPS114_DEFAULT_PENCOLOR;
uint16_t IPS114_backgroundColor = IPS114_DEFAULT_BGCOLOR;
uint8_t IPS114_colorSwap = 0;

static ips114_dir_enum ips114_display_dir = IPS114_DEFAULT_DISPLAY_DIR;
static ips114_font_size_enum ips114_display_font = IPS114_DEFAULT_DISPLAY_FONT;
static uint8_t ips114_x_max = 240;
static uint8_t ips114_y_max = 135;
static uint8_t IPS114_colorMode = NORMAL;
static uint16_t IPS114_buffer[135][240] = {0};


#define ips114_write_8bit_data(data)    (spi_write_8bit(IPS114_SPI, (data)))
#define ips114_write_16bit_data(data)   (spi_write_16bit(IPS114_SPI, (data)))

static void ips114_write_index(const uint8 dat)
{
    IPS114_DC(0);
    ips114_write_8bit_data(dat);
    IPS114_DC(1);
}

/*!
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 */
static void IPS114_SetRegion(const int16 x1, const int16 y1, const int16 x2, const int16 y2)
{
    if (ips114_display_dir == IPS114_CROSSWISE)
    {
        ips114_write_index(0x2a);                                               // 列地址设置
        ips114_write_16bit_data(x1 + 40);
        ips114_write_16bit_data(x2 + 40);
        ips114_write_index(0x2b);                                               // 行地址设置
        ips114_write_16bit_data(y1 + 53);
        ips114_write_16bit_data(y2 + 53);
        ips114_write_index(0x2c);                                               // 储存器写
    } else if (ips114_display_dir == IPS114_CROSSWISE_180)
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

void IPS114_SetDrawColor(IPS114_ColorMode_e mode)
{
    IPS114_colorMode = mode;
}

/*!
 * @brief   Send buffer to ips114
 *
 * @param   void
 * @return  void
 */
void IPS114_SendBuffer()
{
    IPS114_CS(0);
    IPS114_SetRegion(0, 0, 239, 134);
    for (int i = 0; i < 135; i++)
    {
        for (int j = 0; j < 240; j++)
        {
            ips114_write_16bit_data(IPS114_buffer[i][j]);
        }
    }
    IPS114_CS(1);
}

/*!
 * @brief   Clear buffer array
 *
 * @param   void
 * @return  void
 *
 * @note    Use black background color can easily clear the buffer by memset,
 *          but other color cannot and on board flash is not enough for another buffer
 *          to use memcpy, so using color other than black will slower this function.
 */
void IPS114_ClearBuffer()
{
    if (IPS114_backgroundColor == RGB565_BLACK)
    {
        memset(IPS114_buffer, 0, 135 * 240 * sizeof(uint16_t));
    } else
    {
        for (int i = 0; i < 135; i++)
        {
            for (int j = 0; j < 240; j++)
            {
                IPS114_buffer[i][j] = IPS114_backgroundColor;
            }
        }
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
void IPS114_DrawPoint(int16 x, int16 y, const uint16 color)
{
    if (x < 240 && y < 135 && x >= 0 && y >= 0)
    {
        if (IPS114_colorMode == XOR)
        {
            if (IPS114_buffer[y][x] == color)
                IPS114_buffer[y][x] = IPS114_backgroundColor;
            else
                IPS114_buffer[y][x] = color;
        } else
            IPS114_buffer[y][x] = color;
    }
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
void IPS114_DrawLine(int16 x_start, int16 y_start, int16 x_end, int16 y_end, const uint16 color)
{
    int16 x_dir = (x_start < x_end ? 1 : -1);
    int16 y_dir = (y_start < y_end ? 1 : -1);
    float temp_rate = 0;
    float temp_b = 0;

    do
    {
        if (x_start != x_end)
        {
            temp_rate = (float) (y_start - y_end) / (float) (x_start - x_end);
            temp_b = (float) y_start - (float) x_start * temp_rate;
        } else
        {
            while (y_start != y_end)
            {
                IPS114_DrawPoint(x_start, y_start, color);
                y_start += y_dir;
            }
            break;
        }
        if (func_abs(y_start - y_end) > func_abs(x_start - x_end))
        {
            while (y_start != y_end)
            {
                IPS114_DrawPoint(x_start, y_start, color);
                y_start += y_dir;
                x_start = (int16) (((float) y_start - temp_b) / temp_rate);
            }
        } else
        {
            while (x_start != x_end)
            {
                IPS114_DrawPoint(x_start, y_start, color);
                x_start += x_dir;
                y_start = (int16) ((float) x_start * temp_rate + temp_b);
            }
        }
    } while (0);
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
void IPS114_ShowChar(int16 x, int16 y, const char dat)
{
    uint8 i, j;
    switch (ips114_display_font)
    {
        case IPS114_6X8_FONT:
            for (i = 0; i < 6; i++)
            {
                // 减 32 因为是取模是从空格开始取得 空格在 ascii 中序号是 32
                uint8 temp_top = ascii_font_6x8[dat - 32][i];
                for (j = 0; j < 8; j++)
                {
                    if (temp_top & 0x01)
                    {
                        IPS114_DrawPoint(x + i, y + j ,IPS114_penColor);
                    }
                    temp_top >>= 1;
                }
            }
            break;
        case IPS114_8X16_FONT:
            for (i = 0; i < 8; i++)
            {
                // 减 32 因为是取模是从空格开始取得 空格在 ascii 中序号是 32
                uint8 temp_top = ascii_font_8x16[dat - 32][i];
                uint8 temp_bottom = ascii_font_8x16[dat - 32][i + 8];
                for (j = 0; j < 8; j++)
                {
                    if (temp_top & 0x01)
                    {
                        IPS114_DrawPoint(x + i, y + j ,IPS114_penColor);
                    }
                    temp_top >>= 1;
                }
                for (j = 0; j < 8; j++)
                {
                    if (temp_bottom & 0x01)
                    {
                        IPS114_DrawPoint(x + i, y + j + 8,IPS114_penColor);
                    }
                    temp_bottom >>= 1;
                }
            }
            break;
        default:
            break;
    }
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
void IPS114_ShowStr(int16 x, int16 y, const char dat[])
{
    uint16 j = 0;
    while (dat[j] != '\0')
    {
        switch (ips114_display_font)
        {
            case IPS114_6X8_FONT:
                IPS114_ShowChar(x + 6 * j, y, dat[j]);
                j++;
                break;
            case IPS114_8X16_FONT:
                IPS114_ShowChar(x + 8 * j, y, dat[j]);
                j++;
                break;
            default:
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
void IPS114_ShowInt(int16 x, int16 y, const int32 dat, uint8 num)
{
    zf_assert(num > 0);
    zf_assert(num <= 10);

    int32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];

    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num + 1);

    if (num < 10)
    {
        for (; num > 0; num--)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_int_to_str(data_buffer, dat_temp);
    IPS114_ShowStr(x, y, (const char *) &data_buffer);
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
void IPS114_ShowUint(int16 x, int16 y, const uint32 dat, uint8 num)
{
    zf_assert(num > 0);
    zf_assert(num <= 10);

    uint32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];
    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num);

    if (num < 10)
    {
        for (; num > 0; num--)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_uint_to_str(data_buffer, dat_temp);
    IPS114_ShowStr(x, y, (const char *) &data_buffer);
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
void IPS114_ShowFloat(int16 x, int16 y, const float dat, uint8 num, uint8 pointnum)
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

    if (num < 10)
    {
        for (; num > 0; num--)
        {
            offset *= 10;
        }
        dat_temp = dat_temp - ((int) dat_temp / (int) offset) * offset;
    }
    func_float_to_str(data_buffer, dat_temp, pointnum);
    IPS114_ShowStr(x, y, data_buffer);
}


bool reversedColor = false;

void IPS114_ModifyColor()
{
    if (reversedColor)
    {
        IPS114_penColor = IPS114_DEFAULT_BGCOLOR;
        IPS114_backgroundColor = IPS114_DEFAULT_PENCOLOR;
    } else
    {
        IPS114_penColor = IPS114_DEFAULT_PENCOLOR;
        IPS114_backgroundColor = IPS114_DEFAULT_BGCOLOR;
    }
}


/*!
 * @brief   Draw circle / disc with 5 choices of section
 *
 * @param   x           Center x of the circle
 * @param   y           Center y of the circle
 * @param   r           Radius
 * @param   color       Color
 * @param   section     See definition in user_ips114.h
 * @return  void
 */
void IPS114_DrawCircle(int16_t x, int16_t y, uint16_t r, const uint16_t color, uint8_t section)
{
    // y = kx, k = 1
    uint16_t x0 = (uint16_t) (r * cos(0.01745 * 45));
    uint16_t fx;

    // x^2 + y^2 = r^2, y->x / x->y
    for (int i = -x0 + 1; i < 0; ++i)
    {
        fx = (uint16_t) sqrt(pow(r, 2) - pow(i, 2));
        if (section & CIRCLE_UPPER_RIGHT)
        {
            IPS114_DrawPoint(x - i, y - fx, color);
            IPS114_DrawPoint(x + fx, y + i, color);
        }
        if (section & CIRCLE_UPPER_LEFT)
        {
            IPS114_DrawPoint(x + i, y - fx, color);
            IPS114_DrawPoint(x - fx, y + i, color);
        }
        if (section & CIRCLE_LOWER_LEFT)
        {
            IPS114_DrawPoint(x + i, y + fx, color);
            IPS114_DrawPoint(x - fx, y - i, color);
        }
        if (section & CIRCLE_LOWER_RIGHT)
        {
            IPS114_DrawPoint(x - i, y + fx, color);
            IPS114_DrawPoint(x + fx, y - i, color);
        }
    }

    // Add support for XOR color mode
    fx = (uint16_t) sqrt(pow(r, 2) - pow(x0, 2));
    if (section & CIRCLE_UPPER_RIGHT)
    {
        if (r > 1)
        {
            IPS114_DrawPoint(x + r, y, color);
            IPS114_DrawPoint(x, y - r, color);
        }
        if (x0 == fx)
            IPS114_DrawPoint(x + x0, y - x0, color);
        else
        {
            IPS114_DrawPoint(x + x0, y - fx, color);
            IPS114_DrawPoint(x + fx, y - x0, color);
        }
    }
    if (section & CIRCLE_UPPER_LEFT)
    {
        if (r > 1)
        {
            IPS114_DrawPoint(x - r, y, color);
            IPS114_DrawPoint(x, y - r, color);
        }
        if (x0 == fx)
            IPS114_DrawPoint(x - x0, y - x0, color);
        else
        {
            IPS114_DrawPoint(x - x0, y - fx, color);
            IPS114_DrawPoint(x - fx, y - x0, color);
        }
    }
    if (section & CIRCLE_LOWER_LEFT)
    {
        if (r > 1)
        {
            IPS114_DrawPoint(x - r, y, color);
            IPS114_DrawPoint(x, y + r, color);
        }
        if (x0 == fx)
            IPS114_DrawPoint(x - x0, y + x0, color);
        else
        {
            IPS114_DrawPoint(x - x0, y + fx, color);
            IPS114_DrawPoint(x - fx, y + x0, color);
        }
    }
    if (section & CIRCLE_LOWER_RIGHT)
    {
        if (r > 1)
        {
            IPS114_DrawPoint(x + r, y, color);
            IPS114_DrawPoint(x, y + r, color);
        }
        if (x0 == fx)
            IPS114_DrawPoint(x + x0, y + x0, color);
        else
        {
            IPS114_DrawPoint(x + x0, y + fx, color);
            IPS114_DrawPoint(x + fx, y + x0, color);
        }
    }
    if (section == CIRCLE_DRAW_ALL)
    {
        IPS114_DrawPoint(x + r, y, color);
        IPS114_DrawPoint(x - r, y, color);
        IPS114_DrawPoint(x, y - r, color);
        IPS114_DrawPoint(x, y + r, color);
    }
}
void IPS114_DrawDisc(int16_t x, int16_t y, uint16_t r, const uint16_t color, uint8_t section)
{
    // y = kx, k = 1
    uint16_t x0 = (uint16_t) (r * cos(0.01745 * 45));
    uint16_t fx;

    // x^2 + y^2 = r^2, y->x / x->y
    for (int i = -x0 + 1; i < 0; ++i)
    {
        fx = (uint16_t) sqrt(pow(r, 2) - pow(i, 2));
        if (section & CIRCLE_UPPER_RIGHT)
        {
            IPS114_DrawLine(x - i, y - fx, x - i, y + i, color);
            IPS114_DrawLine(x + fx, y + i, x - i, y + i, color);
        }
        if (section & CIRCLE_UPPER_LEFT)
        {
            IPS114_DrawLine(x + i, y - fx, x + i, y + i, color);
            IPS114_DrawLine(x - fx, y + i, x + i, y + i, color);
        }
        if (section & CIRCLE_LOWER_LEFT)
        {
            IPS114_DrawLine(x + i, y + fx, x + i, y - i, color);
            IPS114_DrawLine(x - fx, y - i, x + i, y - i, color);
        }
        if (section & CIRCLE_LOWER_RIGHT)
        {
            IPS114_DrawLine(x - i, y + fx, x - i, y - i, color);
            IPS114_DrawLine(x + fx, y - i, x - i, y - i, color);
        }
    }

    // Add support for XOR color mode
    IPS114_DrawPoint(x, y, color);
    if (r != 2)
        IPS114_DrawPoint(x, y, color);

    fx = (uint16_t) sqrt(pow(r, 2) - pow(x0, 2));
    if (section & CIRCLE_UPPER_RIGHT)
    {
        if (r > 1)
        {
            IPS114_DrawLine(x + r, y, x, y, color);
            IPS114_DrawLine(x, y - r, x, y, color);
        }
        if (r > 2)
            IPS114_DrawLine(x, y, x + x0, y - x0, color);
        if (x0 == fx)
            IPS114_DrawPoint(x + x0, y - x0, color);
        else
        {
            IPS114_DrawPoint(x + x0, y - fx, color);
            IPS114_DrawPoint(x + fx, y - x0, color);
            IPS114_DrawPoint(x + x0, y - x0, color);
        }
    }
    if (section & CIRCLE_UPPER_LEFT)
    {
        if (r > 1)
        {
            IPS114_DrawLine(x - r, y, x, y, color);
            IPS114_DrawLine(x, y - r, x, y, color);
        }
        if (r > 2)
            IPS114_DrawLine(x, y, x - x0, y - x0, color);
        if (x0 == fx)
            IPS114_DrawPoint(x - x0, y - x0, color);
        else
        {
            IPS114_DrawPoint(x - x0, y - fx, color);
            IPS114_DrawPoint(x - fx, y - x0, color);
            IPS114_DrawPoint(x - x0, y - x0, color);
        }
    }
    if (section & CIRCLE_LOWER_LEFT)
    {
        if (r > 1)
        {
            IPS114_DrawLine(x - r, y, x, y, color);
            IPS114_DrawLine(x, y + r, x, y, color);
        }
        if (r > 2)
            IPS114_DrawLine(x, y, x - x0, y + x0, color);
        if (x0 == fx)
            IPS114_DrawPoint(x - x0, y + x0, color);
        else
        {
            IPS114_DrawPoint(x - x0, y + fx, color);
            IPS114_DrawPoint(x - fx, y + x0, color);
            IPS114_DrawPoint(x - x0, y + x0, color);
        }
    }
    if (section & CIRCLE_LOWER_RIGHT)
    {
        if (r > 1)
        {
            IPS114_DrawLine(x + r, y, x, y, color);
            IPS114_DrawLine(x, y + r, x, y, color);
        }
        if (r > 2)
            IPS114_DrawLine(x, y, x + x0, y + x0, color);
        if (x0 == fx)
            IPS114_DrawPoint(x + x0, y + x0, color);
        else
        {
            IPS114_DrawPoint(x + x0, y + fx, color);
            IPS114_DrawPoint(x + fx, y + x0, color);
            IPS114_DrawPoint(x + x0, y + x0, color);
        }
    }
    if (section == CIRCLE_DRAW_ALL)
    {
        IPS114_DrawLine(x + r, y, x, y, color);
        IPS114_DrawLine(x - r, y, x, y, color);
        IPS114_DrawLine(x, y - r, x, y, color);
        IPS114_DrawLine(x, y + r, x, y, color);
        IPS114_DrawPoint(x, y, color);
    }
}


/*!
 * @brief   Draw box / filled box
 *
 * @param   x       Starting x
 * @param   y       Starting y
 * @param   width   Box width
 * @param   height  Box height
 * @param   color   Color
 * @return  void
 */
void IPS114_DrawFrame(int16_t x, int16_t y, uint16_t width, uint16_t height, const uint16_t color)
{
    for (int i = x; i < x + width; i++)
    {
        IPS114_DrawPoint(i, y, color);
        IPS114_DrawPoint(i, y + height - 1, color);
    }
    for (int j = y; j < y + height; j++)
    {
        IPS114_DrawPoint(x, j, color);
        IPS114_DrawPoint(x + width - 1, j, color);
    }
}
void IPS114_DrawBox(int16_t x, int16_t y, uint16_t width, uint16_t height, const uint16_t color)
{
    for (int i = x; i < x + width; ++i)
    {
        for (int j = y; j < y + height; ++j)
        {
            IPS114_DrawPoint(i, j, color);
        }
    }
}


/*!
 * @brief   Draw rounded box / filled box
 *
 * @param   x       Starting x
 * @param   y       Starting y
 * @param   width   Box width
 * @param   height  Box height
 * @param   color   Color
 * @param   r       Radius
 * @return  void
 */
void IPS114_DrawRFrame(int16_t x, int16_t y, uint16_t width, uint16_t height, const uint16_t color, uint8_t r)
{
    for (int i = x + r + 1; i < x + width - r - 1; i++)
    {
        IPS114_DrawPoint(i, y, color);
        IPS114_DrawPoint(i, y + height - 1, color);
    }
    for (int j = y + r + 1; j < y + height - r - 1; j++)
    {
        IPS114_DrawPoint(x, j, color);
        IPS114_DrawPoint(x + width - 1, j, color);
    }

    IPS114_DrawCircle(x + r, y + r, r, color, CIRCLE_UPPER_LEFT);
    IPS114_DrawCircle(x + width - 1 - r, y + r, r, color, CIRCLE_UPPER_RIGHT);
    IPS114_DrawCircle(x + r, y + height - 1 - r, r, color, CIRCLE_LOWER_LEFT);
    IPS114_DrawCircle(x + width - 1 - r, y + height - 1 - r, r, color, CIRCLE_LOWER_RIGHT);
}
void IPS114_DrawRBox(int16_t x, int16_t y, uint16_t width, uint16_t height, const uint16_t color, uint8_t r)
{
    IPS114_DrawDisc(x + r, y + r, r, color, CIRCLE_UPPER_LEFT);
    IPS114_DrawDisc(x + width - 1 - r, y + r, r, color, CIRCLE_UPPER_RIGHT);
    IPS114_DrawDisc(x + r, y + height - 1 - r, r, color, CIRCLE_LOWER_LEFT);
    IPS114_DrawDisc(x + width - 1 - r, y + height - 1 - r, r, color, CIRCLE_LOWER_RIGHT);

    IPS114_DrawBox(x + r + 1, y, width - 2 - 2 * r, r + 1, color);
    IPS114_DrawBox(x, y + r + 1, width, height - 2 * r - 2, color);
    IPS114_DrawBox(x + r + 1, y + height - 1 - r, width - 2 - 2 * r, r + 1, color);
}


/*!
 * @brief   Show Binary BMP photo on screen
 *
 * @param   x       Starting x
 * @param   y       Starting y
 * @param   width   Pic width
 * @param   height  Pic height
 * @param   pic     The array of picture(阴码 逐行式 逆向)
 */
void IPS114_ShowBMP(int16_t x, int16_t y, uint16_t width, uint16_t height, const uint8_t *pic)
{
    uint8_t temp, j;
    uint8_t x0 = x;
    uint8_t *tmp = (uint8_t *) pic;
    uint16_t i, picSize = 0;

    picSize = (width / 8 + ((width % 8) ? 1 : 0)) * height;

    for (i = 0; i < picSize; i++)
    {
        temp = tmp[i];
        for (j = 0; j < 8; j++)
        {
            if (temp & 0x01)
            {
                IPS114_DrawPoint(x, y, IPS114_penColor);
            }
            temp >>= 1;
            x++;

            if ((x - x0) == width)
            {
                x = x0;
                y++;
                break;
            }
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 显示 8bit 灰度图像 带二值化阈值
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips114_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips114_y_max-1]
// 参数说明     *image          图像数组指针
// 参数说明     width           图像实际宽度
// 参数说明     height          图像实际高度
// 参数说明     dis_width       图像显示宽度 参数范围 [0, ips114_x_max]
// 参数说明     dis_height      图像显示高度 参数范围 [0, ips114_y_max]
// 参数说明     threshold       二值化显示阈值 0-不开启二值化
// 返回参数     void
// 使用示例     ips114_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void
IPS114_ShowGrayImage(uint16_t x, uint16_t y, const uint8_t *image, uint16_t width, uint16_t height, uint16_t dis_width,
                     uint16_t dis_height, uint8_t threshold)
{
    uint16_t i, j;
    uint16_t color, temp;
    uint32_t width_index, height_index;

    IPS114_CS(0);
    for (j = 0; j < dis_height; j++)
    {
        height_index = j * height / dis_height;
        for (i = 0; i < dis_width; i++)
        {
            width_index = i * width / dis_width;
            temp = *(image + height_index * width + width_index);
            if (threshold == 0)
            {
                color = (0x001f & ((temp) >> 3)) << 11;
                color = color | (((0x003f) & ((temp) >> 2)) << 5);
                color = color | (0x001f & ((temp) >> 3));
                IPS114_DrawPoint(x + i, y + j, color);
            } else if (temp < threshold)
                IPS114_DrawPoint(x + i, y + j, RGB565_BLACK);
            else
                IPS114_DrawPoint(x + i, y + j, RGB565_WHITE);
        }
    }
    IPS114_CS(1);
}