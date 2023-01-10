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
// �������     IPS114 SPI д 8bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     ips114_write_8bit_data(dat);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define ips114_write_8bit_data(data)    (spi_write_8bit(IPS114_SPI, (data)))

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 SPI д 16bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     ips114_write_16bit_data(x1 + 52);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define ips114_write_16bit_data(data)   (spi_write_16bit(IPS114_SPI, (data)))

//-------------------------------------------------------------------------------------------------------------------
// �������     д����
// ����˵��     dat             ����
// ���ز���     void
// ʹ��ʾ��     ips114_write_index(0x2a);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void ips114_write_index (const uint8 dat)
{
    IPS114_DC(0);
    ips114_write_8bit_data(dat);
    IPS114_DC(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ����
// ����˵��     x1              ��ʼx������
// ����˵��     y1              ��ʼy������
// ����˵��     x2              ����x������
// ����˵��     y2              ����y������
// ���ز���     void
// ʹ��ʾ��     ips114_set_region(0, 0, ips114_x_max - 1, ips114_y_max - 1);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void ips114_set_region (const int16 x1, const int16 y1, const int16 x2, const int16 y2)
{

    if(ips114_display_dir == IPS114_PORTAIT)
    {
        ips114_write_index(0x2a);                                               // �е�ַ����
        ips114_write_16bit_data(x1 + 52);
        ips114_write_16bit_data(x2 + 52);
        ips114_write_index(0x2b);                                               // �е�ַ����
        ips114_write_16bit_data(y1 + 40);
        ips114_write_16bit_data(y2 + 40);
        ips114_write_index(0x2c);                                               // ������д
    }
    else if(ips114_display_dir == IPS114_PORTAIT_180)
    {
        ips114_write_index(0x2a);                                               // �е�ַ����
        ips114_write_16bit_data(x1 + 53);
        ips114_write_16bit_data(x2 + 53);
        ips114_write_index(0x2b);                                               // �е�ַ����
        ips114_write_16bit_data(y1 + 40);
        ips114_write_16bit_data(y2 + 40);
        ips114_write_index(0x2c);                                               // ������д
    }
    else if(ips114_display_dir == IPS114_CROSSWISE)
    {
        ips114_write_index(0x2a);                                               // �е�ַ����
        ips114_write_16bit_data(x1 + 40);
        ips114_write_16bit_data(x2 + 40);
        ips114_write_index(0x2b);                                               // �е�ַ����
        ips114_write_16bit_data(y1 + 53);
        ips114_write_16bit_data(y2 + 53);
        ips114_write_index(0x2c);                                               // ������д
    }
    else
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

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ����
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     ips114_draw_point(0, 0, RGB565_RED);            // ���� 0,0 ��һ����ɫ�ĵ�
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void IPS114_DrawPoint (int16 x, int16 y, const uint16 color)
{
    IPS114_CS(0);
    ips114_set_region(x, y, x, y);
    ips114_write_16bit_data(color);
    IPS114_CS(1);
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
// �������     IPS114 ��ʾ�ַ�
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ���ַ�
// ���ز���     void
// ʹ��ʾ��     ips114_show_char(0, 0, 'x');                    // ���� 0,0 дһ���ַ� x
// ��ע��Ϣ
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
                // �� 32 ��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո��� ascii ������� 32
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
                // �� 32 ��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո��� ascii ������� 32
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
            // �ݲ�֧��
            break;
    }
    IPS114_CS(1);
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
                // �ݲ�֧��
                break;
        }
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
// �������     IPS114 ��ʾ32λ�޷��� (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� uint32
// ����˵��     num             ��Ҫ��ʾ��λ�� ���10λ  ������������
// ���ز���     void
// ʹ��ʾ��     ips114_show_uint(0, 0, x, 3);                   // x ����Ϊ uint32 uint16 uint8 ����
// ��ע��Ϣ     ��������ʾһ�� ��-����   ������ʾһ���ո�
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