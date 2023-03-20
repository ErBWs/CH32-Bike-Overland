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
* �ļ�����          zf_device_camera
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2021-12-02        ��W            ���Ӵ��ڷ���ͼ����λ������
* 2022-09-15        ��W            first version
********************************************************************************************************************/


#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "zf_driver_exti.h"
#include "zf_driver_timer.h"
#include "zf_device_type.h"
#include "zf_device_mt9v03x_dvp.h"
#include "zf_device_scc8660_dvp.h"

#include "zf_device_camera.h"


fifo_struct camera_receiver_fifo;
uint8 camera_receiver_buffer[CAMERA_RECEIVER_BUFFER_SIZE];

uint8 camera_send_image_frame_header[4] = {0x00, 0xFF, 0x01, 0x01};



//-------------------------------------------------------------------------------------------------------------------
// �������     ����ͷ������ͼ�����ݽ�ѹΪʮ�����ư�λ���� С�����
// ����˵��     *data1          ����ͷͼ������
// ����˵��     *data2          ��Ž�ѹ���ݵĵ�ַ
// ����˵��     image_size      ͼ��Ĵ�С
// ���ز���     void
// ʹ��ʾ��     camera_binary_image_decompression(&ov7725_image_binary[0][0], &data_buffer[0][0], OV7725_SIZE);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void camera_binary_image_decompression (const uint8 *data1, uint8 *data2, uint32 image_size)
{
    zf_assert(data1 != NULL);
    zf_assert(data2 != NULL);
    uint8  i = 8;

    while(image_size --)
    {
        i = 8;
        while(i --)
        {
            *data2 ++ = (((*data1 >> i) & 0x01) ? 255 : 0);
        }
        data1 ++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ͷͼ��������λ���鿴ͼ��
// ����˵��     uartn           ʹ�õĴ��ں�
// ����˵��     *image_addr     ��Ҫ���͵�ͼ���ַ
// ����˵��     image_size      ͼ��Ĵ�С
// ���ز���     void
// ʹ��ʾ��     camera_send_image(DEBUG_UART_INDEX, &mt9v03x_image[0][0], MT9V03X_IMAGE_SIZE);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void camera_send_image (uart_index_enum uartn, const uint8 *image_addr, uint32 image_size)
{
    zf_assert(image_addr != NULL);
    // ��������
    uart_write_buffer(uartn, camera_send_image_frame_header, 4);

    // ����ͼ��
    uart_write_buffer(uartn, (uint8 *)image_addr, image_size);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ͷ���� FIFO ��ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     camera_fifo_init();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void camera_fifo_init (void)
{
    fifo_init(&camera_receiver_fifo, FIFO_DATA_8BIT, camera_receiver_buffer, CAMERA_RECEIVER_BUFFER_SIZE);
}

