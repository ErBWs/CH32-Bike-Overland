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
* �ļ�����          zf_device_wifi_uart
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
*                   RX                  �鿴 zf_device_wifi_uart.h �� WRIELESS_UART_RX_PINx  �궨��
*                   TX                  �鿴 zf_device_wifi_uart.h �� WRIELESS_UART_TX_PINx  �궨��
*                   RTS                 �鿴 zf_device_wifi_uart.h �� WRIELESS_UART_RTS_PINx �궨��
*                   RST                 �鿴 zf_device_wifi_uart.h �� WRIELESS_UART_RST_PINx �궨��
*                   VCC                 5V ��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
*********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_fifo.h"
#include "zf_common_function.h"
#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"
#include "zf_device_type.h"

#include "zf_device_wifi_uart.h"



#define WAIT_TIME_OUT                   (10000)                                 // ��ָ��ȴ�ʱ��  ��λ��ms

wifi_uart_information_struct    wifi_uart_information;                          // ģ���������

static  fifo_struct             wifi_uart_fifo;
static  uint8                   wifi_uart_buffer[WIFI_UART_BUFFER_SIZE];        // ���ݴ������
static  uint8                   wifi_uart_data;

//--------------------------------------------------------------------------------------------------
// �������     �ȴ�ģ����Ӧ
// ����˵��     *wait_buffer    �ȴ�����Ӧ���ַ���
// ����˵��     timeout         ��ʱʱ��
// ���ز���     uint8           0��ģ����Ӧָ������   1��ģ��δ��Ӧָ�����ݻ�ʱ
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_uart_wait_ack (char *wait_buffer, uint32 timeout)
{
    uint8 return_state = 1;
    char receiver_buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint32 receiver_len = 8;

    do
    {
        system_delay_ms(1);
        // �жϽ��ջ��������Ƿ�����Ҫ��Ӧ��ָ������ ����� ������ѭ�����ҷ���0
        receiver_len = 8;
        fifo_read_tail_buffer(&wifi_uart_fifo, (uint8 *)receiver_buffer, &receiver_len, FIFO_READ_ONLY);
        if(strstr(receiver_buffer, wait_buffer))
        {
            return_state = 0;
            break;
        }
        else if(strstr(receiver_buffer, "ERROR") || strstr(receiver_buffer, "busy"))
        {
        // ������յ��������ģ��æ ������ѭ�����ҷ���1
            return_state = 1;
            break;
        }
    }while(timeout --);
    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ���WiFi���ջ���������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     wifi_uart_clear_receive_buffer();
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static void wifi_uart_clear_receive_buffer (void)
{
    // ���WiFi���ջ�����
    fifo_clear(&wifi_uart_fifo);
}

//--------------------------------------------------------------------------------------------------
// �������     ģ�����ݽ���
// ����˵��     *target_buffer  Ŀ���ŵ�ַָ�� �ַ�������
// ����˵��     *origin_buffer  ������Դ��ַָ�� �ַ�������
// ����˵��     start_char      ��ʼ��ȡ�ֽ� ����� "1234" �д� '2' ��ʼ��ȡ ��Ӧ������ '2'
// ����˵��     end_char        ������ȡ�ֽ� ����� "1234" ���� '4' ������ȡ ��Ӧ������ '\0'(0x00 ���ַ� һ�����ַ�����β)
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_data_parse(wifi_uart_information.mac, wifi_uart_receive_buffer, '"', '"'); // ���û�ȡ����mac��ַ�󣬵��ô˺�����ȡmac��ַ
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_data_parse (uint8 *target_buffer, uint8 *origin_buffer, char start_char, char end_char)
{
    uint8 return_state = 0;
    char *location1;
    char *location2;
    location1 = strchr((char *)origin_buffer, start_char);
    if(location1)
    {
        location1 ++;
        location2 = strchr(location1, end_char);
        if(location2)
        {
            memcpy(target_buffer, location1, location2-location1);
        }
        else
        {
            return_state = 1;
        }
    }
    else
    {
        return_state = 1;
    }
    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �鿴ģ��汾��Ϣ
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_get_version();
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_uart_get_version (void)
{
    char *location1;
    uint8 return_state = 0;
    uint8 receiver_buffer[256];
    uint32 receiver_len = 256;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "AT+GMR\r\n");
    do
    {

        if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            break;
        }

        fifo_read_buffer(&wifi_uart_fifo, receiver_buffer, &receiver_len, FIFO_READ_ONLY);
        location1 = strrchr((char *)receiver_buffer, ':');
        if(wifi_data_parse(wifi_uart_information.wifi_uart_version, (uint8 *)location1, ':', '('))
        {
            return_state = 1;
            break;
        }
    }while(0);
    wifi_uart_clear_receive_buffer();                                           // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ģ���������
// ����˵��     model           0:�ر�ģ��Ļ�д����  ����������ģ���д
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_writeback_set("1");//����ģ���д����
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_uart_echo_set (char *model)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "ATE");
    uart_write_string(WIFI_UART_INDEX, model);
    uart_write_string(WIFI_UART_INDEX, "\r\n");
    return_state = wifi_uart_wait_ack("OK", WAIT_TIME_OUT);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ����ģ��Ĵ�������
