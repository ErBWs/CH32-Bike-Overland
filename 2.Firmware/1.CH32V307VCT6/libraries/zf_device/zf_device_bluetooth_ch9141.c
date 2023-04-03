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
* �ļ�����          zf_device_bluetooth_ch9141
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2022-01-10        ��W            �Ի�CH1��CH2�����ź�
* 2022-03-16        ��W            ɾ����Բ���������ʹ�������λ���������
* 2022-09-15        ��W            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* ���߶���:
*                   ------------------------------------
*                   ģ��ܽ�                  ��Ƭ���ܽ�
*                   TX          �鿴 zf_device_bluetooth_ch9141.h �� BLUETOOTH_CH9141_TX_PIN �궨��
*                   RX          �鿴 zf_device_bluetooth_ch9141.h �� BLUETOOTH_CH9141_RX_PIN �궨��
*                   RTS         �鿴 zf_device_bluetooth_ch9141.h �� BLUETOOTH_CH9141_RTS_PIN �궨��
*                   VCC         3.3V��Դ
*                   GND         ��Դ��
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_fifo.h"

#include "zf_device_type.h"

#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"
#include "zf_driver_delay.h"

#include "zf_device_bluetooth_ch9141.h"

static  fifo_struct     bluetooth_ch9141_fifo;
static  uint8           bluetooth_ch9141_buffer[BLUETOOTH_CH9141_BUFFER_SIZE];  // ���ݴ������

