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
// �������     ������ʾ����
// ����˵��     x1              ��ʼx������
// ����˵��     y1              ��ʼy������
// ����˵��     x2              ����x������
// ����˵��     y2              ����y������
// ���ز���     void
// ʹ��ʾ��     ips096_set_region(0, 0, ips096_x_max - 1, ips096_y_max - 1);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void ips096_set_region (const uint16 x1, const uint16 y1, const uint16 x2, const uint16 y2)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    // ���һ�������ʾ���õĺ��� �Լ�����һ�����ﳬ������Ļ��ʾ��Χ
    zf_assert(x1 < ips096_x_max);
    zf_assert(y1 < ips096_y_max);
    zf_assert(x2 < ips096_x_max);
    zf_assert(y2 < ips096_y_max);

    if(ips096_display_dir == IPS096_PORTRAIT)
    {
        ips096_write_index(0x2a);                                               // �е�ַ����
        ips096_write_16bit_data(x1 + 24);
        ips096_write_16bit_data(x2 + 24);
        ips096_write_index(0x2b);                                               // �е�ַ����
        ips096_write_16bit_data(y1);
        ips096_write_16bit_data(y2);
        ips096_write_index(0x2c);                                               // ������д
    }
    else if(ips096_display_dir == IPS096_PORTRAIT_180)
    {
        ips096_write_index(0x2a);                                               // �е�ַ����
        ips096_write_16bit_data(x1 + 24);
        ips096_write_16bit_data(x2 + 24);
        ips096_write_index(0x2b);                                               // �е�ַ����
        ips096_write_16bit_data(y1);
        ips096_write_16bit_data(y2);
        ips096_write_index(0x2c);                                               // ������д
    }
    else if(ips096_display_dir == IPS096_CROSSWISE)
    {
        ips096_write_index(0x2a);                                               // �е�ַ����
        ips096_write_16bit_data(x1);
        ips096_write_16bit_data(x2);
        ips096_write_index(0x2b);                                               // �е�ַ����
        ips096_write_16bit_data(y1 + 24);
        ips096_write_16bit_data(y2 + 24);
        ips096_write_index(0x2c);                                               // ������д
    }
    else
    {
        ips096_write_index(0x2a);                                               // �е�ַ����
        ips096_write_16bit_data(x1);
        ips096_write_16bit_data(x2);
        ips096_write_index(0x2b);                                               // �е�ַ����
        ips096_write_16bit_data(y1 + 24);
        ips096_write_16bit_data(y2 + 24);
        ips096_write_index(0x2c);                                               // ������д
    }
}


//-------------------------------------------------------------------------------------------------------------------
// �������     IPS096 ��������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     ips096_clear();
// ��ע��Ϣ     ����Ļ��ճɱ�����ɫ
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
// �������     IPS096 ��Ļ��亯��
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     ips096_full(RGB565_BLACK);
// ��ע��Ϣ
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
// �������     ������ʾ����
// ����˵��     dir             ��ʾ����  ���� zf_device_ips096.h �� ips096_dir_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     ips096_set_dir(IPS096_CROSSWISE);
// ��ע��Ϣ     �������ֻ���ڳ�ʼ����Ļ֮ǰ���ò���Ч
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
// �������     ������ʾ����
// ����˵��     dir             ��ʾ����  ���� zf_device_ips096.h �� ips096_font_size_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     ips096_set_font(IPS096_8x16_FONT);
// ��ע��Ϣ     ���������ʱ�������� ���ú���Ч ������ʾ�����µ������С
//-------------------------------------------------------------------------------------------------------------------
void ips096_set_font (ips096_font_size_enum font)
{
    ips096_display_font = font;
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ��ɫ
// ����˵��     pen             ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ����˵��     bgcolor         ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     ips096_set_color(RGB565_WHITE, RGB565_BLACK);
// ��ע��Ϣ     ������ɫ�ͱ�����ɫҲ������ʱ�������� ���ú���Ч
//-------------------------------------------------------------------------------------------------------------------
void ips096_set_color (const uint16 pen, const uint16 bgcolor)
{
    ips096_pencolor = pen;
    ips096_bgcolor = bgcolor;
}


//-------------------------------------------------------------------------------------------------------------------
// �������     IPS096 ����
// ����˵��     x               ����x�������� ������Χ [0, ips096_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips096_y_max-1]
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     ips096_draw_point(0, 0, RGB565_RED);            // ���� 0,0 ��һ����ɫ�ĵ�
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void ips096_draw_point (uint16 x, uint16 y, const uint16 color)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);

    IPS096_CS(0);
    ips096_set_region(x, y, x, y);
    ips096_write_16bit_data(color);
    IPS096_CS(1);
}


