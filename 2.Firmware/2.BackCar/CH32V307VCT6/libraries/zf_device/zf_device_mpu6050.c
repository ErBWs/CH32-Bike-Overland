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
* �ļ�����          zf_device_mpu6050
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
*                   ģ��ܽ�                                        ��Ƭ���ܽ�
*                   ��� IIC ͨ�����Ŷ�Ӧ��ϵ
*                   SCL                 �鿴 zf_device_mpu6050.h �� MPU6050_SOFT_IIC_SCL �궨��
*                   SDA                 �鿴 zf_device_mpu6050.h �� MPU6050_SOFT_IIC_SDA �궨��
*                   Ӳ�� IIC ͨ�����Ŷ�Ӧ��ϵ
*                   SCL                 �鿴 zf_device_mpu6050.h �� MPU6050_IIC_SCL �궨��
*                   SDA                 �鿴 zf_device_mpu6050.h �� MPU6050_IIC_SDA �궨��
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_device_mpu6050.h"

int16 mpu6050_gyro_x = 0, mpu6050_gyro_y = 0, mpu6050_gyro_z = 0;               // ��������������      gyro (������)
int16 mpu6050_acc_x = 0, mpu6050_acc_y = 0, mpu6050_acc_z = 0;                  // ������ٶȼ�����    acc (accelerometer ���ٶȼ�)

#if MPU6050_USE_SOFT_IIC
static soft_iic_info_struct mpu6050_iic_struct;

#define mpu6050_write_register(reg, data)       (soft_iic_write_8bit_register(&mpu6050_iic_struct, (reg), (data)))
#define mpu6050_read_register(reg)              (soft_iic_read_8bit_register(&mpu6050_iic_struct, (reg)))
#define mpu6050_read_registers(reg, data, len)  (soft_iic_read_8bit_registers(&mpu6050_iic_struct, (reg), (data), (len)))
#else
#define mpu6050_write_register(reg, data)       (iic_write_8bit_register(MPU6050_IIC, MPU6050_DEV_ADDR, (reg), (data)))
#define mpu6050_read_register(reg)              (iic_read_8bit_register(MPU6050_IIC, MPU6050_DEV_ADDR, (reg)))
#define mpu6050_read_registers(reg, data, len)  (iic_read_8bit_registers(MPU6050_IIC, MPU6050_DEV_ADDR, (reg), (data), (len)))
#endif


