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
* �ļ�����          zf_device_aht20
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
*                   ģ��ܽ�                                 ��Ƭ���ܽ�
*                   ��� IIC ͨ�����Ŷ�Ӧ��ϵ
*                   SCL                 �鿴 zf_device_aht20.h �� AHT20_SOFT_IIC_SCL �궨��
*                   SDA                 �鿴 zf_device_aht20.h �� AHT20_SOFT_IIC_SDA �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ������������
*
*                   Ӳ�� IIC ͨ�����Ŷ�Ӧ��ϵ
*                   SCL                 �鿴 zf_device_aht20.h �� AHT20_IIC_SCL �궨��
*                   SDA                 �鿴 zf_device_aht20.h �� AHT20_IIC_SDA �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_device_aht20.h"

float aht_temperature = 0, aht_humidity = 0;

#if AHT20_USE_SOFT_IIC
static soft_iic_info_struct aht20_iic_struct;

#define aht20_write_register(reg, data)         (soft_iic_write_8bit_register(&aht20_iic_struct, (reg), (data)))
#define aht20_write_registers(reg, data, len)   (soft_iic_write_8bit_registers(&aht20_iic_struct, (reg), (data), (len)))
#define aht20_read_register(reg)                (soft_iic_read_8bit_register(&aht20_iic_struct, (reg)))
#define aht20_read_registers(reg, data, len)    (soft_iic_read_8bit_registers(&aht20_iic_struct, (reg), (data), (len)))
#else
#define aht20_write_register(reg, data)         (iic_write_8bit_register(AHT20_IIC, AHT20_DEV_ADDR, (reg), (data)))
#define aht20_write_registers(reg, data, len)   (iic_write_8bit_registers(AHT20_IIC, AHT20_DEV_ADDR, (reg), (data), (len)))
#define aht20_read_register(reg)                (iic_read_8bit_register(AHT20_IIC, AHT20_DEV_ADDR, (reg)))
#define aht20_read_registers(reg, data, len)    (iic_read_8bit_registers(AHT20_IIC, AHT20_DEV_ADDR, (reg), (data), (len)))
#endif

//-------------------------------------------------------------------------------------------------------------------
// �������      AHT20 �Լ캯��
// ����˵��     NULL
// ���ز���     uint8           0 - ��ʼ���ɹ� 1 - ��ʼ��ʧ��
// ʹ��ʾ��     ���øú���ǰ�����ȵ���ģ��IIC�ĳ�ʼ��
//-------------------------------------------------------------------------------------------------------------------
static uint8 aht20_self1_check(void)
{
    uint8 return_state = 0;
    uint16 timeout_count = 0;
    uint8 send_data[2] = {0x08, 0x00};
    while((AHT20_CAL_ENABLE & aht20_read_register(AHT20_READ_STATE)) != AHT20_CAL_ENABLE)
    {
        //��������ԭ�������¼���
        //1 AHT20 ���ˣ�������µ������ĸ��ʼ���
        //2 ���ߴ������û�нӺ�
        //3 ��������Ҫ����������裬������3.3V
        aht20_write_registers(AHT20_SELF_INIT, send_data, 2);
        system_delay_ms(10);
        if(timeout_count ++ > AHT20_TIMEOUT_COUNT)
        {
            return_state =  1;
            break;
        }
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      ��ȡ AHT20 ��ʪ������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     aht20_read_data();                              // ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
//-------------------------------------------------------------------------------------------------------------------
void aht20_read_data (void)
{
    uint32 temp_data;
    uint8 data_buffer[6] = {0x33, 0x00, 0x00, 0x00, 0x00, 0x00};

    aht20_write_registers(AHT20_MEASURE_CMD, data_buffer, 2);
    system_delay_ms(75);
    data_buffer[0] = AHT20_STATE_BUSY;
    while(data_buffer[0] & aht20_read_register(AHT20_READ_STATE))
    {
        system_delay_ms(1);
    }
    aht20_read_registers(AHT20_READ_STATE, data_buffer, 6);

    temp_data = data_buffer[1];
    temp_data = (temp_data << 8) + data_buffer[2];
    temp_data = (temp_data << 4) + (data_buffer[3]>>4 & 0x0f);
    aht_humidity = ((double)temp_data/0x100000)*100;

    temp_data = (data_buffer[3] & 0x0f);
    temp_data = (temp_data << 8) + data_buffer[4];
    temp_data = (temp_data << 8) + data_buffer[5];
    aht_temperature = ((double)temp_data/0x100000)*200-50;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      ��ʼ�� AHT20
// ����˵��     NULL
// ���ز���     uint8           0 - ��ʼ���ɹ� 1 - ��ʼ��ʧ��
// ʹ��ʾ��     ���øú���ǰ�����ȵ���ģ��IIC�ĳ�ʼ��
//-------------------------------------------------------------------------------------------------------------------
uint8 aht20_init (void)
{
    uint8 return_state = 0;
#if AHT20_USE_SOFT_IIC
    soft_iic_init(&aht20_iic_struct, AHT20_DEV_ADDR, AHT20_SOFT_IIC_DELAY, AHT20_SCL_PIN, AHT20_SDA_PIN);
#else
    iic_init(AHT20_IIC, AHT20_DEV_ADDR, AHT20_IIC_SPEED, AHT20_SCL_PIN, AHT20_SDA_PIN);
#endif
    system_delay_ms(40);                                                        // �ϵ���ʱ

    return_state = aht20_self1_check();
    return return_state;
}
