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
* �ļ�����          zf_device_absolute_encoder
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
* ���߶���:
*                   ------------------------------------
*                   ģ��ܽ�                  ��Ƭ���ܽ�
*                   SCLK        �鿴 zf_device_absolute_encoder.h �� ABSOLUTE_ENCODER_SCLK_PIN �궨��
*                   MOSI        �鿴 zf_device_absolute_encoder.h �� ABSOLUTE_ENCODER_MOSI_PIN �궨��
*                   MISO        �鿴 zf_device_absolute_encoder.h �� ABSOLUTE_ENCODER_MISO_PIN �궨��
*                   CS          �鿴 zf_device_absolute_encoder.h �� ABSOLUTE_ENCODER_CS_PIN   �궨��
*                   VCC         3.3V��Դ
*                   GND         ��Դ��
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_function.h"
#include "zf_driver_delay.h"
#include "zf_driver_soft_spi.h"
#include "zf_driver_spi.h"

#include "zf_device_absolute_encoder.h"

static int16 now_location = 0;
static int16 last_location = 0;

#if ABSOLUTE_ENCODER_USE_SOFT_SPI
static soft_spi_info_struct                 absolute_encoder_spi;
#define absolute_encoder_read()             (soft_spi_read_8bit(&absolute_encoder_spi))
#define absolute_encoder_write(data)        (soft_spi_write_8bit(&absolute_encoder_spi, (data)))
#else
#define absolute_encoder_read()             (spi_read_8bit(ABSOLUTE_ENCODER_SPI))
#define absolute_encoder_write(data)        (spi_write_8bit(ABSOLUTE_ENCODER_SPI, (data)))
#endif

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ֵ������д�Ĵ���
// ����˵��     reg             �Ĵ�����ַ
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     absolute_encoder_write_register(i + 1, dat[i]);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void absolute_encoder_write_register(uint8 reg, uint8 data)
{
    ABSOLUTE_ENCODER_CSN(0);                                                    // Ƭѡ����ѡ��
    absolute_encoder_write(reg | ABSOLUTE_ENCODER_SPI_W);                       // �Ĵ���
    absolute_encoder_write(data);                                               // ����
    ABSOLUTE_ENCODER_CSN(1);                                                    // Ƭѡ�����ͷ�
    system_delay_us(1);                                                         // ��Ҫ����
    ABSOLUTE_ENCODER_CSN(0);                                                    // Ƭѡ����ѡ��
    absolute_encoder_read();                                                    // ����᷵��д���Ƿ�ɹ� �������ж�
    absolute_encoder_read();                                                    // ��Ҫ����
    ABSOLUTE_ENCODER_CSN(1);                                                    // Ƭѡ�����ͷ�
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ֵ���������Ĵ��� �ڲ�����
// ����˵��     reg             �Ĵ�����ַ
// ���ز���     uint8           ����
// ʹ��ʾ��     absolute_encoder_read_register(6);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8 absolute_encoder_read_register(uint8 reg)
{
    uint8 data = 0;
    ABSOLUTE_ENCODER_CSN(0);                                                    // Ƭѡ����ѡ��
    absolute_encoder_write(reg | ABSOLUTE_ENCODER_SPI_R);                       // �Ĵ���
    absolute_encoder_write(0x00);                                               // ռλ
    ABSOLUTE_ENCODER_CSN(1);                                                    // Ƭѡ�����ͷ�
    system_delay_us(1);                                                         // ��Ҫ����
    ABSOLUTE_ENCODER_CSN(0);                                                    // Ƭѡ����ѡ��
    data = absolute_encoder_read();                                             // ��ȡ��ȡ������
    absolute_encoder_read();                                                    // ��Ҫ����
    ABSOLUTE_ENCODER_CSN(1);                                                    // Ƭѡ�����ͷ�
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ֵ��������λ�� �ڲ�����
// ����˵��     void
// ���ز���     uint16          λ��ֵ
// ʹ��ʾ��     absolute_encoder_read_data();
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint16 absolute_encoder_read_data (void)
{
    uint16 data = 0;
    ABSOLUTE_ENCODER_CSN(0);                                                    // Ƭѡ����ѡ��
    data = absolute_encoder_read();                                             // ��ȡ�߰�λ����
    data = (data & 0x00FF) << 8;                                                // ����λ��
    data |= absolute_encoder_read();                                            // ��ȡ�Ͱ�λ����
    ABSOLUTE_ENCODER_CSN(1);                                                    // Ƭѡ�����ͷ�
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ֵ�������Լ� �ڲ�����
// ����˵��     void
// ���ز���     uint8           �Լ�״̬
// ʹ��ʾ��     absolute_encoder_self_check();
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8 absolute_encoder_self_check (void)
{
    uint8 i = 0, return_state = 0;
    uint8 dat[6] = {0, 0, 0, 0xC0, 0xFF, 0x1C};
    uint16 time_count = 0;
    while(0x1C != absolute_encoder_read_register(6))                            // ��ȡ״̬�Ĵ���
    {
        for(i = 0; i < 6; i ++)
        {
            absolute_encoder_write_register(i + 1, dat[i]);                     // д��Ĭ�����ò���
            system_delay_ms(1);
        }
        if(time_count ++ > ABSOLUTE_ENCODER_TIMEOUT_COUNT)                      // �ȴ���ʱ
        {
            return_state = 1;
            break;
        }
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ֵ��������ȡ��ǰ�Ƕ�ֵ
// ����˵��     void
// ���ز���     int16           �Ƕ�ֵ
// ʹ��ʾ��     absolute_encoder_get_location();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
int16 absolute_encoder_get_location (void)
{
    last_location = now_location;
    now_location = absolute_encoder_read_data() >> 4;
    return now_location;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ֵ��������ȡ����ϴ�λ�õ�ƫ��ֵ
// ����˵��     void
// ���ز���     int16           ƫ��ֵ
// ʹ��ʾ��     absolute_encoder_get_offset();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
int16 absolute_encoder_get_offset (void)
{
    int16 result_data = 0;
    if(func_abs(now_location - last_location) > 2048)
    {
        result_data = (now_location > 2048 ? (now_location - 4096 - last_location) : (now_location + 4096 - last_location));
    }
    else
    {
        result_data = (now_location - last_location);
    }
    return result_data;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ֵ��������ʼ��
// ����˵��     void
// ���ز���     uint8           ��ʼ��״̬ 0-�ɹ� 1-ʧ��
// ʹ��ʾ��     absolute_encoder_init();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint8 absolute_encoder_init (void)
{
    uint8 return_state = 0;
    uint16 zero_position = ABSOLUTE_ENCODER_DEFAULT_ZERO;
#if ABSOLUTE_ENCODER_USE_SOFT_SPI
    soft_spi_init(&absolute_encoder_spi, 0, ABSOLUTE_ENCODER_SOFT_SPI_DELAY, ABSOLUTE_ENCODER_SCLK_PIN, ABSOLUTE_ENCODER_MOSI_PIN, ABSOLUTE_ENCODER_MISO_PIN, SOFT_SPI_PIN_NULL);
#else
    spi_init(ABSOLUTE_ENCODER_SPI, SPI_MODE0, ABSOLUTE_ENCODER_SPI_SPEED, ABSOLUTE_ENCODER_SCLK_PIN, ABSOLUTE_ENCODER_MOSI_PIN, ABSOLUTE_ENCODER_MISO_PIN, SPI_CS_NULL);
#endif
    gpio_init(ABSOLUTE_ENCODER_CS_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);

    do
    {
        if(absolute_encoder_self_check())
        {
            // �������������˶�����Ϣ ������ʾ����λ��������
            // ��ô���Ǿ���ֵ�������Լ������ʱ�˳���
            // ���һ�½�����û������ ���û������ܾ��ǻ���
            return_state = 1;
            zf_log(0, "absolute encoder init errror.");
            break;
        }
        absolute_encoder_write_register(ABSOLUTE_ENCODER_DIR_REG, 0x00);                    // ������ת���� ��ת��ֵ��С��0x00   ��ת��ֵ���0x80
        zero_position = (uint16)(4096 - zero_position);
        zero_position = zero_position << 4;
        absolute_encoder_write_register(ABSOLUTE_ENCODER_ZERO_L_REG, (uint8)zero_position); // ������λ
        absolute_encoder_write_register(ABSOLUTE_ENCODER_ZERO_H_REG, zero_position >> 8);
    }while(0);
    return return_state;
}

