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
* �ļ�����          zf_device_mt9v03x
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2021-12-23        ��W            ����ͷ�ɼ���ɱ�־λ����volatile����
* 2022-03-26        ��W            �޸Ĳ��ֲ���Ҫ��ע��
* 2022-09-15        ��W            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   TXD                 �鿴 zf_device_mt9v03x.h �� MT9V03X_COF_UART_TX        �궨��
*                   RXD                 �鿴 zf_device_mt9v03x.h �� MT9V03X_COF_UART_RX        �궨��
*                   D0                  �鿴 zf_device_mt9v03x.h �� MT9V03X_D0_PIN             �궨��
*                   D1                  �鿴 zf_device_mt9v03x.h �� MT9V03X_D1_PIN             �궨��
*                   D2                  �鿴 zf_device_mt9v03x.h �� MT9V03X_D2_PIN             �궨��
*                   D3                  �鿴 zf_device_mt9v03x.h �� MT9V03X_D3_PIN             �궨��
*                   D4                  �鿴 zf_device_mt9v03x.h �� MT9V03X_D4_PIN             �궨��
*                   D5                  �鿴 zf_device_mt9v03x.h �� MT9V03X_D5_PIN             �궨��
*                   D6                  �鿴 zf_device_mt9v03x.h �� MT9V03X_D6_PIN             �궨��
*                   D7                  �鿴 zf_device_mt9v03x.h �� MT9V03X_D7_PIN             �궨��
*                   PCLK                �鿴 zf_device_mt9v03x.h �� MT9V03X_PCLK_PIN           �궨��
*                   VSYNC               �鿴 zf_device_mt9v03x.h �� MT9V03X_VSY_PIN            �궨��
*                   HSYNC               �鿴 zf_device_mt9v03x.h �� MT9V03X_HERF_PIN           �궨��
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_mt9v03x_h_
#define _zf_device_mt9v03x_h_


#include "zf_common_typedef.h"


//--------------------------------------------------------------------------------------------------
// ��������
//--------------------------------------------------------------------------------------------------
#define MT9V03X_COF_UART        (UART_5     )                		// ��������ͷ��ʹ�õ��Ĵ���
#define MT9V03X_COF_BAUR        (9600       )                		// ��������ô��ڲ�����
#define MT9V03X_COF_UART_TX     (UART5_MAP0_RX_D2)           		// ����� UART-TX ���� Ҫ���ڵ�Ƭ�� RX ��
#define MT9V03X_COF_UART_RX     (UART5_MAP0_TX_C12)          		// ����� UART-RX ���� Ҫ���ڵ�Ƭ�� TX ��

#define MT9V03X_COF_IIC_DELAY   (500)                               // ����� IIC ��ʱ
#define MT9V03X_COF_IIC_SCL     (D2 )                               // ����� IIC-SCL ����
#define MT9V03X_COF_IIC_SDA     (C12)                               // ����� IIC-SDA ����

#define MT9V03X_D0_PIN      	(A9	)
#define MT9V03X_D1_PIN      	(A10)
#define MT9V03X_D2_PIN      	(C8 )
#define MT9V03X_D3_PIN      	(C9 )
#define MT9V03X_D4_PIN      	(C11)
#define MT9V03X_D5_PIN      	(B6 )
#define MT9V03X_D6_PIN      	(B8 )
#define MT9V03X_D7_PIN      	(B9 )
	
#define MT9V03X_PCLK_PIN    	(A6 )
#define MT9V03X_VSY_PIN     	(A5 )
#define MT9V03X_HERF_PIN    	(A4 )
#define MT9V03X_INIT_TIMEOUT    (0x0080)                          	// Ĭ�ϵ�����ͷ��ʼ����ʱʱ�� ����Ϊ��λ

//--------------------------------------------------------------------------------------------------
// ����ͷĬ�ϲ������� �ڴ��޸�����ͷ����
//--------------------------------------------------------------------------------------------------
#define MT9V03X_W               (188)                           	// ͼ����     ��Χ [1-752]
#define MT9V03X_H               (120)                           	// ͼ��߶�     ��Χ [1-480]
#define MT9V03X_IMAGE_SIZE      (MT9V03X_W * MT9V03X_H)         	// ����ͼ���С���ܳ��� 65535
		
