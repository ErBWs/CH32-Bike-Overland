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
* �ļ�����          zf_device_k24c02
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
*                   ģ��ܽ�                                        ��Ƭ���ܽ�
*                   ��� IIC ͨ�����Ŷ�Ӧ��ϵ
*                   SCL                 �鿴 zf_device_k24c02.h �� K24C02_SCL_PIN �궨��
*                   SDA                 �鿴 zf_device_k24c02.h �� K24C02_SDA_PIN �궨��
*                   Ӳ�� IIC ͨ�����Ŷ�Ӧ��ϵ
*                   SCL                 �鿴 zf_device_k24c02.h �� K24C02_SCL_PIN �궨��
*                   SDA                 �鿴 zf_device_k24c02.h �� K24C02_SDA_PIN �궨��
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_k24c02_h_
#define _zf_device_k24c02_h_

#include "zf_common_typedef.h"

#define K24C02_USE_SOFT_IIC        (1)                                          // Ĭ��ʹ����� IIC ��ʽ���� ����ʹ����� IIC ��ʽ
#if K24C02_USE_SOFT_IIC                                                         // ������ ��ɫ�����Ĳ�����ȷ�� ��ɫ�ҵľ���û���õ�
//====================================================��� IIC ����====================================================
#define K24C02_SOFT_IIC_DELAY      (500)                                        // ��� IIC ��ʱ����ʱ���� ��ֵԽС IIC ͨ������Խ��
#define K24C02_SCL_PIN             (B10 )                                        // ��� IIC SCL ���� ���� K24C02 �� SCL ����
#define K24C02_SDA_PIN             (B11 )                                        // ��� IIC SDA ���� ���� K24C02 �� SDA ����
//====================================================��� IIC ����====================================================
#else
//====================================================Ӳ�� IIC ����====================================================
#define K24C02_IIC_SPEED           (400000     )                                // Ӳ�� IIC ͨ������ ��� 400KHz ��������� 40KHz
#define K24C02_IIC                 (IIC_1      )                                // Ӳ�� IIC
#define K24C02_SCL_PIN             (IIC1_SCL_C6)                                // Ӳ�� IIC SCL ���� ���� K24C02 �� SCL ����
#define K24C02_SDA_PIN             (IIC1_SDA_C7)                                // Ӳ�� IIC SDA ���� ���� K24C02 �� SDA ����
//====================================================Ӳ�� IIC ����====================================================
#endif

#define K24C02_TIMEOUT_COUNT       (0x00FF)                                     // K24C02 ��ʱ����

//================================================���� K24C02 �ڲ���ַ================================================
#define K24C02_DEV_ADDR            (0xA0 >> 1)                                  // IICд��ʱ�ĵ�ַ�ֽ����� +1Ϊ��ȡ
//================================================���� K24C02 �ڲ���ַ================================================

#define K24C02_SIZE                 (256)                                       // 256 byte
#define K24C02_PAGE_SIZE            (8)                                         // 8 byte
#define K24C02_DATA_BUFFER_SIZE     (K24C02_PAGE_SIZE / sizeof(k24c02_data_union))// �Զ�����ÿ��ҳ�ܹ����¶��ٸ�����

typedef enum                                                                    // ö�� K24C02 ҳ���� ��ö�ٶ��岻�����û��޸�
{
    K24C02_PAGE_0 , K24C02_PAGE_1 , K24C02_PAGE_2 , K24C02_PAGE_3 ,
    K24C02_PAGE_4 , K24C02_PAGE_5 , K24C02_PAGE_6 , K24C02_PAGE_7 ,
    K24C02_PAGE_8 , K24C02_PAGE_9 , K24C02_PAGE_10, K24C02_PAGE_11,
    K24C02_PAGE_12, K24C02_PAGE_13, K24C02_PAGE_14, K24C02_PAGE_15,
    K24C02_PAGE_16, K24C02_PAGE_17, K24C02_PAGE_18, K24C02_PAGE_19,
    K24C02_PAGE_20, K24C02_PAGE_21, K24C02_PAGE_22, K24C02_PAGE_23,
    K24C02_PAGE_24, K24C02_PAGE_25, K24C02_PAGE_26, K24C02_PAGE_27,
    K24C02_PAGE_28, K24C02_PAGE_29, K24C02_PAGE_30, K24C02_PAGE_31,
}k24c02_page_enum;

typedef union                                                                   // �̶������ݻ��嵥Ԫ��ʽ
{
    float   float_type;                                                         // float  ����
    uint32  uint32_type;                                                        // uint32 ����
    int32   int32_type;                                                         // int32  ����
    uint16  uint16_type;                                                        // uint16 ����
    int16   int16_type;                                                         // int16  ����
    uint8   uint8_type;                                                         // uint8  ����
    int8    int8_type;                                                          // int8   ����
}k24c02_data_union;                                                             // �����������ݹ���ͬһ�� 32bit ��ַ

extern k24c02_data_union k24c02_union_buffer[K24C02_DATA_BUFFER_SIZE];

void    k24c02_read_page                (k24c02_page_enum page_num, uint8 *buf, uint8 len);
uint8   k24c02_write_page               (k24c02_page_enum page_num, const uint8 *buf, uint8 len);

void    k24c02_read_page_to_buffer      (k24c02_page_enum page_num);
uint8   k24c02_write_page_from_buffer   (k24c02_page_enum page_num);

uint8   k24c02_init                     (void);

#endif
