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
* �ļ�����          zf_device_scc8660_dvp_dvp
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
*���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   TXD                 �鿴 zf_device_scc8660_dvp.h �� SCC8660_COF_UART_TX        �궨��
*                   RXD                 �鿴 zf_device_scc8660_dvp.h �� SCC8660_COF_UART_RX        �궨��
*                   D0                  �鿴 zf_device_scc8660_dvp.h �� SCC8660_D0_PIN             �궨��
*                   D1                  �鿴 zf_device_scc8660_dvp.h �� SCC8660_D1_PIN             �궨��
*                   D2                  �鿴 zf_device_scc8660_dvp.h �� SCC8660_D2_PIN             �궨��
*                   D3                  �鿴 zf_device_scc8660_dvp.h �� SCC8660_D3_PIN             �궨��
*                   D4                  �鿴 zf_device_scc8660_dvp.h �� SCC8660_D4_PIN             �궨��
*                   D5                  �鿴 zf_device_scc8660_dvp.h �� SCC8660_D5_PIN             �궨��
*                   D6                  �鿴 zf_device_scc8660_dvp.h �� SCC8660_D6_PIN             �궨��
*                   D7                  �鿴 zf_device_scc8660_dvp.h �� SCC8660_D7_PIN             �궨��
*                   PCLK                �鿴 zf_device_scc8660_dvp.h �� SCC8660_PCLK_PIN           �궨��
*                   VSYNC               �鿴 zf_device_scc8660_dvp.h �� SCC8660_VSY_PIN            �궨��
*                   HSYNC               �鿴 zf_device_scc8660_dvp.h �� SCC8660_HERF_PIN           �궨��
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_device_type.h"
#include "zf_device_camera.h"
#include "zf_driver_dvp.h"
#include "zf_driver_delay.h"
#include "zf_device_scc8660_dvp.h"

vuint8 scc8660_finish_flag = 0;                                                  // һ��ͼ��ɼ���ɱ�־λ
uint16 scc8660_image[SCC8660_H][SCC8660_W];

// ��Ҫ���õ�����ͷ������ �����������޸Ĳ���
static int16 scc8660_set_confing_buffer[SCC8660_CONFIG_FINISH][2]=
{
    {SCC8660_INIT,              0},                                             // ����ͷ��ʼ��ʼ��
    {SCC8660_AUTO_EXP,          SCC8660_AUTO_EXP_DEF},                          // �Զ��ع�
    {SCC8660_BRIGHT,            SCC8660_BRIGHT_DEF},                            // ��������
    {SCC8660_FPS,               SCC8660_FPS_DEF},                               // ͼ��֡��
    {SCC8660_SET_COL,           SCC8660_W},                                     // ͼ������
    {SCC8660_SET_ROW,           SCC8660_H},                                     // ͼ������
    {SCC8660_PCLK_DIV,          SCC8660_PCLK_DIV_DEF},                          // PCLK��Ƶϵ��
    {SCC8660_PCLK_MODE,         SCC8660_PCLK_MODE_DEF},                         // PCLKģʽ
    {SCC8660_COLOR_MODE,        SCC8660_COLOR_MODE_DEF},                        // ͼ��ɫ��ģʽ
    {SCC8660_DATA_FORMAT,       SCC8660_DATA_FORMAT_DEF},                       // ������ݸ�ʽ
    {SCC8660_MANUAL_WB,         SCC8660_MANUAL_WB_DEF},                         // �ֶ���ƽ��

};

// ������ͷ�ڲ���ȡ������������ �����������޸Ĳ���
static int16 scc8660_get_confing_buffer[SCC8660_CONFIG_FINISH - 1][2]=
{
    {SCC8660_AUTO_EXP,          0},
    {SCC8660_BRIGHT,            0},                                             // ��������
    {SCC8660_FPS,               0},                                             // ͼ��֡��
    {SCC8660_SET_COL,           0},                                             // ͼ������
    {SCC8660_SET_ROW,           0},                                             // ͼ������
    {SCC8660_PCLK_DIV,          0},                                             // PCLK��Ƶϵ��
    {SCC8660_PCLK_MODE,         0},                                             // PCLKģʽ
    {SCC8660_COLOR_MODE,        0},                                             // ͼ��ɫ��ģʽ
    {SCC8660_DATA_FORMAT,       0},                                             // ������ݸ�ʽ
    {SCC8660_MANUAL_WB,         0},                                             // ��ƽ������
};

