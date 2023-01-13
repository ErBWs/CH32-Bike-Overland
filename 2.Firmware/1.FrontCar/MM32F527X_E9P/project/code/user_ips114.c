/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "user_ips114.h"

uint16_t IPS114_penColor = IPS114_DEFAULT_PENCOLOR;
uint16_t IPS114_backgroundColor = IPS114_DEFAULT_BGCOLOR;

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
        ips114_write_index(0x2a);                                               // �е�ַ����
        ips114_write_16bit_data(x1 + 40);
        ips114_write_16bit_data(x2 + 40);
        ips114_write_index(0x2b);                                               // �е�ַ����
        ips114_write_16bit_data(y1 + 53);
        ips114_write_16bit_data(y2 + 53);
        ips114_write_index(0x2c);                                               // ������д
    } else if (ips114_display_dir == IPS114_CROSSWISE_180)
    {
        ips114_write_index(0x2a);                                               // �е�ַ����
        ips114_write_16bit_data(x1 + 40);
        ips114_write_16bit_data(x2 + 40);
        ips114_write_index(0x2b);                                               // �е�ַ����
        ips114_write_16bit_data(y1 + 52);
        ips114_write_16bit_data(y2 + 52);
        ips114_write_index(0x2c);                                               // ������д
    }
}

void IPS114_SetDrawColor(IPS114_ColorMode_e mode)
{
    IPS114_colorMode = mode;
}

/*!
 * @brief   Send buffer to ips114
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
// �������     IPS114 ����
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     ips114_draw_point(0, 0, RGB565_RED);            // ���� 0,0 ��һ����ɫ�ĵ�
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void IPS114_DrawPoint(int16 x, int16 y, const uint16 color)
{
    if (x < 240 && y < 135)
    {
        IPS114_buffer[y][x] = color;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ����
// ����˵��     x_start         ����x��������
// ����˵��     y_start         ����y��������
// ����˵��     x_end           ����x������յ�
// ����˵��     y_end           ����y������յ�
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     ips114_draw_line(0, 0, 10, 10, RGB565_RED);     // ���� 0,0 �� 10,10 ��һ����ɫ����
// ��ע��Ϣ
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
// �������     IPS114 ��ʾ�ַ�
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ���ַ�
// ���ز���     void
// ʹ��ʾ��     ips114_show_char(0, 0, 'x');                    // ���� 0,0 дһ���ַ� x
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void IPS114_ShowChar(int16 x, int16 y, const char dat)
{
    uint8 i, j;

    for (i = 0; i < 6; i++)
    {
        // �� 32 ��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո��� ascii ������� 32
        uint8 temp_top = ascii_font_6x8[dat - 32][i];
        for (j = 0; j < 8; j++)
        {
            if (x + i < 240 && y + j < 135)
            {
                if (temp_top & 0x01)
                {
                    IPS114_buffer[y + j][x + i] = IPS114_penColor;
                } else
                {
                    IPS114_buffer[y + j][x + i] = IPS114_backgroundColor;
                }
                temp_top >>= 1;
            } else
            {
                break;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ�ַ���
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ���ַ���
// ���ز���     void
// ʹ��ʾ��     ips114_show_string(0, 0, "seekfree");
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void IPS114_ShowStr(int16 x, int16 y, const char dat[])
{
    uint16 j = 0;
    while (dat[j] != '\0')
    {
        IPS114_ShowChar(x + 6 * j, y, dat[j]);
        j++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ32λ�з��� (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� int32
// ����˵��     num             ��Ҫ��ʾ��λ�� ���10λ  ������������
// ���ز���     void
// ʹ��ʾ��     ips114_show_int(0, 0, x, 3);                    // x ����Ϊ int32 int16 int8 ����
// ��ע��Ϣ     ��������ʾһ�� ��-����   ������ʾһ���ո�
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
// �������     IPS114 ��ʾ32λ�޷��� (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� uint32
// ����˵��     num             ��Ҫ��ʾ��λ�� ���10λ  ������������
// ���ز���     void
// ʹ��ʾ��     ips114_show_uint(0, 0, x, 3);                   // x ����Ϊ uint32 uint16 uint8 ����
// ��ע��Ϣ     ��������ʾһ�� ��-����   ������ʾһ���ո�
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
// �������     IPS114 ��ʾ������ (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� float �� double
// ����˵��     num             ����λ��ʾ����   ���8λ
// ����˵��     pointnum        С��λ��ʾ����   ���6λ
// ���ز���     void
// ʹ��ʾ��     ips114_show_float(0, 0, x, 2, 3);               // ��ʾ������ ������ʾ 2 λ С����ʾ 3 λ
// ��ע��Ϣ     �ر�ע�⵱����С��������ʾ��ֵ����д���ֵ��һ����ʱ��
//              ���������ڸ��������ȶ�ʧ���⵼�µģ��Ⲣ������ʾ���������⣬
//              �й���������飬�����аٶ�ѧϰ   ���������ȶ�ʧ���⡣
//              ��������ʾһ�� ��-����   ������ʾһ���ո�
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

void IPS114_DrawFrame(int16_t x, int16_t y, uint16_t width, uint16_t height, const uint16_t color)
{
    if (IPS114_colorMode == XOR)
    {
        for (int i = x; i < x + width; i++)
        {
            if (IPS114_buffer[y][i] == color)
                IPS114_DrawPoint(i, y, IPS114_backgroundColor);
            else
                IPS114_DrawPoint(i, y, color);
            if (IPS114_buffer[y + height - 1][i] == color)
                IPS114_DrawPoint(i, y + height - 1, IPS114_backgroundColor);
            else
                IPS114_DrawPoint(i, y + height - 1, color);
        }
        for (int j = y; j < y + height; j++)
        {
            if (IPS114_buffer[j][x] == color)
                IPS114_DrawPoint(x, j, IPS114_backgroundColor);
            else
                IPS114_DrawPoint(x, j, color);
            if (IPS114_buffer[j][x + width - 1] == color)
                IPS114_DrawPoint(x + width - 1, j, IPS114_backgroundColor);
            else
                IPS114_DrawPoint(x + width - 1, j, color);
        }
    } else
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
}


void IPS114_SwapColor()
{
    uint16_t tmp = IPS114_penColor;
    IPS114_penColor = IPS114_backgroundColor;
    IPS114_backgroundColor = tmp;
}

void IPS114_DrawBox(int16_t x, int16_t y, uint16_t width, uint16_t height, const uint16_t color)
{
    for (int i = x; i < x + width; ++i)
    {
        for (int j = y; j < y + height; ++j)
        {
            if (IPS114_colorMode == XOR)
            {
                if (IPS114_buffer[j][i] == color)
                    IPS114_buffer[j][i] = IPS114_backgroundColor;
                else
                    IPS114_buffer[j][i] = color;
            } else
                IPS114_buffer[j][i] = color;
        }
    }
}

/*!
 *
 */