// ����˵��     baudrate        ������  ֧�ַ�ΧΪ 80 ~ 5000000
// ����˵��     databits        ����λ  5��5 bit ����λ----6��6 bit ����λ----7��7 bit ����λ----8��8 bit ����λ
// ����˵��     stopbits        ֹͣλ  1��1 bit ֹͣλ----2��1.5 bit ֹͣλ----3��2 bit ֹͣλ
// ����˵��     parity          У��λ  0��None----1��Odd----2��Even
// ����˵��     flow_control    ����   0����ʹ������----1��ʹ�� RTS----2��ʹ�� CTS----3��ͬʱʹ�� RTS �� CTS
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_uart_config_set("115200", "8", "1", "0", "1");
// ��ע��Ϣ     �ڲ����� ��ʱ���� ���粻����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_uart_uart_config_set (char *baudrate, char *databits, char *stopbits, char *parity, char *flow_control)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "AT+UART_CUR=");
    uart_write_string(WIFI_UART_INDEX, baudrate);
    uart_write_string(WIFI_UART_INDEX, ",");
    uart_write_string(WIFI_UART_INDEX, databits);
    uart_write_string(WIFI_UART_INDEX, ",");
    uart_write_string(WIFI_UART_INDEX, stopbits);
    uart_write_string(WIFI_UART_INDEX, ",");
    uart_write_string(WIFI_UART_INDEX, parity);
    uart_write_string(WIFI_UART_INDEX, ",");
    uart_write_string(WIFI_UART_INDEX, flow_control);
    uart_write_string(WIFI_UART_INDEX, "\r\n");
    return_state = wifi_uart_wait_ack("OK", WAIT_TIME_OUT);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ��ѯģ������ �� MAC ��ַ
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     if(wifi_uart_get_mac()){}
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_uart_get_mac (void)
{
    uint8 return_state = 0;
    uint8 receiver_buffer[64];
    uint32 receiver_len = 64;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "AT+CIPAPMAC?\r\n");
    do
    {
        if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            break;
        }

        fifo_read_buffer(&wifi_uart_fifo, receiver_buffer, &receiver_len, FIFO_READ_ONLY);
        if(wifi_data_parse(wifi_uart_information.wifi_uart_mac, receiver_buffer, '"', '"'))
        {
            return_state = 1;
            break;
        }
    }while(0);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����


    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ��ѯģ�����Ŀ��WIFI �� IP ��ַ(ȡ����ģ�鵱ǰ�Ĺ���ģʽ)
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     if(wifi_uart_get_ip()){}
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_uart_get_ip (void)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    if(wifi_uart_information.wifi_uart_mode == WIFI_UART_STATION)
    {
        uart_write_string(WIFI_UART_INDEX, "AT+CIPSTA?\r\n");
    }
    else if(wifi_uart_information.wifi_uart_mode == WIFI_UART_SOFTAP)
    {
        uart_write_string(WIFI_UART_INDEX, "AT+CIPAP?\r\n");
    }

    do
    {
        if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            break;
        }
        uint8 receiver_buffer[128];
        uint32 receiver_len = 128;
        fifo_read_buffer(&wifi_uart_fifo, receiver_buffer, &receiver_len, FIFO_READ_ONLY);
        if(wifi_data_parse(wifi_uart_information.wifi_uart_local_ip, receiver_buffer, '"', '"'))
        {
            return_state = 1;
            break;
        }
    }while(0);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ��ѯģ��������Ϣ
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     if(wifi_uart_get_information()){}
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_uart_get_information (void)
{
    uint8 return_state = 0;
    do
    {
        // ��ȡģ��汾��
        if(wifi_uart_get_version())
        {
            return_state = 1;
            break;
        }
        // ��ȡģ��IP��ַ
        if(wifi_uart_get_ip())
        {
            return_state = 1;
            break;
        }
        // ��ȡģ��MAC��Ϣ
        if(wifi_uart_get_mac())
        {
            return_state = 1;
            break;
        }
        memcpy(wifi_uart_information.wifi_uart_local_port, "no port", 7);
    }while(0);
    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ���� WiFi
// ����˵��     wifi_ssid       WiFi����
// ����˵��     pass_word       WiFi����
// ����˵��     model           0:��ѯWiFi�������   ����������WiFi
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_get_or_connect_wifi("WiFi_name", "Pass_word", 1);
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_uart_set_wifi (char *wifi_ssid, char *pass_word)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    if(wifi_uart_information.wifi_uart_mode == WIFI_UART_SOFTAP)
    {
        uart_write_string(WIFI_UART_INDEX, "AT+CWSAP=\"");
        uart_write_string(WIFI_UART_INDEX, wifi_ssid);
        uart_write_string(WIFI_UART_INDEX, "\",\"");
        uart_write_string(WIFI_UART_INDEX, pass_word);
        uart_write_string(WIFI_UART_INDEX, "\",5,3\r\n");
    }
    else
    {
        uart_write_string(WIFI_UART_INDEX, "AT+CWJAP=\"");
        uart_write_string(WIFI_UART_INDEX, wifi_ssid);
        uart_write_string(WIFI_UART_INDEX, "\",\"");
        uart_write_string(WIFI_UART_INDEX, pass_word);
        uart_write_string(WIFI_UART_INDEX, "\"\r\n");
    }
    return_state = wifi_uart_wait_ack("OK", WAIT_TIME_OUT);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �ϵ��Ƿ��Զ�����WiFi
// ����˵��     model           0:�ϵ粻�Զ�����wifi   �������ϵ��Զ�����wifi
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_auto_connect_wifi(0); //�ϵ粻�Զ�����wifi
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_uart_auto_connect_wifi (char *model)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "AT+CWAUTOCONN=");
    uart_write_string(WIFI_UART_INDEX, model);
    uart_write_string(WIFI_UART_INDEX, "\r\n");
    return_state = wifi_uart_wait_ack("OK", WAIT_TIME_OUT);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ��������ģʽ
