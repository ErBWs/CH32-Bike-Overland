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
* �ļ�����          zf_device_icm20602
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
*                   ģ��ܽ�                                        ��Ƭ���ܽ�
*                   //------------------Ӳ�� SPI ����------------------//
*                   SCL/SPC             �鿴 zf_device_icm20602.h �� ICM20602_SPC_PIN �궨��
*                   SDA/DSI             �鿴 zf_device_icm20602.h �� ICM20602_SDI_PIN �궨��
*                   SA0/SDO             �鿴 zf_device_icm20602.h �� ICM20602_SDO_PIN �궨��
*                   CS                  �鿴 zf_device_icm20602.h �� IPS114_CS_PIN �궨��
*                   //------------------Ӳ�� SPI ����------------------//
*                   //------------------��� IIC ����------------------//
*                   SCL/SPC             �鿴 zf_device_icm20602.h �� ICM20602_SCL_PIN �궨��
*                   SDA/DSI             �鿴 zf_device_icm20602.h �� ICM20602_SDA_PIN �궨��
*                   //------------------��� IIC ����------------------//
*                   ��Դ����
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_icm20602_h_
#define _zf_device_icm20602_h_

#include "zf_common_typedef.h"


#define ICM20602_USE_SOFT_IIC       0                                           // Ĭ��ʹ��Ӳ�� SPI ��ʽ����
#if ICM20602_USE_SOFT_IIC                                                       // ������ ��ɫ�����Ĳ�����ȷ�� ��ɫ�ҵľ���û���õ�
//====================================================��� IIC ����====================================================
#define ICM20602_SOFT_IIC_DELAY     100                                         // ��� IIC ��ʱ����ʱ���� ��ֵԽС IIC ͨ������Խ��
#define ICM20602_SCL_PIN            B3                                          // ��� IIC SCL ���� ���� MPU6050 �� SCL ����
#define ICM20602_SDA_PIN            B5                                          // ��� IIC SDA ���� ���� MPU6050 �� SDA ����
//====================================================��� IIC ����====================================================
#else
//====================================================Ӳ�� SPI ����====================================================
#define ICM20602_SPI_SPEED          (10*1000*1000)                              // Ӳ�� SPI ����
#define ICM20602_SPI                SPI_3                                       // Ӳ�� SPI ��
#define ICM20602_SPC_PIN            SPI3_MAP0_SCK_B3                            // Ӳ�� SPI SCK ����
#define ICM20602_SDI_PIN            SPI3_MAP0_MOSI_B5                           // Ӳ�� SPI MOSI ����
#define ICM20602_SDO_PIN            SPI3_MAP0_MISO_B4                           // Ӳ�� SPI MISO ����
//====================================================Ӳ�� SPI ����====================================================
#endif
#define ICM20602_CS_PIN             C10                                          // CS Ƭѡ����
#define ICM20602_CS(x)              (x? (gpio_high(ICM20602_CS_PIN)): (gpio_low(ICM20602_CS_PIN)))

typedef enum
{
    ICM20602_ACC_SAMPLE_SGN_2G ,                                                // ���ٶȼ����� ��2G  (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
    ICM20602_ACC_SAMPLE_SGN_4G ,                                                // ���ٶȼ����� ��4G  (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
    ICM20602_ACC_SAMPLE_SGN_8G ,                                                // ���ٶȼ����� ��8G  (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
    ICM20602_ACC_SAMPLE_SGN_16G,                                                // ���ٶȼ����� ��16G (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
}icm20602_acc_sample_config;

typedef enum
{
    ICM20602_GYRO_SAMPLE_SGN_250DPS ,                                           // ���������� ��250DPS  (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    ICM20602_GYRO_SAMPLE_SGN_500DPS ,                                           // ���������� ��500DPS  (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    ICM20602_GYRO_SAMPLE_SGN_1000DPS,                                           // ���������� ��1000DPS (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    ICM20602_GYRO_SAMPLE_SGN_2000DPS,                                           // ���������� ��2000DPS (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
}icm20602_gyro_sample_config;

#define ICM20602_ACC_SAMPLE_DEFAULT     ( ICM20602_ACC_SAMPLE_SGN_8G )          // ��������Ĭ�ϵ� ���ٶȼ� ��ʼ������
#define ICM20602_GYRO_SAMPLE_DEFAULT    ( ICM20602_GYRO_SAMPLE_SGN_2000DPS )    // ��������Ĭ�ϵ� ������   ��ʼ������

#define ICM20602_TIMEOUT_COUNT      ( 0x00FF )                                  // ICM20602 ��ʱ����

//================================================���� ICM20602 �ڲ���ַ================================================
#define ICM20602_DEV_ADDR           ( 0x69 )                                    // SA0�ӵأ�0x68 SA0������0x69 ģ��Ĭ������
#define ICM20602_SPI_W              ( 0x00 )
#define ICM20602_SPI_R              ( 0x80 )

