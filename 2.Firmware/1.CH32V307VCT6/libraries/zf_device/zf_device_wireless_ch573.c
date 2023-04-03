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

#include "zf_common_fifo.h"
#include "zf_device_type.h"
#include "zf_device_wireless_ch573.h"

static  fifo_struct       wireless_ch573_fifo;
static  uint8             wireless_ch573_buffer[WIRELESS_CH573_BUFFER_SIZE];                                // ��Ӧ��һ�� ���ߴ��� ���ݴ������

static  uint8             wireless_ch573_data;

//-------------------------------------------------------------------------------------------------------------------
// �������      CH573����ģ���жϻص�����
// ����˵��     void
// ���ز���     void
// Sample usage:
// @note
//-------------------------------------------------------------------------------------------------------------------
void wireless_ch573_callback (void)
{
    uart_query_byte(WIRELESS_CH573_INDEX, &wireless_ch573_data);
    fifo_write_buffer(&wireless_ch573_fifo, &wireless_ch573_data, 1);

}


//-------------------------------------------------------------------------------------------------------------------
// �������      ����ת����ģ�� ��������
// ����˵��     data            8bit ����
// ���ز���     uint32          ʣ�෢�ͳ���
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_ch573_send_byte (const uint8 data)
{
    uint16 time_count = 0;
    while(gpio_get_level(WIRELESS_CH573_RTS_PIN))                                      // ���RTSΪ�͵�ƽ���������������
    {
        if(time_count++ > WIRELESS_CH573_TIMEOUT_COUNT)
            return 1;                                                           // ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
        system_delay_ms(1);
    }
    uart_write_byte(WIRELESS_CH573_INDEX, data);                                 // ������������

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      CH573����ģ�� ���ڷ�������
// ����˵��     buff            ���ݵ�ַ
// ����˵��     len             ���ݳ���
// ���ز���     uint32        ��ʾ��Ϣ
// Sample usage:
// @note
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_ch573_send_buff (const uint8 *buff, uint32 len)
{
    uint16 time_count = 0;
    uint8 pack_len = 62;
    while(len > pack_len)
    {
        time_count = 0;
        while(gpio_get_level(WIRELESS_CH573_RTS_PIN) && time_count++ < WIRELESS_CH573_TIMEOUT_COUNT)  // ���RTSΪ�͵�ƽ���������������
            system_delay_ms(1);
        if(time_count >= WIRELESS_CH573_TIMEOUT_COUNT)
            return len;                                                                             // ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
        uart_write_buffer(WIRELESS_CH573_INDEX, buff, 30);

        buff += pack_len;                                                                           // ��ַƫ��
        len -= pack_len;                                                                            // ����
    }

    time_count = 0;
    while(gpio_get_level(WIRELESS_CH573_RTS_PIN) && time_count++ < WIRELESS_CH573_TIMEOUT_COUNT)  // ���RTSΪ�͵�ƽ���������������
        system_delay_ms(1);
    if(time_count >= WIRELESS_CH573_TIMEOUT_COUNT)
        return len;                                                                                 // ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
    uart_write_buffer(WIRELESS_CH573_INDEX, buff, len);                                            // ������������

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      CH573����ģ�� ���ڽ�������
// ����˵��     buff            ���ݵ�ַ
// ����˵��     len             ���ݳ���
// ���ز���     void
// Sample usage:
// @note
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_ch573_read_buff (uint8 *buff, uint32 len)
{
    uint32 data_len = len;
    fifo_read_buffer(&wireless_ch573_fifo, buff, &data_len, FIFO_READ_AND_CLEAN);
    return data_len;
}


//-------------------------------------------------------------------------------------------------------------------
// �������      ����ת����ģ�� ��������ͷͼ������λ���鿴ͼ��
// ����˵��     *image_addr     ��Ҫ���͵�ͼ���ַ
// ����˵��     image_size      ͼ��Ĵ�С
// ���ز���     void
// ʹ��ʾ��     wireless_uart_send_image(&mt9v03x_image[0][0], MT9V03X_IMAGE_SIZE);
//-------------------------------------------------------------------------------------------------------------------
void wireless_ch573_send_image (const uint8 *image_addr, uint32 image_size)
{
    extern uint8 camera_send_image_frame_header[4];
    wireless_ch573_send_buff(camera_send_image_frame_header, 4);
    wireless_ch573_send_buff((uint8 *)image_addr, image_size);
}

//-------------------------------------------------------------------------------------------------------------------
// �������      CH573����ģ���ʼ��
// ����˵��     void
// ���ز���     void
// Sample usage:
// @note
//-------------------------------------------------------------------------------------------------------------------
uint8 wireless_ch573_init (void)
{

    set_wireless_type(WIRELESS_CH573, wireless_ch573_callback);



    fifo_init(&wireless_ch573_fifo, FIFO_DATA_8BIT, wireless_ch573_buffer, WIRELESS_CH573_BUFFER_SIZE);
    gpio_init(WIRELESS_CH573_RTS_PIN, GPI, GPIO_HIGH, GPI_PULL_UP);

    uart_init (WIRELESS_CH573_INDEX, WIRELESS_CH573_BUAD_RATE, WIRELESS_CH573_RX_PIN, WIRELESS_CH573_TX_PIN);
    uart_rx_interrupt(WIRELESS_CH573_INDEX, 1);

    return 0;
}