// ����˵��     model           0: ������ģʽ     1��������ģʽ
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_set_connect_model("1");
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_uart_set_connect_model (char *model)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "AT+CIPMUX=");
    uart_write_string(WIFI_UART_INDEX, model);
    uart_write_string(WIFI_UART_INDEX, "\r\n");
    return_state = wifi_uart_wait_ack("OK", WAIT_TIME_OUT);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ���ô���ģʽ
// ����˵��     model           �C 0: ��ͨ����ģʽ     IP�Ͽ�����������
//                              �C 1: Wi-Fi ͸������ģʽ����֧�� TCP �����ӡ�UDP �̶�ͨ�ŶԶˡ�SSL �����ӵ����     IP�Ͽ���᲻�ϳ�����������
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_set_transfer_model("1");
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_uart_set_transfer_model (char *model)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "AT+CIPMODE=");
    uart_write_string(WIFI_UART_INDEX, model);
    uart_write_string(WIFI_UART_INDEX, "\r\n");
    return_state = wifi_uart_wait_ack("OK", WAIT_TIME_OUT);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ģ�������λ
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_soft_reset();
// ��ע��Ϣ
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_soft_reset (void)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "+++");
    system_delay_ms(100);
    uart_write_string(WIFI_UART_INDEX, "\r\n");
    system_delay_ms(100);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "AT+RST\r\n");
    return_state = wifi_uart_wait_ack("ready", WAIT_TIME_OUT);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ģ��Ӳ����λ
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_reset();
// ��ע��Ϣ
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_reset (void)
{
#if WIFI_UART_HARDWARE_RST
    uint8 return_state = 0;

    gpio_set_level(WIFI_UART_RST_PIN, 0);
    system_delay_ms(50);
    gpio_set_level(WIFI_UART_RST_PIN, 1);
    system_delay_ms(200);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    return_state = wifi_uart_wait_ack("ready", WAIT_TIME_OUT);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
#else
    return wifi_uart_soft_reset();
#endif
}

//--------------------------------------------------------------------------------------------------
// �������     ����ģ��ģʽ (Station/SoftAP/Station+SoftAP)
// ����˵��     state           0:�� Wi-Fi ģʽ�����ҹر� Wi-Fi RF----1: Station ģʽ----2: SoftAP ģʽ----3: SoftAP+Station ģʽ
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_set_model("1");
// ��ע��Ϣ
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_set_model (wifi_uart_mode_enum  mode)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    if(mode == WIFI_UART_SOFTAP)
    {
        uart_write_string(WIFI_UART_INDEX, "AT+CWMODE=2\r\n");
    }
    else
    {
        uart_write_string(WIFI_UART_INDEX, "AT+CWMODE=1\r\n");
    }
    // ����ģ�鹤��ģʽ
    wifi_uart_information.wifi_uart_mode = mode;
    return_state = wifi_uart_wait_ack("OK", WAIT_TIME_OUT);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �Ͽ���wifi������
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_close_ap();
// ��ע��Ϣ
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_disconnected_wifi (void)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "AT+CWQAP\r\n");
    return_state = wifi_uart_wait_ack("OK", WAIT_TIME_OUT);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �����͸��ģʽ
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_entry_serianet();
// ��ע��Ϣ
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_entry_serianet (void)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "AT+CIPSEND\r\n");
    return_state = wifi_uart_wait_ack("OK", WAIT_TIME_OUT);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �˳�͸��ģʽ