//-------------------------------------------------------------------------------------------------------------------
// �������     MPU6050 �Լ�
// ����˵��     void
// ���ز���     uint8           1-�Լ�ʧ�� 0-�Լ�ɹ�
// ʹ��ʾ��     if(mpu6050_self1_check())
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8 mpu6050_self1_check (void)
{
    uint8 dat = 0, return_state = 0;
    uint16 timeout_count = 0;

    mpu6050_write_register(MPU6050_PWR_MGMT_1, 0x00);                           // �������״̬
    mpu6050_write_register(MPU6050_SMPLRT_DIV, 0x07);                           // 125HZ������
    while(0x07 != dat)
    {
        if(timeout_count ++ > MPU6050_TIMEOUT_COUNT)
        {
            return_state =  1;
            break;
        }
        dat = mpu6050_read_register(MPU6050_SMPLRT_DIV);
        system_delay_ms(10);
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ MPU6050 ���ٶȼ�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     mpu6050_get_acc();                                              // ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void mpu6050_get_acc (void)
{
    uint8 dat[6];

    mpu6050_read_registers(MPU6050_ACCEL_XOUT_H, dat, 6);  
    mpu6050_acc_x = (int16)(((uint16)dat[0] << 8 | dat[1]));
    mpu6050_acc_y = (int16)(((uint16)dat[2] << 8 | dat[3]));
    mpu6050_acc_z = (int16)(((uint16)dat[4] << 8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ MPU6050 ����������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     mpu6050_get_gyro();                                             // ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void mpu6050_get_gyro (void)
{
    uint8 dat[6];

    mpu6050_read_registers(MPU6050_GYRO_XOUT_H, dat, 6);  
    mpu6050_gyro_x = (int16)(((uint16)dat[0] << 8 | dat[1]));
    mpu6050_gyro_y = (int16)(((uint16)dat[2] << 8 | dat[3]));
    mpu6050_gyro_z = (int16)(((uint16)dat[4] << 8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �� MPU6050 ���ٶȼ�����ת��Ϊʵ����������
// ����˵��     gyro_value      ������ļ��ٶȼ�����
// ���ز���     void
// ʹ��ʾ��     float data = mpu6050_acc_transition(mpu6050_acc_x);                // ��λΪ g(m/s^2)
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
float mpu6050_acc_transition (int16 acc_value)
{
    float acc_data = 0;
    switch(MPU6050_ACC_SAMPLE)
    {
        case 0x00: acc_data = (float)acc_value / 16384; break;                  // 0x00 ���ٶȼ�����Ϊ:��2g     ��ȡ���ļ��ٶȼ����� ���� 16384      ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
        case 0x08: acc_data = (float)acc_value / 8192; break;                   // 0x08 ���ٶȼ�����Ϊ:��4g     ��ȡ���ļ��ٶȼ����� ���� 8192       ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
        case 0x10: acc_data = (float)acc_value / 4096; break;                   // 0x10 ���ٶȼ�����Ϊ:��8g     ��ȡ���ļ��ٶȼ����� ���� 4096       ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
        case 0x18: acc_data = (float)acc_value / 2048; break;                   // 0x18 ���ٶȼ�����Ϊ:��16g    ��ȡ���ļ��ٶȼ����� ���� 2048       ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
        default: break;
    }
    return acc_data;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �� MPU6050 ����������ת��Ϊʵ����������
// ����˵��     gyro_value      �����������������
// ���ز���     void
// ʹ��ʾ��     float data = mpu6050_gyro_transition(mpu6050_gyro_x);           // ��λΪ��/s
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
float mpu6050_gyro_transition (int16 gyro_value)
{
    float gyro_data = 0;
    switch(MPU6050_GYR_SAMPLE)
    {
        case 0x00: gyro_data = (float)gyro_value / 131.0f;  break;              // 0x00 ����������Ϊ:��250 dps     ��ȡ�������������ݳ��� 131           ����ת��Ϊ������λ�����ݣ���λΪ����/s
        case 0x08: gyro_data = (float)gyro_value / 65.5f;   break;              // 0x08 ����������Ϊ:��500 dps     ��ȡ�������������ݳ��� 65.5          ����ת��Ϊ������λ�����ݣ���λΪ����/s
        case 0x10: gyro_data = (float)gyro_value / 32.8f;   break;              // 0x10 ����������Ϊ:��1000dps     ��ȡ�������������ݳ��� 32.8          ����ת��Ϊ������λ�����ݣ���λΪ����/s
        case 0x18: gyro_data = (float)gyro_value / 16.4f;   break;              // 0x18 ����������Ϊ:��2000dps     ��ȡ�������������ݳ��� 16.4          ����ת��Ϊ������λ�����ݣ���λΪ����/s
        default: break;
    }
    return gyro_data;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ʼ�� MPU6050
// ����˵��     void
// ���ز���     uint8           1-��ʼ��ʧ�� 0-��ʼ���ɹ�
// ʹ��ʾ��     mpu6050_init();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 mpu6050_init (void)
{
    uint8 return_state = 0;
#if MPU6050_USE_SOFT_IIC
    soft_iic_init(&mpu6050_iic_struct, MPU6050_DEV_ADDR, MPU6050_SOFT_IIC_DELAY, MPU6050_SCL_PIN, MPU6050_SDA_PIN);
#else
    iic_init(MPU6050_IIC, MPU6050_DEV_ADDR, MPU6050_IIC_SPEED, MPU6050_SCL_PIN, MPU6050_SDA_PIN);
#endif
    system_delay_ms(100);                                                       // �ϵ���ʱ

    do
    {
        if(mpu6050_self1_check())
        {
            // �������������˶�����Ϣ ������ʾ����λ��������
            // ��ô���� MPU6050 �Լ������ʱ�˳���
            // ���һ�½�����û������ ���û������ܾ��ǻ���
            zf_log(0, "MPU6050 self check error.");
            return_state = 1;
            break;
        }
        mpu6050_write_register(MPU6050_PWR_MGMT_1, 0x00);                       // �������״̬
        mpu6050_write_register(MPU6050_SMPLRT_DIV, 0x07);                       // 125HZ������
        mpu6050_write_register(MPU6050_CONFIG, 0x04);

        mpu6050_write_register(MPU6050_GYRO_CONFIG, MPU6050_GYR_SAMPLE);        // 2000
        // GYRO_CONFIG�Ĵ���
        // ����Ϊ:0x00 ����������Ϊ:��250 dps     ��ȡ�������������ݳ���131.2         ����ת��Ϊ������λ�����ݣ���λΪ����/s
        // ����Ϊ:0x08 ����������Ϊ:��500 dps     ��ȡ�������������ݳ���65.6          ����ת��Ϊ������λ�����ݣ���λΪ����/s
        // ����Ϊ:0x10 ����������Ϊ:��1000dps     ��ȡ�������������ݳ���32.8          ����ת��Ϊ������λ�����ݣ���λΪ����/s
        // ����Ϊ:0x18 ����������Ϊ:��2000dps     ��ȡ�������������ݳ���16.4          ����ת��Ϊ������λ�����ݣ���λΪ����/s

        mpu6050_write_register(MPU6050_ACCEL_CONFIG, MPU6050_ACC_SAMPLE);       // 8g
        // ACCEL_CONFIG�Ĵ���
        // ����Ϊ:0x00 ���ٶȼ�����Ϊ:��2g          ��ȡ���ļ��ٶȼ����� ����16384      ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
        // ����Ϊ:0x08 ���ٶȼ�����Ϊ:��4g          ��ȡ���ļ��ٶȼ����� ����8192       ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
        // ����Ϊ:0x10 ���ٶȼ�����Ϊ:��8g          ��ȡ���ļ��ٶȼ����� ����4096       ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
        // ����Ϊ:0x18 ���ٶȼ�����Ϊ:��16g         ��ȡ���ļ��ٶȼ����� ����2048       ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)

        mpu6050_write_register(MPU6050_USER_CONTROL, 0x00);
        mpu6050_write_register(MPU6050_INT_PIN_CFG, 0x02);
    }while(0);
    return return_state;
}
