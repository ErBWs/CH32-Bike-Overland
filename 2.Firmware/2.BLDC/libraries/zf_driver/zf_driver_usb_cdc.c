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
* �ļ�����          zf_driver_usb_cdc
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
#include "ch32v30x.h"
#include "zf_driver_delay.h"
#include "zf_driver_usb_cdc.h"



//-------------------------------------------------------------------------------------------------------------------
// �������     USB_CDC����һ�� ��
// ����˵��     *p          Ҫ���͵�����ָ��
// ����˵��     length      ���Ͷ��ٸ�����( length ��ҪС��64)
// ���ز���     void
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void cdc_send_pack(const uint8 *p, uint32 length)
{
    uint32 i = 0;

    for(i=0; i<length; i++)
    {
       pEP2_IN_DataBuf[i] = p[i];
    }
    DevEP2_IN_Deal(length);

    //�ȴ��������
    while(!(USBOTG_FS->UEP2_TX_CTRL&USBHD_UEP_T_RES1));

    // bUEP_T_RES1 & bUEP_T_RES0: handshake response type for USB endpoint X transmittal (IN)
    // 00: DATA0 or DATA1 then expecting ACK (ready)
    // 01: DATA0 or DATA1 then expecting no response, time out from host, for non-zero endpoint isochronous transactions
    // 10: NAK (busy)
    // 11: TALL (error)
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ����ͼ�����ݵ���λ��
// ����˵��     *image          ͼ������
// ����˵��     length          ���Ͷ��ٸ�����
// ���ز���     void
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void camera_send_image_usb_cdc(const uint8 *image, uint32 length)
{
    uint8 send_buffer[4] = {0x00,0xff,0x01,0x01};
    cdc_send_pack(send_buffer, 4);

    while(length)
    {
        if(length >= 63)
        {
            cdc_send_pack(image, 63);
            image += 63;
            length -= 63;
        }
        else
        {
            cdc_send_pack(image, length);
            length = 0;
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
// �������     USB�豸ȫ���豸��ʼ��
// ����˵��     void          ��
// ���ز���     void
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void usb_cdc_init( void )
{
    // �˵㻺������ʼ��
    pEP0_RAM_Addr = EP0_DatabufHD;
    pEP1_RAM_Addr = EP1_DatabufHD;
    pEP2_RAM_Addr = EP2_DatabufHD;
    // ʹ��usbʱ��
    USBOTG_RCC_Init();
    system_delay_ms(100);
    // usb�豸��ʼ��
    USBDeviceInit();
    EXTEN->EXTEN_CTR |= EXTEN_USBD_PU_EN;
    // ʹ��usb�ж�
    NVIC_EnableIRQ(OTG_FS_IRQn);
}