// ����˵��     model           0:�ر�͸��ģʽ   ����������͸��ģʽ
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_open_or_close_serianet(1);
// ��ע��Ϣ
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_exit_serianet (void)
{
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    system_delay_ms(20);
    uart_write_string(WIFI_UART_INDEX, "+++");
    system_delay_ms(1000);

    return 0;
}

//--------------------------------------------------------------------------------------------------
// �������     ����TCP����
// ����˵��     ip              Զ�� IPv4 ��ַ��IPv6 ��ַ��������
// ����˵��     port            Զ�˶˿�ֵ
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_connect_tcp_servers("192.168.101.110", "8080");
// ��ע��Ϣ     ����������Ӳ��ϵ��Ե�TCP������ ���Գ���ʹ���������ӵ���
//              �����ʹ��WiFi���� ���ܻᵼ��ģ������TCP�������ȴ��ϳ�ʱ��
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_connect_tcp_servers (char *ip, char *port, wifi_uart_transfer_mode_enum mode)
{
    zf_assert(ip != NULL);
    zf_assert(port != NULL);

    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
    do
    {
        if(wifi_uart_set_connect_model("0"))
        {
            return_state = 1;
            break;
        }

        wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

        uart_write_string(WIFI_UART_INDEX, "AT+CIPSTARTEX=\"TCP\",\"");
        uart_write_string(WIFI_UART_INDEX, ip);
        uart_write_string(WIFI_UART_INDEX, "\",");
        uart_write_string(WIFI_UART_INDEX, port);
        uart_write_string(WIFI_UART_INDEX, "\r\n");
        if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            wifi_uart_information.wifi_uart_connect_state = WIFI_UART_SERVER_OFF;
            break;
        }

        wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

        // ���ô���ģʽ
        if(wifi_uart_set_transfer_model(mode == WIFI_UART_COMMAND ? "0" : "1"))
        {
            return_state = 1;
            break;
        }

        wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
        uart_write_string(WIFI_UART_INDEX, "AT+CIPSTATE?\r\n");
        if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            break;
        }
        else
        {
            uint8 receiver_buffer[128];
            uint32 receiver_len = 128;
            fifo_read_buffer(&wifi_uart_fifo, receiver_buffer, &receiver_len, FIFO_READ_ONLY);
            char* buffer_index = (char *)receiver_buffer;
            char* end_index;

            buffer_index += 22;
            buffer_index += strlen(ip);
            buffer_index += strlen(port);
            end_index = strchr(buffer_index, ',');

            memcpy(wifi_uart_information.wifi_uart_local_port, "       ", 7);
            memcpy(wifi_uart_information.wifi_uart_local_port, buffer_index, (end_index - buffer_index));
        }

        wifi_uart_information.wifi_uart_connect_state = WIFI_UART_SERVER_ON;
        wifi_uart_information.wifi_uart_connect_mode = WIFI_UART_TCP_CLIENT;
        wifi_uart_information.wifi_uart_transfer_mode = mode;

        wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����
        if(mode == WIFI_UART_SERIANET)// ͸��ģʽ��ֱ�ӿ���͸��
        {
            if(wifi_uart_entry_serianet())
            {
                return_state = 1;
                break;
            }
        }

    }while(0);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ����UDP����
// ����˵��     *ip             Զ�� IPv4 ��ַ��IPv6 ��ַ ������ �ַ�����ʽ
// ����˵��     *port           Զ�˶˿�ֵ �ַ�����ʽ
// ����˵��     *local_port     Զ�� IPv4 ��ַ��IPv6 ��ַ ������ �ַ�����ʽ
// ����˵��     mode            ģ������ͨ��ģʽ
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_connect_udp_client("192.168.101.110", "8080", "8080", WIFI_UART_COMMAND);
// ��ע��Ϣ     �Զ�����ID
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_connect_udp_client (char *ip, char *port, char *local_port, wifi_uart_transfer_mode_enum mode)
{
    zf_assert(ip != NULL);
    zf_assert(port != NULL);
    zf_assert(local_port != NULL);
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer();                                           // ���WiFi���ջ�����
    do
    {
        if(wifi_uart_set_connect_model("0"))
        {
            return_state = 1;
            break;
        }

        wifi_uart_clear_receive_buffer();                                       // ���WiFi���ջ�����

        uart_write_string(WIFI_UART_INDEX, "AT+CIPSTARTEX=\"UDP\",\"");
        uart_write_string(WIFI_UART_INDEX, ip);
        uart_write_string(WIFI_UART_INDEX, "\",");
        uart_write_string(WIFI_UART_INDEX, port);
        uart_write_string(WIFI_UART_INDEX, ",");
        uart_write_string(WIFI_UART_INDEX, local_port);
        uart_write_string(WIFI_UART_INDEX, "\r\n");

        if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            wifi_uart_information.wifi_uart_connect_state = WIFI_UART_SERVER_OFF;
            break;
        }

        wifi_uart_clear_receive_buffer();                                       // ���WiFi���ջ�����
        if(wifi_uart_set_transfer_model(mode == WIFI_UART_COMMAND ? "0" : "1")) // ���ô���ģʽ
        {
            return_state = 1;
            break;
        }

        wifi_uart_clear_receive_buffer();                                       // ���WiFi���ջ�����
        if(mode == WIFI_UART_SERIANET)                                          // ͸��ģʽ��ֱ�ӿ���͸��
        {
            if(wifi_uart_entry_serianet())
            {
                return_state = 1;
                break;
            }
        }
        memcpy(wifi_uart_information.wifi_uart_local_port, "       ", 7);
        memcpy(wifi_uart_information.wifi_uart_local_port, local_port, strlen(local_port));
        wifi_uart_information.wifi_uart_connect_state = WIFI_UART_SERVER_ON;
        wifi_uart_information.wifi_uart_connect_mode  = WIFI_UART_UDP_CLIENT;
        wifi_uart_information.wifi_uart_transfer_mode = mode;
    }while(0);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �Ͽ����� TCP Server ʹ�ñ��ӿڽ���Ͽ���������
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_disconnect_link();
// ��ע��Ϣ
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_disconnect_link (void)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer();                                           // ���WiFi���ջ�����
    do
    {
        if(WIFI_UART_TCP_SERVER == wifi_uart_information.wifi_uart_connect_mode)
        {
            uart_write_string(WIFI_UART_INDEX, "AT+CIPCLOSE=5\r\n");
        }
        else
        {
            uart_write_string(WIFI_UART_INDEX, "AT+CIPCLOSE\r\n");
        }

        if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            wifi_uart_information.wifi_uart_connect_state = WIFI_UART_SERVER_OFF;
            break;
        }
    }while(0);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     TCP Server �Ͽ�ָ������ TCP/UDP Client �������з�Ӧ
// ����˵��     link_id         ��Ҫ�Ͽ���Ŀ������
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_disconnect_link_with_id(WIFI_UART_LINK_0);
// ��ע��Ϣ
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_disconnect_link_with_id (wifi_uart_link_id_enum link_id)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer();                                           // ���WiFi���ջ�����
    do
    {
        if(WIFI_UART_TCP_SERVER == wifi_uart_information.wifi_uart_connect_mode)
        {
            uart_write_string(WIFI_UART_INDEX, "AT+CIPCLOSE=");
            uart_write_byte(WIFI_UART_INDEX, link_id + 0x30);
            uart_write_string(WIFI_UART_INDEX, "\r\n");
        }
        else
        {
            break;
        }

        if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            wifi_uart_information.wifi_uart_connect_state = WIFI_UART_SERVER_OFF;
            break;
        }
    }while(0);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ���� TCP ������
// ����˵��     *port           �˿�ֵ �ַ�����ʽ
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_entry_tcp_servers("80");
// ��ע��Ϣ     �Զ�����ID
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_entry_tcp_servers (char *port)
{
    zf_assert(port != NULL);
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer();                                           // ���WiFi���ջ�����
    do
    {
        if(wifi_uart_set_transfer_model("0"))                                   // ���ô���ģʽΪ��ͨ����ģʽ
        {
            return_state = 1;
            break;
        }
        wifi_uart_clear_receive_buffer();                                       // ���WiFi���ջ�����

        if(wifi_uart_set_connect_model("1"))                                    // ��������ģʽΪ������ģʽ
        {
            return_state = 1;
            break;
        }
        wifi_uart_clear_receive_buffer();                                       // ���WiFi���ջ�����

        uart_write_string(WIFI_UART_INDEX, "AT+CIPSERVER=1,");
        uart_write_string(WIFI_UART_INDEX, port);
        uart_write_string(WIFI_UART_INDEX, "\r\n");

        if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            wifi_uart_information.wifi_uart_connect_state = WIFI_UART_SERVER_OFF;
            break;
        }
        memcpy(wifi_uart_information.wifi_uart_local_port, "       ", 7);
        memcpy(wifi_uart_information.wifi_uart_local_port, port, strlen(port));
        wifi_uart_information.wifi_uart_connect_state = WIFI_UART_SERVER_ON;
        wifi_uart_information.wifi_uart_transfer_mode = WIFI_UART_COMMAND;
        wifi_uart_information.wifi_uart_connect_mode = WIFI_UART_TCP_SERVER;
    }while(0);
    wifi_uart_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �ر� TCP ������
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_uart_exit_tcp_servers();
// ��ע��Ϣ
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_exit_tcp_servers (void)
{
    uint8 return_state = 0;

    wifi_uart_clear_receive_buffer();                                           // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "AT+CIPSERVER=0,1\r\n");
    return_state = wifi_uart_wait_ack("OK", WAIT_TIME_OUT);
    wifi_uart_clear_receive_buffer();                                           // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     TCP Server ģʽ�¼�鵱ǰ�������� ����ȡ IP
// ����˵��     void
// ���ز���     uint8           ��ǰ��������������
// ʹ��ʾ��     wifi_uart_tcp_servers_check_link();
// ��ע��Ϣ
//--------------------------------------------------------------------------------------------------
uint8 wifi_uart_tcp_servers_check_link (void)
{
    uint8 return_value = 0;
    uint8 loop_temp = 0;
    uint8 linke_index = 0;
    
    uint8 receiver_buffer[256];
    uint32 receiver_len = 256;

    char* buffer_index;
    char* start_index;
    char* end_index;
    
    for(loop_temp = 0; loop_temp < 5; loop_temp ++)
    {
        memset(wifi_uart_information.wifi_uart_remote_ip[loop_temp], 0, 15);
    }

    wifi_uart_clear_receive_buffer();                                           // ���WiFi���ջ�����
    uart_write_string(WIFI_UART_INDEX, "AT+CIPSTATE?\r\n");

    if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT) == 0)
    {
        fifo_read_buffer(&wifi_uart_fifo, receiver_buffer, &receiver_len, FIFO_READ_ONLY);
        buffer_index = (char *)receiver_buffer;
        for(loop_temp = 0; loop_temp < 5; loop_temp ++)
        {
            start_index = strchr(buffer_index, ':');
            if(NULL == start_index)
            {
                break;
            }
            start_index ++;
            linke_index = *(start_index) - 0x30;
            start_index += 9;
            end_index = strchr((const char *)(start_index), '"');
            memset(wifi_uart_information.wifi_uart_remote_ip[linke_index], 0, 15);
            memcpy(wifi_uart_information.wifi_uart_remote_ip[linke_index], start_index, (end_index - start_index));
            buffer_index = end_index;
        }
    }
    wifi_uart_clear_receive_buffer();                                           // ���WiFi���ջ�����
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     WiFi ģ�� ���ͺ���
// ����˵��     buff            ��Ҫ���͵����ݵ�ַ
// ����˵��     len             ���ͳ���
// ���ز���     uint16          ʣ��δ�������ݳ���
// ʹ��ʾ��     wifi_uart_send_buffer("123", 3);
// ��ע��Ϣ     ��ģ����ΪTCP������ʱ���������ݺ���Ĭ�Ͻ����ݷ�������һ������ģ��Ŀͻ���
//-------------------------------------------------------------------------------------------------------------------
uint32 wifi_uart_send_buffer (uint8 *buff, uint32 len)
{
    zf_assert(buff != NULL);
    int32 timeout = WAIT_TIME_OUT;

    char lenth[32] = {0};

    if(wifi_uart_information.wifi_uart_connect_state == WIFI_UART_SERVER_ON)
    {
        if(wifi_uart_information.wifi_uart_transfer_mode == WIFI_UART_COMMAND)
        {
            wifi_uart_clear_receive_buffer();                                   // ���WiFi���ջ�����

            func_int_to_str(lenth,len);
            if(len > 8192)
            {
                uart_write_string(WIFI_UART_INDEX, "AT+CIPSENDL=");
            }
            else
            {
                uart_write_string(WIFI_UART_INDEX, "AT+CIPSEND=");
            }
            if(wifi_uart_information.wifi_uart_connect_mode == WIFI_UART_TCP_SERVER)
            {
                uart_write_string(WIFI_UART_INDEX, "0,");
            }

            uart_write_string(WIFI_UART_INDEX, lenth);
            uart_write_string(WIFI_UART_INDEX, "\r\n");

            if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT) == 0)                    // �ȴ�ģ����Ӧ
            {
                wifi_uart_clear_receive_buffer();                               // ���WiFi���ջ�����
                uart_write_buffer(WIFI_UART_INDEX, buff, len);
                if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT) == 0)                // �ȴ�ģ����Ӧ
                {
                    len = 0;
                }
            }

        }
        else
        {
            while(len--)
            {
                while(gpio_get_level(WIFI_UART_RTS_PIN) && 0 < timeout -- );    // ���RTSΪ�͵�ƽ����������
                if(0 >= timeout)
                {
                    break;
                }
                uart_write_byte(WIFI_UART_INDEX, *buff);                        // ������������
                buff ++;
            }
        }
    }
    wifi_uart_clear_receive_buffer();                                           // ���WiFi���ջ�����
    return len;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     WiFi ģ����Ϊ TCP ������ ��ָ��Ŀ���豸���ͺ���
// ����˵��     buff            ��Ҫ���͵����ݵ�ַ
// ����˵��     len             ���ͳ���
// ����˵��     id              Ŀ�� client id
// ���ز���     uint16          ʣ��δ�������ݳ���
// ʹ��ʾ��     wifi_uart_tcp_servers_send_buffer("123", 3, WIFI_UART_LINK_0);
// ��ע��Ϣ     ��ģ����ΪTCP������ʱ���������ݺ���Ĭ�Ͻ����ݷ�������һ������ģ��Ŀͻ���
//-------------------------------------------------------------------------------------------------------------------
uint32 wifi_uart_tcp_servers_send_buffer (uint8 *buff, uint32 len, wifi_uart_link_id_enum id)
{
    zf_assert(buff != NULL);
    char lenth[32] = {0};

    if( wifi_uart_information.wifi_uart_transfer_mode == WIFI_UART_COMMAND && \
        wifi_uart_information.wifi_uart_connect_mode == WIFI_UART_TCP_SERVER)
    {
        wifi_uart_clear_receive_buffer();                                       // ���WiFi���ջ�����

        func_int_to_str(lenth,len);
        if(len > 8192)
        {
            uart_write_string(WIFI_UART_INDEX, "AT+CIPSENDL=");
        }
        else
        {
            uart_write_string(WIFI_UART_INDEX, "AT+CIPSEND=");
        }
        
        uart_write_byte(WIFI_UART_INDEX, (id + '0'));
        uart_write_string(WIFI_UART_INDEX, ",");

        uart_write_string(WIFI_UART_INDEX, lenth);
        uart_write_string(WIFI_UART_INDEX, "\r\n");

        if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT) == 0)                        // �ȴ�ģ����Ӧ
        {
            // ģ������������
            wifi_uart_clear_receive_buffer();                                   // ���WiFi���ջ�����
            uart_write_buffer(WIFI_UART_INDEX, buff, len);
            if(wifi_uart_wait_ack("OK", WAIT_TIME_OUT) == 0)                    // �ȴ�ģ����Ӧ
            {
                len = 0;
            }
        }
    }
    wifi_uart_clear_receive_buffer();                                           // ���WiFi���ջ�����
    return len;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     WiFi ģ�����ݽ��պ���
// ����˵��     buffer          �������ݵĴ�ŵ�ַ
// ����˵��     len             ���鳤�ȣ���ֱ����д����ʹ��sizeof���
// ���ز���     uint16          ����ʵ�ʽ��յ������ݳ���
// ʹ��ʾ��     uint8 test_buffer[256]; wifi_uart_read_buffer(&test_buffer[0], sizeof(test_buffer));
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint16 wifi_uart_read_buffer (uint8 *buffer, uint16 len)
{
    zf_assert(buffer != NULL);
    uint32 read_len = len;
    fifo_read_buffer(&wifi_uart_fifo, buffer, &read_len, FIFO_READ_AND_CLEAN);
    return read_len;
}

//--------------------------------------------------------------------------------------------------
// �������     WiFi ���ڻص�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     wireless_uart_callback();
// ��ע��Ϣ     �ú����� ISR �ļ� �����жϳ��򱻵���
//              �ɴ����жϷ��������� wireless_module_uart_handler() ����
//              ���� wireless_module_uart_handler() �������ñ�����
//--------------------------------------------------------------------------------------------------
void wifi_uart_callback (void)
{
    uart_query_byte(WIFI_UART_INDEX, &wifi_uart_data);                          // ��ȡ��������
    fifo_write_buffer(&wifi_uart_fifo, &wifi_uart_data, 1);                     // ���� FIFO
}