#define MT9V03X_AUTO_EXP_DEF    (0  )                           	// �Զ��ع�����     Ĭ�ϲ������Զ��ع�����  ��Χ [0-63] 0Ϊ�ر�
																	//                  ����Զ��ع⿪��  EXP_TIME���������Զ��ع�ʱ�������
																	//                  һ������ǲ���Ҫ�����Զ��ع����� ����������߷ǳ������ȵ�������Գ��������Զ��ع⣬����ͼ���ȶ���
#define MT9V03X_EXP_TIME_DEF    (512)                           	// �ع�ʱ��         ����ͷ�յ�����Զ����������ع�ʱ�䣬������ù���������Ϊ�������������ع�ֵ
#define MT9V03X_FPS_DEF         (50 )                           	// ͼ��֡��         ����ͷ�յ�����Զ���������FPS���������������Ϊ������������FPS
#define MT9V03X_LR_OFFSET_DEF   (0  )                           	// ͼ������ƫ����   ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ188 376 752ʱ�޷�����ƫ��
																	//                  ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
#define MT9V03X_UD_OFFSET_DEF   (0  )                           	// ͼ������ƫ����   ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ120 240 480ʱ�޷�����ƫ��
																	//                  ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
#define MT9V03X_GAIN_DEF        (32 )                           	// ͼ������         ��Χ [16-64]  ����������ع�ʱ��̶�������¸ı�ͼ�������̶�
#define MT9V03X_PCLK_MODE_DEF   (1  )                           	// ����ʱ��ģʽ     ��Χ [0-1]    Ĭ�ϣ�0 ��ѡ����Ϊ��[0������������ź�,1����������ź�]
                                                                    //                  ͨ��������Ϊ0�����ʹ��CH32V307��DVP�ӿڻ�STM32��DCMI�ӿڲɼ���Ҫ����Ϊ1
                                                                    //                  ������� MT9V034 V1.5 �Լ����ϰ汾֧�ָ�����
																				
// ����ͷ����ö��
typedef enum
{
    MT9V03X_INIT = 0,                              						// ����ͷ��ʼ������
    MT9V03X_AUTO_EXP,                              						// �Զ��ع�����
    MT9V03X_EXP_TIME,                              						// �ع�ʱ������
    MT9V03X_FPS,                                   						// ����ͷ֡������
    MT9V03X_SET_COL,                               						// ͼ��������
    MT9V03X_SET_ROW,                               						// ͼ��������
    MT9V03X_LR_OFFSET,                             						// ͼ������ƫ������
    MT9V03X_UD_OFFSET,                             						// ͼ������ƫ������
    MT9V03X_GAIN,                                  						// ͼ��ƫ������
    MT9V03X_PCLK_MODE,                             						// ����ʱ��ģʽ����(�������MT9V034 V1.5�Լ����ϰ汾֧�ָ�����)
    MT9V03X_CONFIG_FINISH,                         						// ������λ����Ҫ����ռλ����
						
    MT9V03X_COLOR_GET_WHO_AM_I = 0xEF,						
    MT9V03X_SET_EXP_TIME = 0XF0,                   						// ���������ع�ʱ������
    MT9V03X_GET_STATUS,                            						// ��ȡ����ͷ��������
    MT9V03X_GET_VERSION,                           						// �̼��汾������
						
    MT9V03X_SET_ADDR = 0XFE,                       						// �Ĵ�����ַ����
    MT9V03X_SET_DATA                               						// �Ĵ�����������
}m9v03x_cmd_enum;


// ����ͷ�ӿ�����ö��
typedef enum
{
    MT9V03X_UART,
    MT9V03X_SCCB,
}m9v03x_type_enum;

extern volatile vuint8    mt9v03x_finish_flag;//һ��ͼ��ɼ���ɱ�־λ
extern uint8    mt9v03x_image[MT9V03X_H][MT9V03X_W];

void   mt9v03x_uart_callback      (void);
void   mt9v03x_handler            (void);
uint16 mt9v03x_get_version        (void);
uint8  mt9v03x_set_exposure_time  (uint16 light);
uint8  mt9v03x_set_reg            (uint8 addr, uint16 data);
uint8  mt9v03x_init               (void);

#endif
