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
* �ļ�����          zf_device_type
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
#ifndef _zf_device_type_h_
#define _zf_device_type_h_

#include "zf_common_typedef.h"

typedef enum
{
    NO_CAMERE = 0,                                                              // ������ͷ
    CAMERA_BIN_IIC,                                                             // С��� IIC �汾
    CAMERA_BIN_UART,                                                            // С��� UART �汾
    CAMERA_GRAYSCALE,                                                           // �����
    CAMERA_COLOR,                                                               // ��ͫ
}camera_type_enum;

typedef enum
{
    NO_WIRELESS = 0,                                                            // ���豸
    WIRELESS_UART,                                                              // ���ߴ���
    BLUETOOTH_CH9141,                                                           // ���� CH9141
    WIFI_UART,                                                                  // Wi-Fi ����
    WIRELESS_CH573,
}wireless_type_enum;

typedef void (*callback_function)(void);

extern camera_type_enum     camera_type;
extern wireless_type_enum   wireless_type;

extern callback_function    camera_uart_handler;
extern callback_function    camera_dvp_handler;
extern callback_function    wireless_module_uart_handler;

void    set_camera_type     (camera_type_enum type_set, callback_function uart_callback, callback_function dvp_callback);
void    set_wireless_type   (wireless_type_enum type_set, callback_function uart_callback);

#endif
