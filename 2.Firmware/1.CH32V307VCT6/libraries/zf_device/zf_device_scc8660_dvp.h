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
* �ļ�����          zf_device_scc8660_dvp
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
*���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   TXD                 �鿴 zf_device_scc8660.h �� SCC8660_COF_UART_TX_DVP        �궨��
*                   RXD                 �鿴 zf_device_scc8660.h �� SCC8660_COF_UART_RX_DVP        �궨��
*                   D0                  �鿴 zf_device_scc8660.h �� SCC8660_D0_PIN_DVP             �궨��
*                   D1                  �鿴 zf_device_scc8660.h �� SCC8660_D1_PIN_DVP             �궨��
*                   D2                  �鿴 zf_device_scc8660.h �� SCC8660_D2_PIN_DVP             �궨��
*                   D3                  �鿴 zf_device_scc8660.h �� SCC8660_D3_PIN_DVP             �궨��
*                   D4                  �鿴 zf_device_scc8660.h �� SCC8660_D4_PIN_DVP             �궨��
*                   D5                  �鿴 zf_device_scc8660.h �� SCC8660_D5_PIN_DVP             �궨��
*                   D6                  �鿴 zf_device_scc8660.h �� SCC8660_D6_PIN_DVP             �궨��
*                   D7                  �鿴 zf_device_scc8660.h �� SCC8660_D7_PIN_DVP             �궨��
*                   PCLK                �鿴 zf_device_scc8660.h �� SCC8660_PCLK_PIN_DVP           �궨��
*                   VSYNC               �鿴 zf_device_scc8660.h �� SCC8660_VSY_PIN_DVP            �궨��
*                   HSYNC               �鿴 zf_device_scc8660.h �� SCC8660_HERF_PIN_DVP           �궨��
*                   ------------------------------------
********************************************************************************************************************/


#ifndef _zf_device_scc8660_h_
#define _zf_device_scc8660_h_

#include "zf_common_typedef.h"

//--------------------------------------------------------------------------------------------------
// ��������
//--------------------------------------------------------------------------------------------------
#define SCC8660_COF_UART        UART_5                                          // ��������ͷ��ʹ�õ��Ĵ���
#define SCC8660_COF_BAUR        9600                                            // ��������ͷ�õĴ��ڲ����� ��ֹ�޸�
#define SCC8660_COF_UART_RX     UART5_MAP0_TX_C12                               // ����ͷ��  UART-RX ���� Ҫ���ڵ�Ƭ�� TX ��
#define SCC8660_COF_UART_TX     UART5_MAP0_RX_D2                                // ����ͷ��  UART-TX ���� Ҫ���ڵ�Ƭ�� RX ��

#define SCC8660_D0_PIN          (A9 )
#define SCC8660_D1_PIN          (A10)
#define SCC8660_D2_PIN          (C8 )
#define SCC8660_D3_PIN          (C9 )
#define SCC8660_D4_PIN          (C11)
#define SCC8660_D5_PIN          (B6 )
#define SCC8660_D6_PIN          (B8 )
#define SCC8660_D7_PIN          (B9 )

#define SCC8660_PCLK_PIN        (A6 )
#define SCC8660_VSY_PIN         (A5 )
#define SCC8660_HERF_PIN        (A4 )
#define SCC8660_INIT_TIMEOUT    (0x0080)                                        // Ĭ�ϵ�����ͷ��ʼ����ʱʱ�� ����Ϊ��λ

//--------------------------------------------------------------------------------------------------
// ����ͷĬ�ϲ������� �ڴ��޸�����ͷ����
//--------------------------------------------------------------------------------------------------
#define SCC8660_W               (160)                                           // ʵ��ͼ��ֱ��ʿ�� ��ѡ����Ϊ��160 180
#define SCC8660_H               (120)                                           // ʵ��ͼ��ֱ��ʸ߶� ��ѡ����Ϊ��120 160
#define SCC8660_IMAGE_SIZE      (SCC8660_W * 2 * SCC8660_H)                     // ����ͼ���С SCC8660_W*2*SCC8660_H ���ܳ��� 65535

