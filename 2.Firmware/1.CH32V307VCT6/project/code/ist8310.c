/*
 * ist8310.c
 *
 *  Created on: 2023 04 29
 *      Author: sorrymaker
 */
#include "ist8310.h"

static soft_iic_info_struct ist8310_iic_struct;

#define ist8310_write_array(data, len)          (soft_iic_write_8bit_array(&ist8310_iic_struct, (data), (len)))
#define ist8310_write_register(reg, data)       (soft_iic_write_8bit_register(&ist8310_iic_struct, (reg), (data)))
#define ist8310_read_register(reg)              (soft_iic_read_8bit_register(&ist8310_iic_struct, (reg)))
#define ist8310_read_registers(reg, data, len)  (soft_iic_read_8bit_registers(&ist8310_iic_struct, (reg), (data), (len)))

static bool isInit = false;

_xyz_s16_st Mag_ADCRaw; //ist8310 origin data
_xyz_f_st   Mag_Raw;    // unit ut

bool CompassCheck(void)
{
    uint8_t Id;
    soft_iic_init(&ist8310_iic_struct, IST8310_SLAVE_ADDRESS, IST8310_SOFT_IIC_DELAY, IST8310_SCL_PIN, IST8310_SDA_PIN);
    Id = ist8310_read_register(IST8310_ID);
    if(0x10 == Id)
    {
        isInit = true;
    }
    return isInit;
}

void Magdata_To_Ut(void)
{
    //转换为uT
    Mag_Raw.x = Mag_ADCRaw.x * 0.3f;//14位有效数据的正负，1600uT
    Mag_Raw.y = Mag_ADCRaw.y * 0.3f;//14位有效数据的正负，1600uT
    Mag_Raw.z = Mag_ADCRaw.z * 0.3f;//14位有效数据的正负，2500uT
}

void IST8310Init(void)
{
    if (CompassCheck())
    {
        ist8310_write_register(IST8310_PD_CTR,0xC0);//配置设置或者复位脉冲持续时间
        system_delay_ms(1);
        ist8310_write_register(IST8310_AVER_CTR,0x24);//配置读取数据求平均，设置为16个数据平均
        system_delay_ms(1);
        ist8310_write_register(IST8310_CTR_1,0x01);//配置模式， Single Measurement Mode
    }
    else
    {
        zf_assert(0);
    }
}

void Compass_Read(void)
{
  uint8_t IST8310_Buff[6] = {0};
  uint8_t IST8310_Stu = 0x00;

  ist8310_read_registers(IST8310_STATUS_1, &IST8310_Stu, 1);
  system_delay_ms(1);
  if(0x01 == (IST8310_Stu & 0x01))
  {
//    ist8310_read_registers(IST8310_XOUT_L, IST8310_Buff, 6);
      IST8310_Buff[0]=ist8310_read_register(IST8310_XOUT_L);//OUT_X_L_A
      IST8310_Buff[1]=ist8310_read_register(IST8310_XOUT_H);//OUT_X_H_A
      IST8310_Buff[2]=ist8310_read_register(IST8310_YOUT_L);//OUT_Y_L_A
      IST8310_Buff[3]=ist8310_read_register(IST8310_YOUT_H);//OUT_Y_H_A
      IST8310_Buff[4]=ist8310_read_register(IST8310_ZOUT_L);//OUT_Z_L_A
      IST8310_Buff[5]=ist8310_read_register(IST8310_ZOUT_H);//OUT_Z_H_A
      
    //NED
    Mag_ADCRaw.x = (int16_t)(((u16)IST8310_Buff[3] << 8 | IST8310_Buff[2]));
    Mag_ADCRaw.y = (int16_t)(((u16)IST8310_Buff[1] << 8 | IST8310_Buff[0]));
    Mag_ADCRaw.z = (int16_t)(((u16)IST8310_Buff[5] << 8 | IST8310_Buff[4]));
  }
  system_delay_ms(1);
  ist8310_write_register(IST8310_CTR_1, 0x01);//配置模式， Single Measurement Mode,每次读数据之前要配置该寄存器
  Magdata_To_Ut();
}