#define ICM20602_XG_OFFS_TC_H       ( 0x04 )
#define ICM20602_XG_OFFS_TC_L       ( 0x05 )
#define ICM20602_YG_OFFS_TC_H       ( 0x07 )
#define ICM20602_YG_OFFS_TC_L       ( 0x08 )
#define ICM20602_ZG_OFFS_TC_H       ( 0x0A )
#define ICM20602_ZG_OFFS_TC_L       ( 0x0B )
#define ICM20602_SELF_TEST_X_ACCEL  ( 0x0D )
#define ICM20602_SELF_TEST_Y_ACCEL  ( 0x0E )
#define ICM20602_SELF_TEST_Z_ACCEL  ( 0x0F )
#define ICM20602_XG_OFFS_USRH       ( 0x13 )
#define ICM20602_XG_OFFS_USRL       ( 0x14 )
#define ICM20602_YG_OFFS_USRH       ( 0x15 )
#define ICM20602_YG_OFFS_USRL       ( 0x16 )
#define ICM20602_ZG_OFFS_USRH       ( 0x17 )
#define ICM20602_ZG_OFFS_USRL       ( 0x18 )
#define ICM20602_SMPLRT_DIV         ( 0x19 )
#define ICM20602_CONFIG             ( 0x1A )
#define ICM20602_GYRO_CONFIG        ( 0x1B )
#define ICM20602_ACCEL_CONFIG       ( 0x1C )
#define ICM20602_ACCEL_CONFIG_2     ( 0x1D )
#define ICM20602_LP_MODE_CFG        ( 0x1E )
#define ICM20602_ACCEL_WOM_X_THR    ( 0x20 )
#define ICM20602_ACCEL_WOM_Y_THR    ( 0x21 )
#define ICM20602_ACCEL_WOM_Z_THR    ( 0x22 )
#define ICM20602_FIFO_EN            ( 0x23 )
#define ICM20602_FSYNC_INT          ( 0x36 )
#define ICM20602_INT_PIN_CFG        ( 0x37 )
#define ICM20602_INT_ENABLE         ( 0x38 )
#define ICM20602_FIFO_WM_INT_STATUS ( 0x39 )
#define ICM20602_INT_STATUS         ( 0x3A )
#define ICM20602_ACCEL_XOUT_H       ( 0x3B )
#define ICM20602_ACCEL_XOUT_L       ( 0x3C )
#define ICM20602_ACCEL_YOUT_H       ( 0x3D )
#define ICM20602_ACCEL_YOUT_L       ( 0x3E )
#define ICM20602_ACCEL_ZOUT_H       ( 0x3F )
#define ICM20602_ACCEL_ZOUT_L       ( 0x40 )
#define ICM20602_TEMP_OUT_H         ( 0x41 )
#define ICM20602_TEMP_OUT_L         ( 0x42 )
#define ICM20602_GYRO_XOUT_H        ( 0x43 )
#define ICM20602_GYRO_XOUT_L        ( 0x44 )
#define ICM20602_GYRO_YOUT_H        ( 0x45 )
#define ICM20602_GYRO_YOUT_L        ( 0x46 )
#define ICM20602_GYRO_ZOUT_H        ( 0x47 )
#define ICM20602_GYRO_ZOUT_L        ( 0x48 )
#define ICM20602_SELF_TEST_X_GYRO   ( 0x50 )
#define ICM20602_SELF_TEST_Y_GYRO   ( 0x51 )
#define ICM20602_SELF_TEST_Z_GYRO   ( 0x52 )
#define ICM20602_FIFO_WM_TH1        ( 0x60 )
#define ICM20602_FIFO_WM_TH2        ( 0x61 )
#define ICM20602_SIGNAL_PATH_RESET  ( 0x68 )
#define ICM20602_ACCEL_INTEL_CTRL   ( 0x69 )
#define ICM20602_USER_CTRL          ( 0x6A )
#define ICM20602_PWR_MGMT_1         ( 0x6B )
#define ICM20602_PWR_MGMT_2         ( 0x6C )
#define ICM20602_I2C_IF             ( 0x70 )
#define ICM20602_FIFO_COUNTH        ( 0x72 )
#define ICM20602_FIFO_COUNTL        ( 0x73 )
#define ICM20602_FIFO_R_W           ( 0x74 )
#define ICM20602_WHO_AM_I           ( 0x75 )
#define ICM20602_XA_OFFSET_H        ( 0x77 )
#define ICM20602_XA_OFFSET_L        ( 0x78 )
#define ICM20602_YA_OFFSET_H        ( 0x7A )
#define ICM20602_YA_OFFSET_L        ( 0x7B )
#define ICM20602_ZA_OFFSET_H        ( 0x7D )
#define ICM20602_ZA_OFFSET_L        ( 0x7E )
//================================================���� ICM20602 �ڲ���ַ================================================

extern int16 icm20602_gyro_x, icm20602_gyro_y, icm20602_gyro_z;                 // ��������������
extern int16 icm20602_acc_x, icm20602_acc_y, icm20602_acc_z;                    // ������ٶȼ�����
extern float icm20602_transition_factor[2];

void    icm20602_get_acc            (void);
void    icm20602_get_gyro           (void);

//-------------------------------------------------------------------------------------------------------------------
// �������     �� ICM20602 ���ٶȼ�����ת��Ϊʵ����������
// ����˵��     acc_value       ������ļ��ٶȼ�����
// ���ز���     void
// ʹ��ʾ��     float data = icm20602_acc_transition(icm20602_acc_x);           // ��λΪ g(m/s^2)
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
#define icm20602_acc_transition(acc_value)      ((float)acc_value / icm20602_transition_factor[0])

//-------------------------------------------------------------------------------------------------------------------
// �������     �� ICM20602 ����������ת��Ϊʵ����������
// ����˵��     gyro_value      �����������������
// ���ز���     void
// ʹ��ʾ��     float data = icm20602_gyro_transition(icm20602_gyro_x);         // ��λΪ ��/s
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
#define icm20602_gyro_transition(gyro_value)    ((float)gyro_value / icm20602_transition_factor[1])

uint8   icm20602_init               (void);

#endif