#define SCC8660_AUTO_EXP_DEF    (0  )                                           // �Զ��ع�     Ĭ�ϲ������Զ��ع�����  ��Χ [0-1] 0Ϊ�ر�
#define SCC8660_BRIGHT_DEF      (300)                                           // ��������     �ֶ��ع�Ĭ�ϣ�300   �ֶ��ع�ʱ��������Χ0-65535   �Զ��ع��Ƽ�ֵ��100 �Զ��ع�ʱ�������÷�Χ0-255
#define SCC8660_FPS_DEF         (60 )                                           // ͼ��֡��     Ĭ�ϣ�60        ��ѡ����Ϊ��60 50 30 25�� ʵ��֡�ʻ���Ҫ��SCC8660_PCLK_DIV����������
#define SCC8660_PCLK_DIV_DEF    (0  )                                           // PCLK��Ƶϵ�� Ĭ�ϣ�0         ��ѡ����Ϊ��<0:1/1> <1:2/3> <2:1/2> <3:1/3> <4:1/4> <5:1/8>
                                                                                //              ��Ƶϵ��Խ��PCLKƵ��Խ�ͣ�����PCLK���Լ���DVP�ӿڵĸ��ţ�������PCLKƵ�����Ӱ��֡�ʡ��������������뱣��Ĭ�ϡ�
                                                                                //              ��������FPSΪ50֡������pclk��Ƶϵ��ѡ���Ϊ5��������ͷ�����֡��Ϊ50*��1/8��=6.25֡
                                                                                //              �����������������£�SCC8660_PCLK_DIV����Խ��ͼ���Խ��
#define SCC8660_PCLK_MODE_DEF   (1  )                                           // PCLKģʽ     Ĭ�ϣ�0         ��ѡ����Ϊ��[0,1] 0������������ź� 1����������ź� <ͨ��������Ϊ0�����ʹ��STM32��DCMI�ӿڲɼ���Ҫ����Ϊ1>
#define SCC8660_COLOR_MODE_DEF  (0  )                                           // ͼ��ɫ��ģʽ Ĭ�ϣ�0         ��ѡ����Ϊ��[0,1] 0��������ɫģʽ   1������ģʽ��ɫ�ʱ��Ͷ���ߣ�
#define SCC8660_DATA_FORMAT_DEF (0  )                                           // ������ݸ�ʽ Ĭ�ϣ�0         ��ѡ����Ϊ��[0-3] 0��RGB565 1��RGB565(�ֽڽ���) 2��YUV422(YUYV) 3��YUV422(UYVY)
#define SCC8660_MANUAL_WB_DEF   (0  )                                           // �ֶ���ƽ��   Ĭ�ϣ�0         ��ѡ����Ϊ��[0,0x65-0xa0] 0���ر��ֶ���ƽ�⣬�����Զ���ƽ��    �������ֶ���ƽ�� �ֶ���ƽ��ʱ ������Χ0x65-0xa0

// ����ͷ����ö��
typedef enum
{
    SCC8660_INIT                = 0x00,                                         // ����ͷ��ʼ������
    SCC8660_AUTO_EXP,                                                           // �Զ��ع�����
    SCC8660_BRIGHT,                                                             // ��������
    SCC8660_FPS,                                                                // ����ͷ֡������
    SCC8660_SET_COL,                                                            // ͼ��������
    SCC8660_SET_ROW,                                                            // ͼ��������
    SCC8660_PCLK_DIV,                                                           // ����ʱ�ӷ�Ƶ����
    SCC8660_PCLK_MODE,                                                          // ����ʱ��ģʽ����
    SCC8660_COLOR_MODE,                                                         // ɫ��ģʽ����
    SCC8660_DATA_FORMAT,                                                        // ���ݸ�ʽ����
    SCC8660_MANUAL_WB,                                                          // �ֶ���ƽ������
    SCC8660_CONFIG_FINISH,                                                      // ������λ����Ҫ����ռλ����

    SCC8660_GET_WHO_AM_I        = 0xEF,                                         // ����˭��������ж�����ͷ�ͺ�
    SCC8660_SET_BRIGHT          = 0xF0,                                         // ������������
    SCC8660_GET_STATUS          = 0XF1,                                         // ��ȡ����ͷ��������
    SCC8660_GET_VERSION         = 0xF2,                                         // �̼��汾��
    SCC8660_SET_MANUAL_WB       = 0xF3,                                         // ���������ֶ���ƽ��

    SCC8660_SET_REG_ADDR        = 0xFE,
    SCC8660_SET_REG_DATA        = 0xFF,
}scc8660_cmd_enum;

extern vuint8       scc8660_finish_flag;                                        // һ��ͼ��ɼ���ɱ�־λ
extern uint16       scc8660_image[SCC8660_H][SCC8660_W];

uint16      scc8660_get_id              (void);
uint16      scc8660_get_parameter       (uint16 config);
uint16      scc8660_get_version         (void);
uint8       scc8660_set_bright          (uint16 data);
uint8       scc8660_set_white_balance   (uint16 data);
uint8       scc8660_set_reg             (uint8 addr, uint16 data);

uint8       scc8660_init                (void);

#endif
