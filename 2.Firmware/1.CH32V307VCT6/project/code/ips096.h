/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library ����CH32V307VCT6 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���CH32V307VCT6 ��Դ���һ����
*
* CH32V307VCT6 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          zf_device_ips096
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2022-09-15        ��W            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�             ��Ƭ���ܽ�
*                   SCL                  �鿴 zf_device_ips096.h �� IPS096_SCL_PIN �궨��
*                   SDA                  �鿴 zf_device_ips096.h �� IPS096_SDA_PIN �궨��
*                   RST                  �鿴 zf_device_ips096.h �� IPS096_RST_PIN �궨��
*                   DC                   �鿴 zf_device_ips096.h �� IPS096_DC_PIN �궨��
*                   CS                   �鿴 zf_device_ips096.h �� IPS096_CS_PIN �궨��
*                   BLK                  �鿴 zf_device_ips096.h �� IPS096_BLK_PIN �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ���ֱ��� 135 * 240
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_ips096_h_
#define _zf_device_ips096_h_

#include "zf_common_typedef.h"

#define IPS096_USE_SOFT_SPI             (0)                                     // Ĭ��ʹ��Ӳ�� SPI ��ʽ���� ����ʹ��Ӳ�� SPI ��ʽ����
#if IPS096_USE_SOFT_SPI                                                         // ������ ��ɫ�����Ĳ�����ȷ�� ��ɫ�ҵľ���û���õ�
//====================================================��� SPI ����====================================================
#define IPS096_SOFT_SPI_DELAY           (1 )                                    // ��� SPI ��ʱ����ʱ���� ��ֵԽС SPI ͨ������Խ��
#define IPS096_SCL_PIN                  (D4)                                    // ��� SPI SCK ����
#define IPS096_SDA_PIN                  (D6)                                    // ��� SPI MOSI ����
//====================================================��� SPI ����====================================================
#else
//====================================================Ӳ�� SPI ����====================================================
#define IPS096_SPI_SPEED                (72 * 1000 * 1000)                      // Ӳ�� SPI ���� ��������Ϊϵͳʱ�Ӷ���Ƶ
#define IPS096_SPI                      (SPI_2)                                 // Ӳ�� SPI ��
#define IPS096_SCL_PIN                  (SPI2_MAP0_SCK_B13)                           // Ӳ�� SPI SCK ����
#define IPS096_SDA_PIN                  (SPI2_MAP0_MOSI_B15)                          // Ӳ�� SPI MOSI ����
//====================================================Ӳ�� SPI ����====================================================
#endif

#define IPS096_RST_PIN                  (B7 )                                   // Һ����λ���Ŷ���
#define IPS096_DC_PIN                   (D7 )                                   // Һ������λ���Ŷ���
#define IPS096_CS_PIN                   (D4 )                                   // CS Ƭѡ����
#define IPS096_BLK_PIN                  (D0 )                                   // Һ���������Ŷ���

#define IPS096_DEFAULT_DISPLAY_DIR      (IPS096_CROSSWISE_180)                  // Ĭ�ϵ���ʾ����
#define IPS096_DEFAULT_PENCOLOR         (RGB565_WHITE)                            // Ĭ�ϵĻ�����ɫ
#define IPS096_DEFAULT_BGCOLOR          (RGB565_BLACK)                          // Ĭ�ϵı�����ɫ
#define IPS096_DEFAULT_DISPLAY_FONT     (IPS096_6X8_FONT)                      // Ĭ�ϵ�����ģʽ

#define IPS096_DC(x)                    ((x) ? (gpio_high(IPS096_DC_PIN)) : (gpio_low(IPS096_DC_PIN)))
#define IPS096_RST(x)                   ((x) ? (gpio_high(IPS096_RST_PIN)) : (gpio_low(IPS096_RST_PIN)))
#define IPS096_CS(x)                    ((x) ? (gpio_high(IPS096_CS_PIN)) : (gpio_low(IPS096_CS_PIN)))
#define IPS096_BLK(x)                   ((x) ? (gpio_high(IPS096_BLK_PIN)) : (gpio_low(IPS096_BLK_PIN)))

typedef enum
{
    IPS096_PORTAIT                      = 0,                                    // ����ģʽ
    IPS096_PORTAIT_180                  = 1,                                    // ����ģʽ  ��ת180
    IPS096_CROSSWISE                    = 2,                                    // ����ģʽ
    IPS096_CROSSWISE_180                = 3,                                    // ����ģʽ  ��ת180
}ips096_dir_enum;

typedef enum
{
    IPS096_6X8_FONT                     = 0,                                    // 6x8      ����
    IPS096_8X16_FONT                    = 1,                                    // 8x16     ����
    IPS096_16X16_FONT                   = 2,                                    // 16x16    ���� Ŀǰ��֧��
}ips096_font_size_enum;

void    ips096_clear                    (void);
void    ips096_full                     (const uint16 color);
void    ips096_set_dir                  (ips096_dir_enum dir);
void    ips096_set_font                 (ips096_font_size_enum font);
void    ips096_set_color                (const uint16 pen, const  uint16 bgcolor);
void    ips096_draw_point               (uint16 x, uint16 y, const uint16 color);
void    ips096_draw_line                (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);

void    ips096_show_char                (uint16 x, uint16 y, const char dat);
void    ips096_show_string              (uint16 x, uint16 y, const char dat[]);
void    ips096_show_int                 (uint16 x,uint16 y, const int32 dat, uint8 num);
void    ips096_show_uint                (uint16 x,uint16 y, const uint32 dat, uint8 num);
void    ips096_show_float               (uint16 x,uint16 y, const float dat, uint8 num, uint8 pointnum);

void    ips096_show_binary_image        (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void    ips096_show_gray_image          (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold);
void    ips096_show_rgb565_image        (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode);

void    ips096_show_wave                (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max);
void    ips096_show_chinese             (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color);


//-------------------------------------------------------------------------------------------------------------------
// �������     IPS096 ��ʾС���ͼ��
// ����˵��     p               ͼ������
// ����˵��     width           ��ʾ���
// ����˵��     height          ��ʾ�߶�
// ���ز���     void
// ʹ��ʾ��     ips096_displayimage7725(ov7725_image_binary[0], 80, 60);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
#define ips096_displayimage7725(p, width, height)       (ips096_show_binary_image(0, 0, (p), OV7725_W, OV7725_H, (width), (height)))

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS096 ��ʾ�����ͼ�� ������ֵ�� ��ʾ�Ҷ�ͼ��
// ����˵��     p               ͼ������
// ����˵��     width           ��ʾ���
// ����˵��     height          ��ʾ�߶�
// ���ز���     void
// ʹ��ʾ��     ips096_displayimage03x(mt9v03x_image[0], 94, 60);
// ��ע��Ϣ     ���Ҫ��ʾ��ֵ��ͼ���ȥ���� ips096_show_gray_image ����
//-------------------------------------------------------------------------------------------------------------------
#define ips096_displayimage03x(p, width, height)        (ips096_show_gray_image(0, 0, (p), MT9V03X_W, MT9V03X_H, (width), (height), 0))

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS096 ��ʾ��ͫͼ��
// ����˵��     p               ͼ������
// ����˵��     width           ��ʾ���
// ����˵��     height          ��ʾ�߶�
// ���ز���     void
// ʹ��ʾ��     ips096_displayimage8660(scc8660_image[0], 80, 60);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
#define ips096_displayimage8660(p, width, height)       (ips096_show_rgb565_image(0, 0, (p), SCC8660_W, SCC8660_H, (width), (height), 1))

void    ips096_init                     (void);

#endif
