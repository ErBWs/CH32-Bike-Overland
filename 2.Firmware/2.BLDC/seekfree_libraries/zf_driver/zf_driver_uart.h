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
* �ļ�����          zf_driver_uart
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

#ifndef _zf_driver_uart_h
#define _zf_driver_uart_h

#include "ch32v30x.h"
#include "ch32v30x_gpio.h"
#include "ch32v30x_rcc.h"
#include "ch32v30x_usart.h"

#include "zf_common_interrupt.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"

//  ��ö�ٶ��岻�����û��޸�
//  ��ʼ����ʱ�򣬱���ʹ��ͬһ���������磬UART1_MAP_TX_A9��UART1_MAP_RX_A10��һ������
//
typedef enum //  ��ö�ٶ��岻�����û��޸�
{
    // MAP0  Ĭ��ӳ��
    // MAP1  ��ӳ��
    // MAP2  ����ӳ��
    // MAP3  ��ȫӳ��

    //----------UART1-----------//
    // ����Ϊ����1��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ���磺UART1_MAP0_TX_A9��UART1_MAP1_TX_B6����һ��ʹ�á�

    // Ĭ��ӳ��
    UART1_MAP0_TX_A9  = 0x0000 | A9 ,
    UART1_MAP0_RX_A10 = 0x0000 | A10,

    // ����Ϊ����1��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ӳ��               
    UART1_MAP1_TX_B6  = 0x0100 | B6 ,
    UART1_MAP1_RX_B7  = 0x0100 | B7 ,

    // ����Ϊ����1��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ����ӳ��             
    UART1_MAP2_TX_B15 = 0x0200 | B15,
    UART1_MAP2_RX_A8  = 0x0200 | A8 ,

    // ����Ϊ����1��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ȫӳ��             
    UART1_MAP3_TX_A6  = 0x0300 | A6 ,
    UART1_MAP3_RX_A7  = 0x0300 | A7 ,

    //----------UART2-----------//

    // ����Ϊ����2��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    UART2_MAP0_TX_A2  = 0x1000 | A2 ,
    UART2_MAP0_RX_A3  = 0x1000 | A3 ,

    // ����Ϊ����2��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ӳ��               
    UART2_MAP1_TX_D5  = 0x1100 | D5 ,
    UART2_MAP1_RX_D6  = 0x1100 | D6 ,
                            
    //----------UART3--------------//

    // ����Ϊ����3��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��             
    UART3_MAP0_TX_B10 = 0x2000 | B10,               // ����������Ĭ������
    UART3_MAP0_RX_B11 = 0x2000 | B11,               // ����������Ĭ������

    // ����Ϊ����3��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ӳ��               
    UART3_MAP1_TX_C10 = 0x2100 | C10,
    UART3_MAP1_RX_C11 = 0x2100 | C11,

    // ����Ϊ����3��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ȫӳ��             
    UART3_MAP2_TX_D8  = 0x2300 | D8 ,
    UART3_MAP2_RX_D9  = 0x2300 | D9 ,

    //----------UART4-----------//

    // ����Ϊ����4��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    UART4_MAP0_TX_C10 = 0x3000 | C10,
    UART4_MAP0_RX_C11 = 0x3000 | C11,

    // ����Ϊ����4��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ӳ��               
    UART4_MAP1_TX_B0  = 0x3100 | B0 ,
    UART4_MAP1_RX_B1  = 0x3100 | B1 ,

    // ����Ϊ����4��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ȫӳ��             
    UART4_MAP3_TX_E0  = 0x3300 | E0 ,
    UART4_MAP3_RX_E1  = 0x3300 | E1 ,

    //----------UART5-----------//

    // ����Ϊ����5��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    UART5_MAP0_TX_C12 = 0x4000 | C12,
    UART5_MAP0_RX_D2  = 0x4000 | D2,

    // ����Ϊ����5��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ӳ��                
    UART5_MAP1_TX_B4  = 0x4100 | B4,
    UART5_MAP1_RX_B5  = 0x4100 | B5,

    // ����Ϊ����5��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ȫӳ��             
    UART5_MAP3_TX_E8  = 0x4300 | E8,
    UART5_MAP3_RX_E9  = 0x4300 | E9,

    //----------UART6-----------//

    // ����Ϊ����6��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    UART6_MAP0_TX_C0  = 0x5000 | C0 ,
    UART6_MAP0_RX_C1  = 0x5000 | C1 ,

    // ����Ϊ����6��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ӳ��                
    UART6_MAP1_TX_B8  = 0x5100 | B8 ,
    UART6_MAP1_RX_B9  = 0x5100 | B9 ,

    // ����Ϊ����6��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ȫӳ��             
    UART6_MAP3_TX_E10 = 0x5300 | E10,
    UART6_MAP3_RX_E11 = 0x5300 | E11,

    //----------UART7-----------//

    // ����Ϊ����7��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    UART7_MAP0_TX_C2  = 0x6000 | C2 ,
    UART7_MAP0_RX_C3  = 0x6000 | C3 ,

    // ����Ϊ����7��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ӳ��                
    UART7_MAP1_TX_A6  = 0x6100 | A6 ,
    UART7_MAP1_RX_A7  = 0x6100 | A7 ,

    // ����Ϊ����7��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ȫӳ��             
    UART7_MAP3_TX_E12 = 0x6300 | E12,
    UART7_MAP3_RX_E13 = 0x6300 | E13,

    //----------UART8-----------//

    // ����Ϊ����8��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    UART8_MAP0_TX_C4  = 0x7000 | C4 ,
    UART8_MAP0_RX_C5  = 0x7000 | C5 ,

    // ����Ϊ����8��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ӳ��                
    UART8_MAP1_TX_A14 = 0x7100 | A14,
    UART8_MAP1_RX_A15 = 0x7100 | A15,

    // ����Ϊ����8��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ȫӳ��             
    UART8_MAP3_TX_E14 = 0x7300 | E14,
    UART8_MAP3_RX_E15 = 0x7300 | E15,

}uart_pin_enum;


typedef enum//  ��ö�ٶ��岻�����û��޸�
{
    UART_1,
    UART_2,
    UART_3,
    UART_4,
    UART_5,
    UART_6,
    UART_7,
    UART_8,
}uart_index_enum;



extern const uint32 uart_index[];




void    uart_write_byte         (uart_index_enum uart_n, const uint8 dat);
void    uart_write_buffer       (uart_index_enum uart_n, const uint8 *buff, uint32 len);
void    uart_write_string       (uart_index_enum uart_n, const char *str);

void    uart_read_byte          (uart_index_enum uart_n, uint8 *dat);
uint8   uart_query_byte         (uart_index_enum uart_n, uint8 *dat);

void    uart_tx_interrupt       (uart_index_enum uart_n, uint8 status);
void    uart_rx_interrupt       (uart_index_enum uart_n, uint8 status);

void    uart_init               (uart_index_enum uart_n, uint32 baud, uart_pin_enum tx_pin, uart_pin_enum rx_pin);



#endif
