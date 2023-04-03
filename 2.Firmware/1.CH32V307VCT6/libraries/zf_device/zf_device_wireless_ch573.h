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
* �ļ�����          zf_device_wireless_ch573
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
*                   ģ��ܽ�                                 ��Ƭ���ܽ�
*                   RX                  �鿴 zf_device_wireless_ch573.h �� WIRELESS_CH573_RX_PIN  �궨��
*                   TX                  �鿴 zf_device_wireless_ch573.h �� WIRELESS_CH573_TX_PIN  �궨��
*                   RTS                 �鿴 zf_device_wireless_ch573.h �� WIRELESS_CH573_RTS_PIN �궨��
*                   VCC                 5V ��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
*********************************************************************************************************************/


#ifndef _zf_device_wireless_ch573_h_
#define _zf_device_wireless_ch573_


#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"
#include "zf_driver_delay.h"



#define WIRELESS_CH573_NUMBER            1                                           // ��������CH573����ģ������� Ĭ����������
#define WIRELESS_CH573_INDEX             UART_2                                      // CH573����ģ��1 ��Ӧʹ�õĴ��ں�
#define WIRELESS_CH573_BUAD_RATE         115200                                      // CH573����ģ��1 ��Ӧʹ�õĴ��ڲ�����
#define WIRELESS_CH573_TX_PIN            UART2_MAP1_RX_D6                                 // CH573����ģ��1 ��Ӧģ��� TX Ҫ�ӵ���Ƭ���� RX
#define WIRELESS_CH573_RX_PIN            UART2_MAP1_TX_D5                                 // CH573����ģ��1 ��Ӧģ��� RX Ҫ�ӵ���Ƭ���� TX
#define WIRELESS_CH573_RTS_PIN           E10                                         // CH573����ģ��1 ��Ӧģ��� RTS ����


#define WIRELESS_CH573_BUFFER_SIZE       64
#define WIRELESS_CH573_TIMEOUT_COUNT     0x64



void        wireless_ch573_callback      (void);
uint32      wireless_ch573_send_byte         (const uint8 data);
uint32      wireless_ch573_send_buff         (const uint8 *buff, uint32 len);
uint32      wireless_ch573_send_string       (const uint8 *str);
void        wireless_ch573_send_image        (const uint8 *image_addr, uint32 image_size);
uint32      wireless_ch573_read_buff     (uint8 *buff, uint32 len);
uint8       wireless_ch573_init          (void);

#endif