void IPS114_DrawRFrame(int16_t x, int16_t y, uint16_t width, uint16_t height, const uint16_t color)
{
    if (IPS114_colorMode == XOR)
    {
        for (int i = x + 1; i < x + width - 1; i++)
        {
            if (IPS114_buffer[y][i] == color)
                IPS114_DrawPoint(i, y, IPS114_backgroundColor);
            else
                IPS114_DrawPoint(i, y, color);
            if (IPS114_buffer[y + height - 1][i] == color)
                IPS114_DrawPoint(i, y + height - 1, IPS114_backgroundColor);
            else
                IPS114_DrawPoint(i, y + height - 1, color);
        }
        for (int j = y + 1; j < y + height - 1; j++)
        {
            if (IPS114_buffer[j][x] == color)
                IPS114_DrawPoint(x, j, IPS114_backgroundColor);
            else
                IPS114_DrawPoint(x, j, color);
            if (IPS114_buffer[j][x + width - 1] == color)
                IPS114_DrawPoint(x + width - 1, j, IPS114_backgroundColor);
            else
                IPS114_DrawPoint(x + width - 1, j, color);
        }
    } else
    {
        for (int i = x + 1; i < x + width - 1; i++)
        {
            IPS114_DrawPoint(i, y, color);
            IPS114_DrawPoint(i, y + height - 1, color);
        }
        for (int j = y + 1; j < y + height - 1; j++)
        {
            IPS114_DrawPoint(x, j, color);
            IPS114_DrawPoint(x + width - 1, j, color);
        }
    }
}

void IPS114_DrawRBox(int16_t x, int16_t y, uint16_t width, uint16_t height, const uint16_t color)
{
    IPS114_DrawRFrame(x, y, width, height, color);
    IPS114_DrawBox(x + 1, y + 1, width - 2, height - 2, color);
}

/*!
 * @brief   Show Binary BMP photo on screen
 *
 * @param   x       Starting x
 * @param   y       Starting y
 * @param   width   Pic width
 * @param   height  Pic height
 * @param   pic     The array of picture(���� ����ʽ ����)
 */
void IPS114_ShowBMP(int16_t x, int16_t y, uint16_t width, uint16_t height, const uint8_t *pic)
{
    uint8_t temp, j;
    uint8_t x0 = x;
    uint8_t *tmp = (uint8_t *)pic;
    uint16_t i, picSize = 0;

    picSize = (width / 8 + ((width % 8) ? 1 : 0)) * height;

    for (i = 0; i < picSize; i++)
    {
        temp = tmp[i];
        for (j = 0; j < 8; j++)
        {
            if (temp & 0x01)
            {
                IPS114_buffer[y][x] = IPS114_penColor;
            }
            else
            {
                IPS114_buffer[y][x] = IPS114_backgroundColor;
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