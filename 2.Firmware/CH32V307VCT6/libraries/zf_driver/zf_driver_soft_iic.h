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
* �ļ�����          zf_driver_soft_iic
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

#ifndef _zf_driver_soft_iic_h_
#define _zf_driver_soft_iic_h_


#include "zf_driver_gpio.h"

typedef struct
{
    gpio_pin_enum       scl_pin;                                                // ���ڼ�¼��Ӧ�����ű��
    gpio_pin_enum       sda_pin;                                                // ���ڼ�¼��Ӧ�����ű��
    uint8               addr;                                                   // ������ַ ��λ��ַģʽ
    uint32              delay;                                                  // ģ�� IIC ����ʱʱ��
}soft_iic_info_struct;

void        soft_iic_write_8bit             (soft_iic_info_struct *soft_iic_obj, const uint8 data);
void        soft_iic_write_8bit_array       (soft_iic_info_struct *soft_iic_obj, const uint8 *data, uint32 len);

void        soft_iic_write_16bit            (soft_iic_info_struct *soft_iic_obj, const uint16 data);
void        soft_iic_write_16bit_array      (soft_iic_info_struct *soft_iic_obj, const uint16 *data, uint32 len);

void        soft_iic_write_8bit_register    (soft_iic_info_struct *soft_iic_obj, const uint8 register_name, const uint8 data);
void        soft_iic_write_8bit_registers   (soft_iic_info_struct *soft_iic_obj, const uint8 register_name, const uint8 *data, uint32 len);

void        soft_iic_write_16bit_register   (soft_iic_info_struct *soft_iic_obj, const uint16 register_name, const uint16 data);
void        soft_iic_write_16bit_registers  (soft_iic_info_struct *soft_iic_obj, const uint16 register_name, const uint16 *data, uint32 len);

uint8       soft_iic_read_8bit              (soft_iic_info_struct *soft_iic_obj);
void        soft_iic_read_8bit_array        (soft_iic_info_struct *soft_iic_obj, uint8 *data, uint32 len);

uint16      soft_iic_read_16bit             (soft_iic_info_struct *soft_iic_obj);
void        soft_iic_read_16bit_array       (soft_iic_info_struct *soft_iic_obj, uint16 *data, uint32 len);

uint8       soft_iic_read_8bit_register     (soft_iic_info_struct *soft_iic_obj, const uint8 register_name);
void        soft_iic_read_8bit_registers    (soft_iic_info_struct *soft_iic_obj, const uint8 register_name, uint8 *data, uint32 len);

uint16      soft_iic_read_16bit_register    (soft_iic_info_struct *soft_iic_obj, const uint16 register_name);
void        soft_iic_read_16bit_registers   (soft_iic_info_struct *soft_iic_obj, const uint16 register_name, uint16 *data, uint32 len);

void        soft_iic_transfer_8bit_array    (soft_iic_info_struct *soft_iic_obj, const uint8 *write_data, uint32 write_len, uint8 *read_data, uint32 read_len);
void        soft_iic_transfer_16bit_array   (soft_iic_info_struct *soft_iic_obj, const uint16 *write_data, uint32 write_len, uint16 *read_data, uint32 read_len);

void        soft_iic_sccb_write_register    (soft_iic_info_struct *soft_iic_obj, const uint8 register_name, uint8 data);
uint8       soft_iic_sccb_read_register     (soft_iic_info_struct *soft_iic_obj, const uint8 register_name);

void        soft_iic_init                   (soft_iic_info_struct *soft_iic_obj, uint8 addr, uint32 delay, gpio_pin_enum scl_pin, gpio_pin_enum sda_pin);

#endif

