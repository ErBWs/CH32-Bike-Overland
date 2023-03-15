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
* �ļ�����          zf_device_wireless_uart.h
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
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   RX                  �鿴 zf_device_wireless_uart.h �� WIRELESS_UART_RX_PIN  �궨��
*                   TX                  �鿴 zf_device_wireless_uart.h �� WIRELESS_UART_TX_PIN  �궨��
*                   RTS                 �鿴 zf_device_wireless_uart.h �� WIRELESS_UART_RTS_PIN �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
*********************************************************************************************************************/


#ifndef _zf_device_wireless_uart_h_
#define _zf_device_wireless_uart_h_

#include "zf_common_typedef.h"

#define WIRELESS_UART_INDEX        UART_7                                      // ���ߴ��ڶ�Ӧʹ�õĴ��ں�
#define WIRELESS_UART_BUAD_RATE    115200                                      // ���ߴ��ڶ�Ӧʹ�õĴ��ڲ�����
#define WIRELESS_UART_TX_PIN       UART7_MAP3_RX_E13                           // ���ߴ��ڶ�Ӧģ��� TX Ҫ�ӵ���Ƭ���� RX
#define WIRELESS_UART_RX_PIN       UART7_MAP3_TX_E12                           // ���ߴ��ڶ�Ӧģ��� RX Ҫ�ӵ���Ƭ���� TX
#define WIRELESS_UART_RTS_PIN      E8                                          // ���ߴ��ڶ�Ӧģ��� RTS ����


// ------------------------------------ �Զ������� ------------------------------------
// ע������1������ת����ģ��汾��V2.0���µ����޷������Զ������ʵġ�
// ע������2�������Զ��������������RTS���� ����Ὺ��ʧ�ܡ�
// ע������3��ģ���Զ�������ʧ�ܵĻ� ���Գ��Զϵ�����

// �����Զ�����������Ķ��������� ע������
// �����Զ�����������Ķ��������� ע������
// �����Զ�����������Ķ��������� ע������

// 0���ر��Զ�������
// 1�������Զ������� �Զ������ʵ��������޸� WIRELESS_UART_BAUD ֮����Ҫ��ģ��������� ģ����Զ�����Ϊ��Ӧ�Ĳ�����

#define WIRELESS_UART_AUTO_BAUD_RATE    (0)
// ------------------------------------ �Զ������� ------------------------------------

#define WIRELESS_UART_BUFFER_SIZE       (64  )
#define WIRELESS_UART_TIMEOUT_COUNT     (0x64)

uint32      wireless_uart_send_byte         (const uint8 data);
uint32      wireless_uart_send_buff         (const uint8 *buff, uint32 len);
uint32      wireless_uart_send_string       (const char *str);
void        wireless_uart_send_image        (const uint8 *image_addr, uint32 image_size);

uint32      wireless_uart_read_buff         (uint8 *buff, uint32 len);

void        wireless_uart_callback          (void);

uint8       wireless_uart_init              (void);

#endif