//-------------------------------------------------------------------------------------------------------------------
// �������     ��������ͷ�ڲ�������Ϣ �ڲ�����
// ����˵��     buff            ����������Ϣ�ĵ�ַ
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     if(scc8660_set_config(scc8660_set_confing_buffer)){}
// ��ע��Ϣ     ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
static uint8 scc8660_set_config (int16 buff[SCC8660_CONFIG_FINISH][2])
{
    uint8 return_state = 1;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 loop_count = 0;
    uint32 uart_buffer_index = 0;

    // ���ò���  ������ο���������ֲ�
    // ��ʼ��������ͷ�����³�ʼ��
    for(loop_count = SCC8660_MANUAL_WB; loop_count < SCC8660_SET_REG_DATA; loop_count --)
    {
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = buff[loop_count][0];
        temp = buff[loop_count][1];
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;
        uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

        system_delay_ms(2);
    }

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            if((0xff == uart_buffer[1]) || (0xff == uart_buffer[2]))
            {
                return_state = 0;
                break;
            }
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);

    // ���ϲ��ֶ�����ͷ���õ�����ȫ�����ᱣ��������ͷ��51��Ƭ����eeprom��
    // ����set_exposure_time�����������õ��ع����ݲ��洢��eeprom��
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ����ͷ�ڲ�������Ϣ �ڲ�����
// ����˵��     buff            ����������Ϣ�ĵ�ַ
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     if(scc8660_get_config(scc8660_get_confing_buffer)){}
// ��ע��Ϣ     ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
static uint8 scc8660_get_config (int16 buff[SCC8660_CONFIG_FINISH-1][2])
{
    uint8 return_state = 0;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 loop_count = 0;
    uint32 uart_buffer_index = 0;

    for(loop_count = SCC8660_MANUAL_WB - 1; loop_count >= 1; loop_count --)
    {
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = SCC8660_GET_STATUS;
        temp = buff[loop_count][0];
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;
        uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

        timeout_count = 0;
        do
        {
            if(3 <= fifo_used(&camera_receiver_fifo))
            {
                uart_buffer_index = 3;
                fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
                buff[loop_count][1] = uart_buffer[1] << 8 | uart_buffer[2];
                break;
            }
            system_delay_ms(1);
        }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
        if(timeout_count > SCC8660_INIT_TIMEOUT)                                // ��ʱ
        {
            return_state = 1;
            break;
        }
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     SCC8660 ͨ�Ŵ��ڻص�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     scc8660_uart_handler();
// ��ע��Ϣ     ͨ�� zf_device_type.c �Ľӿڵ��� �û���ʹ��Ĭ������ʱ����Ҫ����
//-------------------------------------------------------------------------------------------------------------------
static void scc8660_uart_handler (void)
{
    uint8 data = 0;
    uart_query_byte(SCC8660_COF_UART, &data);
    if(0xA5 == data)
    {
        fifo_clear(&camera_receiver_fifo);
    }
    fifo_write_element(&camera_receiver_fifo, data);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     SCC8660 ���жϻص�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     scc8660_vsync_handler();
// ��ע��Ϣ     ͨ�� zf_device_type.c �Ľӿڵ��� �û���ʹ��Ĭ������ʱ����Ҫ����
//-------------------------------------------------------------------------------------------------------------------
static void scc8660_dvp_handler (void)
{
    //�Ѿ��޸�Ϊѭ���ɼ�ģʽ������Ҫ���õ�ַ�Ϳ���DVP
    //DVP->DMA_BUF0 = (uint32)camera_buffer_addr;       // �ָ�DMA��ַ
    scc8660_finish_flag = 1;                            // ����ͷ�ɼ���ɱ�־λ��1
    //�Ѿ��޸�Ϊѭ���ɼ�ģʽ������Ҫ���õ�ַ�Ϳ���DVP
    //DVP->CR0 |= RB_ENABLE;                            // ���´�DVP���ɼ���һ��ͼ��
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ����ͷ ID
// ����˵��     void
// ���ز���     uint16          0-��ȡ���� N-�汾��
// ʹ��ʾ��     scc8660_get_id();                               // ���øú���ǰ���ȳ�ʼ������
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_get_id (void)
{
    uint16 temp;
    uint8  uart_buffer[4];
    uint16 timeout_count = 0;
    uint16 return_value = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_GET_WHO_AM_I;
    temp = 0;
    uart_buffer[2] = temp >> 8;
    uart_buffer[3] = (uint8)temp;
    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            return_value = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������������ͷ�ع�ʱ��
// ����˵��     light           �����ع�ʱ��Խ��ͼ��Խ��������ͷ�յ������ݷֱ��ʼ�FPS��������ع�ʱ��������õ����ݹ�����ô����ͷ��������������ֵ
// ���ز���     uint16          ����
// ʹ��ʾ��     scc8660_get_parameter(config);                                  // ���øú���ǰ���ȳ�ʼ������
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_get_parameter (uint16 config)
{
    uint8  uart_buffer[4];
    uint16 timeout_count = 0;
    uint16 return_value = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_GET_WHO_AM_I;
    uart_buffer[2] = 0x00;
    uart_buffer[3] = config;
    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            return_value = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ��ɫ����ͷ�̼��汾
// ����˵��     void
// ���ز���     uint16          �汾��
// ʹ��ʾ��     scc8660_get_version();                                          // ���øú���ǰ���ȳ�ʼ������ͷ���ô���
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_get_version (void)
{
    uint16 temp;
    uint8  uart_buffer[4];
    uint16 timeout_count = 0;
    uint16 return_value = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_GET_STATUS;
    temp           = SCC8660_GET_VERSION;
    uart_buffer[2] = temp >> 8;
    uart_buffer[3] = (uint8)temp;

    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            return_value = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��������ͼ������
// ����˵��     data            ��Ҫ���õ�����ֵ
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     scc8660_set_bright(data);                                       // ͨ���ú������õĲ��������ᱻ51��Ƭ������
// ��ע��Ϣ     ���øú���ǰ���ȳ�ʼ������ͷ���ô���
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_set_bright (uint16 data)
{
    uint8 return_state = 0;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_SET_BRIGHT;
    uart_buffer[2] = data >> 8;
    uart_buffer[3] = (uint8)data;

    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            temp = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
    if((temp != data) || (SCC8660_INIT_TIMEOUT <= timeout_count))
    {
        return_state = 1;
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �������ð�ƽ��
// ����˵��     data            ��Ҫ���õ�����ֵ
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     scc8660_set_white_balance(data);                // ���øú���ǰ���ȳ�ʼ������ͷ���ô���
// ��ע��Ϣ     ͨ���ú������õĲ��������ᱻ51��Ƭ������
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_set_white_balance (uint16 data)
{
    uint8 return_state = 0;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_SET_MANUAL_WB;
    uart_buffer[2] = data >> 8;
    uart_buffer[3] = (uint8)data;

    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            temp = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
    if((temp != data) || (SCC8660_INIT_TIMEOUT <= timeout_count))
    {
        return_state = 1;
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ͷ�ڲ��Ĵ�������д����
// ����˵��     addr            ����ͷ�ڲ��Ĵ�����ַ
// ����˵��     data            ��Ҫд�������
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     scc8660_set_reg(addr, data);                    // ���øú���ǰ���ȳ�ʼ������
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_set_reg (uint8 addr, uint16 data)
{
    uint8 return_state = 0;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_SET_REG_ADDR;
    uart_buffer[2] = 0x00;
    uart_buffer[3] = (uint8)addr;
    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    system_delay_ms(10);
    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_SET_REG_DATA;
    temp           = data;
    uart_buffer[2] = temp >> 8;
    uart_buffer[3] = (uint8)temp;
    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            temp = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
    if((temp != data) || (SCC8660_INIT_TIMEOUT <= timeout_count))
    {
        return_state = 1;
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     SCC8660(��ͫ����ͷ)��ʼ�� ʹ��DVP�ӿ�
// ����˵��     NULL
// ���ز���     void
//  @since      v1.0
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_init(void)
{

    uint8 return_state = 0;

    // ��ʼ������ ��������ͷ
    uart_init(SCC8660_COF_UART, SCC8660_COF_BAUR, SCC8660_COF_UART_RX, SCC8660_COF_UART_TX);
    uart_rx_interrupt(SCC8660_COF_UART, 1);
    system_delay_ms(200);

    set_camera_type(CAMERA_COLOR, scc8660_uart_handler, scc8660_dvp_handler);
    camera_fifo_init();

    // �ȴ�����ͷ�ϵ��ʼ���ɹ� ��ʽ�����֣���ʱ����ͨ����ȡ���õķ�ʽ ��ѡһ
    // system_delay_ms(1000);                                                   // ��ʱ��ʽ

//    if(scc8660_set_config(scc8660_set_confing_buffer))
//    {
//        set_camera_type(NO_CAMERE, NULL, NULL, NULL);
//        return 1;
//    }
    scc8660_get_version();                                                      // ��ȡ���õķ�ʽ

    do
    {
        if(scc8660_set_config(scc8660_set_confing_buffer))
        {
            // �������������˶�����Ϣ ������ʾ����λ��������
            // ��ô���Ǵ���ͨ�ų�����ʱ�˳���
            // ���һ�½�����û������ ���û������ܾ��ǻ���
            zf_log(0, "SCC8660 set config error.");
            set_camera_type(NO_CAMERE, NULL, NULL);
            return_state = 1;
            break;
        }

        // ��ȡ���ñ��ڲ鿴�����Ƿ���ȷ
        if(scc8660_get_config(scc8660_get_confing_buffer))
        {
            // �������������˶�����Ϣ ������ʾ����λ��������
            // ��ô���Ǵ���ͨ�ų�����ʱ�˳���
            // ���һ�½�����û������ ���û������ܾ��ǻ���
            zf_log(0, "SCC8660 get config error.");
            set_camera_type(NO_CAMERE, NULL, NULL);
            return_state = 1;
            break;
        }

        // DVP���ų�ʼ��
        dvp_gpio_init(
                SCC8660_D0_PIN, SCC8660_D1_PIN, SCC8660_D2_PIN, SCC8660_D3_PIN,
                SCC8660_D4_PIN, SCC8660_D5_PIN, SCC8660_D6_PIN, SCC8660_D7_PIN,
                SCC8660_PCLK_PIN, SCC8660_VSY_PIN, SCC8660_HERF_PIN);

        // DVP�ӿڳ�ʼ��
        dvp_camera_init((uint32 *)&scc8660_image[0], NULL, SCC8660_IMAGE_SIZE, 1);
    }while(0);

    return return_state;

}