//-------------------------------------------------------------------------------------------------------------------
// �������     IPS096 ����
// ����˵��     x_start         ����x��������
// ����˵��     y_start         ����y��������
// ����˵��     x_end           ����x������յ�
// ����˵��     y_end           ����y������յ�
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     ips096_draw_line(0, 0, 10, 10, RGB565_RED);     // ���� 0,0 �� 10,10 ��һ����ɫ����
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void ips096_draw_line (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
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
// �������     IPS096 ��ʾ�ַ�
// ����˵��     x               ����x�������� ������Χ [0, ips096_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips096_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ���ַ�
// ���ز���     void
// ʹ��ʾ��     ips096_show_char(0, 0, 'x');                    // ���� 0,0 дһ���ַ� x
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_char (uint16 x, uint16 y, const char dat)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
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
            // �� 32 ��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո��� ascii ������� 32
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
            // �� 32 ��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո��� ascii ������� 32
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
// �������     IPS096 ��ʾ�ַ���
// ����˵��     x               ����x�������� ������Χ [0, ips096_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips096_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ���ַ���
// ���ز���     void
// ʹ��ʾ��     ips096_show_string(0, 0, "seekfree");
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_string (uint16 x, uint16 y, const char dat[])
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
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
// �������     IPS096 ��ʾ32λ�з��� (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, ips096_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips096_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� int32
// ����˵��     num             ��Ҫ��ʾ��λ�� ���10λ  ������������
// ���ز���     void
// ʹ��ʾ��     ips096_show_int(0, 0, x, 3);                    // x ����Ϊ int32 int16 int8 ����
// ��ע��Ϣ     ��������ʾһ�� ��-����   ������ʾһ���ո�
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_int (uint16 x, uint16 y, const int32 dat, uint8 num)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
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
// �������     IPS096 ��ʾ32λ�޷��� (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, ips096_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips096_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� uint32
// ����˵��     num             ��Ҫ��ʾ��λ�� ���10λ  ������������
// ���ز���     void
// ʹ��ʾ��     ips096_show_uint(0, 0, x, 3);                   // x ����Ϊ uint32 uint16 uint8 ����
// ��ע��Ϣ     ��������ʾһ�� ��-����   ������ʾһ���ո�
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_uint (uint16 x, uint16 y, const uint32 dat, uint8 num)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
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
// �������     IPS096 ��ʾ������ (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, ips096_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips096_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� float �� double
// ����˵��     num             ����λ��ʾ����   ���10λ
// ����˵��     pointnum        С��λ��ʾ����   ���6λ
// ���ز���     void
// ʹ��ʾ��     ips096_show_float(0, 0, x, 2, 3);               // ��ʾ������ ������ʾ 2 λ С����ʾ 3 λ
// ��ע��Ϣ     �ر�ע�⵱����С��������ʾ��ֵ����д���ֵ��һ����ʱ��
//              ���������ڸ��������ȶ�ʧ���⵼�µģ��Ⲣ������ʾ���������⣬
//              �й���������飬�����аٶ�ѧϰ   ���������ȶ�ʧ���⡣
//              ��������ʾһ�� ��-����   ������ʾһ���ո�
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_float (uint16 x, uint16 y, const float dat, uint8 num, uint8 pointnum)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
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
// �������     IPS096 ��ʾ��ֵͼ�� ����ÿ�˸������һ���ֽ�����
// ����˵��     x               ����x�������� ������Χ [0, ips096_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips096_y_max-1]
// ����˵��     *image          ͼ������ָ��
// ����˵��     width           ͼ��ʵ�ʿ��
// ����˵��     height          ͼ��ʵ�ʸ߶�
// ����˵��     dis_width       ͼ����ʾ��� ������Χ [0, ips096_x_max]
// ����˵��     dis_height      ͼ����ʾ�߶� ������Χ [0, ips096_y_max]
// ���ز���     void
// ʹ��ʾ��     ips096_show_binary_image(0, 0, ov7725_image_binary[0], OV7725_W, OV7725_H, OV7725_W, OV7725_H);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_binary_image (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);
    zf_assert(image != NULL);

    uint32 i = 0, j = 0;
    uint8 temp = 0;
    uint32 width_index = 0, height_index = 0;

    IPS096_CS(0);
    ips096_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // ������ʾ����

    for(j = 0; j < dis_height; j ++)
    {
        height_index = j * height / dis_height;
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            temp = *(image + height_index * width / 8 + width_index / 8);       // ��ȡ���ص�
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
// �������     IPS096 ��ʾ 8bit �Ҷ�ͼ�� ����ֵ����ֵ
// ����˵��     x               ����x�������� ������Χ [0, ips096_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips096_y_max-1]
// ����˵��     *image          ͼ������ָ��
// ����˵��     width           ͼ��ʵ�ʿ��
// ����˵��     height          ͼ��ʵ�ʸ߶�
// ����˵��     dis_width       ͼ����ʾ��� ������Χ [0, ips096_x_max]
// ����˵��     dis_height      ͼ����ʾ�߶� ������Χ [0, ips096_y_max]
// ����˵��     threshold       ��ֵ����ʾ��ֵ 0-��������ֵ��
// ���ز���     void
// ʹ��ʾ��     ips096_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_gray_image (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);
    zf_assert(image != NULL);

    uint32 i = 0, j = 0;
    uint16 color = 0,temp = 0;
    uint32 width_index = 0, height_index = 0;

    IPS096_CS(0);
    ips096_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // ������ʾ����

    for(j = 0; j < dis_height; j ++)
    {
        height_index = j * height / dis_height;
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            temp = *(image + height_index * width + width_index);               // ��ȡ���ص�
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
// �������     IPS096 ��ʾ����
// ����˵��     x               ����x�������� ������Χ [0, ips096_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips096_y_max-1]
// ����˵��     *wave           ��������ָ��
// ����˵��     width           ����ʵ�ʿ��
// ����˵��     value_max       ����ʵ�����ֵ
// ����˵��     dis_width       ������ʾ��� ������Χ [0, ips096_x_max]
// ����˵��     dis_value_max   ������ʾ���ֵ ������Χ [0, ips096_y_max]
// ���ز���     void
// ʹ��ʾ��     ips096_show_wave(56,35,data,128,64,128,64);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void ips096_show_wave (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips096_x_max);
    zf_assert(y < ips096_y_max);
    zf_assert(wave != NULL);

    uint32 i = 0, j = 0;
    uint32 width_index = 0, value_max_index = 0;

    IPS096_CS(0);
    ips096_set_region(x, y, x + dis_width - 1, y + dis_value_max - 1);          // ������ʾ����
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
// �������     1.14�� IPS Һ����ʾDEBUG��Ϣ��ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     ips096_debug_init();
// ��ע��Ϣ     �ڲ�ʹ��
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
// �������     1.14�� IPSҺ����ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     ips096_init();
// ��ע��Ϣ
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