static  uint8           bluetooth_ch9141_data;

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� ��������
// ����˵��     data            8bit ����
// ���ز���     uint32          ʣ�෢�ͳ���
// ʹ��ʾ��     bluetooth_ch9141_send_byte(0x5A);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint32 bluetooth_ch9141_send_byte (const uint8 data)
{
    uint16 time_count = BLUETOOTH_CH9141_TIMEOUT_COUNT;
    while(time_count)
    {
        if(!gpio_get_level(BLUETOOTH_CH9141_RTS_PIN))
        {
            uart_write_byte(BLUETOOTH_CH9141_INDEX, data);                      // ��������
            break;
        }
        time_count --;
        system_delay_ms(1);
    }
    return (0 < time_count);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� ���ͺ���
// ����˵��     buff             ��Ҫ���͵����ݵ�ַ
// ���ز���     len              ���ͳ���
// ʹ��ʾ��     uint32           ʣ��δ���͵��ֽ���
// ʹ��ʾ��     bluetooth_ch9141_send_buff(buff, 16);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint32 bluetooth_ch9141_send_buff (const uint8 *buff, uint32 len)
{
    zf_assert(buff != NULL);
    uint16 time_count = 0;
    while(0 != len)
    {
        if(!gpio_get_level(BLUETOOTH_CH9141_RTS_PIN))                           // ���RTSΪ�͵�ƽ �������������
        {
            if(30 <= len)                                                       // ���ݷ� 30byte ÿ������
            {
                uart_write_buffer(BLUETOOTH_CH9141_INDEX, buff, 30);            // ��������
                buff += 30;                                                     // ��ַƫ��
                len -= 30;                                                      // ����
                time_count = 0;
            }
            else                                                                // ���� 30byte ������һ���Է������
            {
                uart_write_buffer(BLUETOOTH_CH9141_INDEX, buff, len);           // ��������
                len = 0;
                break;
            }
        }
        else                                                                    // ���RTSΪ�ߵ�ƽ ��ģ��æ
        {
            if(BLUETOOTH_CH9141_TIMEOUT_COUNT <= (++ time_count))               // ���������ȴ�ʱ��
            {
                break;                                                          // �˳�����
            }
            system_delay_ms(1);
        }
    }
    return len;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� �����ַ���
// ����˵��     *str            Ҫ���͵��ַ�����ַ
// ���ز���     uint32          ʣ�෢�ͳ���
// ʹ��ʾ��     bluetooth_ch9141_send_string("Trust yourself.");
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint32 bluetooth_ch9141_send_string (const char *str)
{
    zf_assert(str != NULL);
    uint16 time_count = 0;
    uint32 len = strlen(str);
    while(0 != len)
    {
        if(!gpio_get_level(BLUETOOTH_CH9141_RTS_PIN))                           // ���RTSΪ�͵�ƽ �������������
        {
            if(30 <= len)                                                       // ���ݷ� 30byte ÿ������
            {
                uart_write_buffer(BLUETOOTH_CH9141_INDEX, (const uint8 *)str, 30);   // ��������
                str += 30;                                                      // ��ַƫ��
                len -= 30;                                                      // ����
                time_count = 0;
            }
            else                                                                // ���� 30byte ������һ���Է������
            {
                uart_write_buffer(BLUETOOTH_CH9141_INDEX, (const uint8 *)str, len);// ��������
                len = 0;
                break;
            }
        }
        else                                                                    // ���RTSΪ�ߵ�ƽ ��ģ��æ
        {
            if(BLUETOOTH_CH9141_TIMEOUT_COUNT <= (++ time_count))               // ���������ȴ�ʱ��
            {
                break;                                                          // �˳�����
            }
            system_delay_ms(1);
        }
    }
    return len;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� ��������ͷͼ������λ���鿴ͼ��
// ����˵��     *image_addr     ��Ҫ���͵�ͼ���ַ
// ����˵��     image_size      ͼ��Ĵ�С
// ���ز���     void
// ʹ��ʾ��     bluetooth_ch9141_send_image(&mt9v03x_image[0][0], MT9V03X_IMAGE_SIZE);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void bluetooth_ch9141_send_image (const uint8 *image_addr, uint32 image_size)
{
    zf_assert(image_addr != NULL);
    uint16 time_count = 0;

    extern uint8 camera_send_image_frame_header[4];
    bluetooth_ch9141_send_buff(camera_send_image_frame_header, 4);
    bluetooth_ch9141_send_buff((uint8 *)image_addr, image_size);

    while(0 != image_size)
    {
        if(!gpio_get_level(BLUETOOTH_CH9141_RTS_PIN))                           // ���RTSΪ�͵�ƽ �������������
        {
//            system_delay_ms(5);
            if(30 <= image_size)                                                // ���ݷ� 30byte ÿ������
            {
                uart_write_buffer(BLUETOOTH_CH9141_INDEX, image_addr, 30);      // ��������
                image_addr += 30;                                               // ��ַƫ��
                image_size -= 30;                                               // ����
                time_count = 0;
            }
            else                                                                // ���� 30byte ������һ���Է������
            {
                uart_write_buffer(BLUETOOTH_CH9141_INDEX, image_addr, image_size);// ��������
                image_size = 0;
                break;
            }
        }
        else                                                                    // ���RTSΪ�ߵ�ƽ ��ģ��æ
        {
            if(BLUETOOTH_CH9141_TIMEOUT_COUNT <= (++ time_count))               // ���������ȴ�ʱ��
            {
                break;                                                          // �˳�����
            }
            system_delay_ms(1);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� ��ȡ����
// ����˵��     buff            �洢�����ݵ�ַ
// ����˵��     len             ����
// ���ز���     uint32          ʵ�ʶ�ȡ�ֽ���
// ʹ��ʾ��     bluetooth_ch9141_read_buff(buff, 16);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint32 bluetooth_ch9141_read_buff (uint8 *buff, uint32 len)
{
    zf_assert(buff != NULL);
    uint32 data_len = len;
    fifo_read_buffer(&bluetooth_ch9141_fifo, buff, &data_len, FIFO_READ_AND_CLEAN);
    return data_len;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� �����жϻص�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��
// ��ע��Ϣ     �ú����� ISR �ļ��Ĵ����жϳ��򱻵���
//              �ɴ����жϷ��������� wireless_module_uart_handler() ����
//              ���� wireless_module_uart_handler() �������ñ�����
//-------------------------------------------------------------------------------------------------------------------
void bluetooth_ch9141_uart_callback (void)
{
    uart_query_byte(BLUETOOTH_CH9141_INDEX, &bluetooth_ch9141_data);            // ��ȡ��������
    fifo_write_buffer(&bluetooth_ch9141_fifo, &bluetooth_ch9141_data, 1);       // ���� FIFO
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� ��ʼ��
// ����˵��     void
// ���ز���     uint8           ��ʼ��״̬ 0-�ɹ� 1-ʧ��
// ʹ��ʾ��     bluetooth_ch9141_init();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint8 bluetooth_ch9141_init (void)
{
    uint8 return_state = 0;
    set_wireless_type(BLUETOOTH_CH9141, bluetooth_ch9141_uart_callback);

    fifo_init(&bluetooth_ch9141_fifo, FIFO_DATA_8BIT, bluetooth_ch9141_buffer, BLUETOOTH_CH9141_BUFFER_SIZE);
    // ������ʹ�õĲ�����Ϊ115200 Ϊ����ת����ģ���Ĭ�ϲ����� ����������������ʹ����λ���޸�ģ�����
    gpio_init(BLUETOOTH_CH9141_RTS_PIN, GPI, 1, GPI_PULL_UP);                   // ��ʼ����������
    uart_init(BLUETOOTH_CH9141_INDEX, BLUETOOTH_CH9141_BUAD_RATE, BLUETOOTH_CH9141_RX_PIN, BLUETOOTH_CH9141_TX_PIN);
    uart_rx_interrupt(BLUETOOTH_CH9141_INDEX, 1);

    return return_state;
}


