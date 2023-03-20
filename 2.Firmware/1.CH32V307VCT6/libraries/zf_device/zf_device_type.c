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

#include "zf_device_type.h"


static void type_default_callback (void);

camera_type_enum    camera_type                 = NO_CAMERE;                        // ����ͷ���ͱ���
callback_function   camera_uart_handler         = type_default_callback;            // ����ͨѶ�жϺ���ָ�룬���ݳ�ʼ��ʱ���õĺ���������ת
callback_function   camera_dvp_handler          = type_default_callback;            // DVP����жϺ���ָ�룬���ݳ�ʼ��ʱ���õĺ���������ת

wireless_type_enum  wireless_type               = NO_WIRELESS;
callback_function   wireless_module_uart_handler= type_default_callback;            // ���ߴ��ڽ����жϺ���ָ�룬���ݳ�ʼ��ʱ���õĺ���������ת

//-------------------------------------------------------------------------------------------------------------------
// �������     Ĭ�ϻص�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��
// ��ע��Ϣ     ������������� ��ֹ��û�г�ʼ���豸��ʱ���ܷ�
//-------------------------------------------------------------------------------------------------------------------
static void type_default_callback (void)
{
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��������ͷ����
// ����˵��     type_set        ѡ��������ͷ����
// ����˵��     vsync_callback  �豸�ĳ��жϻص�����
// ����˵��     dma_callback    �豸�� DMA ����жϻص�����
// ����˵��     uart_callback   �豸�Ĵ��ڻص�����
// ���ز���     void
// ʹ��ʾ��     set_camera_type(CAMERA_GRAYSCALE);
// ��ע��Ϣ     һ���ɸ�����ͷ��ʼ���ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void  set_camera_type (camera_type_enum type_set, callback_function uart_callback, callback_function dvp_callback)
{
    camera_type = type_set;
    camera_dvp_handler   =  ((dvp_callback == NULL)     ?   (type_default_callback) : (dvp_callback));
    camera_uart_handler  =  ((uart_callback == NULL)    ?   (type_default_callback) : (uart_callback));
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��������ģ������
// ����˵��     type_set        ѡ��������ģ������
// ����˵��     uart_callback   �豸�Ĵ��ڻص�����
// ���ز���     void
// ʹ��ʾ��     set_wireless_type(WIRELESS_UART, uart_callback);
// ��ע��Ϣ     һ���ɸ�����ͷ��ʼ���ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void set_wireless_type (wireless_type_enum type_set, callback_function uart_callback)
{
    wireless_type = type_set;
    wireless_module_uart_handler = ((uart_callback == NULL) ? (type_default_callback) : (uart_callback));
}