//-------------------------------------------------------------------------------------------------------------------
// �������     WiFi ģ���ʼ��
// ����˵��     *wifi_ssid      Ŀ�����ӵ� WiFi ������ �ַ�����ʽ
// ����˵��     *pass_word      Ŀ�����ӵ� WiFi ������ �ַ�����ʽ
// ����˵��     wifi_mode       ģ��Ĺ���ģʽ ���� zf_device_wrieless_uart.h �� wifi_uart_mode_enum ö��
// ���ز���     uint8           ģ���ʼ��״̬ 0-�ɹ� 1-����
// ʹ��ʾ��     wifi_uart_init("SEEKFREE_2.4G", "SEEKFREEV2", WIFI_UART_STATION);
// ��ע��Ϣ     ��ʼ�����������ô������ã�֮����ģ����л�����������
//              �����������Ϣ������ zf_device_wrieless_uart.h �ļ����޸�
//-------------------------------------------------------------------------------------------------------------------
uint8 wifi_uart_init (char *wifi_ssid, char *pass_word, wifi_uart_mode_enum wifi_mode)
{
    zf_assert(wifi_ssid != NULL);
    zf_assert(pass_word != NULL);
    char uart_baud[32] = {0};
    uint8 return_state = 0;

    // ����ģ������
    set_wireless_type(WIFI_UART, wifi_uart_callback);
    fifo_init(&wifi_uart_fifo, FIFO_DATA_8BIT, wifi_uart_buffer, WIFI_UART_BUFFER_SIZE);
    gpio_init(WIFI_UART_RTS_PIN, GPI, 0, GPI_PULL_UP);                          // ��ʼ����������
#if WIFI_UART_HARDWARE_RST
    gpio_init(WIFI_UART_RST_PIN, GPO, 1, GPO_PUSH_PULL);                        // ��ʼ����λ����
#endif
    uart_init(WIFI_UART_INDEX, 115200, WIFI_UART_RX_PIN, WIFI_UART_TX_PIN);     // ��ʼ��WiFiģ����ʹ�õĴ���
    uart_rx_interrupt(WIFI_UART_INDEX, 1);
    do
    {
        if(wifi_uart_reset())                                                   // ����ģ��
        {
            // ���һ�� RST ���ŵ�����
            // ���û�н� RST ������������Ӳ����λ
            // �ͻ�һֱ����
            // ���������Ӳ����λ ʹ�������λ
            // ���������޷���λ�Ļ��Ͷϵ�����һ��
            zf_log(0, "reset failed");
            return_state = 1;
            break;
        }
        func_int_to_str(uart_baud, WIFI_UART_BAUD);                             // ����WiFiģ����ʹ�õĲ����ʲ���
        if(wifi_uart_uart_config_set(uart_baud, "8", "1", "0", "1"))            // ���ýӿ�����ģ��Ĺ������ڲ���
        {
            zf_log(0, "set config failed");
            return_state = 1;
            break;
        }
        // ���³�ʼ��WiFiģ����ʹ�õĴ���
        uart_init(WIFI_UART_INDEX, WIFI_UART_BAUD, WIFI_UART_RX_PIN, WIFI_UART_TX_PIN);
        uart_rx_interrupt(WIFI_UART_INDEX, 1);
        system_delay_ms(100);
        
        if(wifi_uart_echo_set("0"))                                             // �ر�ģ���д
        {
            zf_log(0, "exit echo failed");
            return_state = 1;
            break;
        }

        if(wifi_uart_auto_connect_wifi("0"))                                    // �ر��Զ�����
        {
            zf_log(0, "close auto connect failed");
            return_state = 1;
            break;
        }

        if(wifi_uart_set_model(wifi_mode))                                      // ��������ģʽ
        {
            zf_log(0, "set run mode failed");
            return_state = 1;
            break;
        }

        if(wifi_uart_set_wifi((char *)wifi_ssid, (char *)pass_word))            // ���� wifi ���߿����ȵ�
        {
            zf_log(0, "wifi set failed");
            return_state = 1;
            break;
        }

        if(wifi_uart_get_information())                                         // ģ�����������ȡ
        {
            zf_log(0, "get module information failed");
            return_state = 1;
            break;
        }
        // zf_log(0, "seekfree wifi uart init succeed");
#if WIFI_UART_AUTO_CONNECT == 1
        if(wifi_uart_connect_tcp_servers(WIFI_UART_TARGET_IP, WIFI_UART_TARGET_PORT,WIFI_UART_COMMAND))                         // ����TCP������
        {
            zf_log(0, "connect TCP server failed");
            return_state = 1;
            break;
        }
        // zf_log(0, "connect TCP client succeed");
#endif
#if WIFI_UART_AUTO_CONNECT == 2
        if(wifi_uart_connect_udp_transfer(WIFI_UART_TARGET_IP, WIFI_UART_TARGET_PORT, WIFI_UART_MINE_PORT, WIFI_UART_SERIANET)) // ����UDP����
        {
            zf_log(0, "connect UDP server failed");
            return_state = 1;
            break;
        }
        // zf_log(0, "connect UDP server succeed");
#endif
#if WIFI_UART_AUTO_CONNECT == 3
        if(wifi_uart_creat_tcp_servers(WIFI_UART_MINE_PORT))                                                                    // ����TCP������
        {
            zf_log(0, "build TCP server failed");
            return_state = 1;
            break;
        }
        // zf_log(0, "build TCP server succeed");
#endif
    }while(0);
    
    wifi_uart_clear_receive_buffer();                                           // ���WiFi���ջ�����

    return return_state;
}
