/*
 * ist8310.h
 *
 *  Created on: 2023 04 29
 *      Author: sorrymaker
 */
#ifndef __IST8310_H
#define __IST8310_H

#include "zf_common_headfile.h"

//====================================================软件 IIC 驱动====================================================
#define IST8310_SOFT_IIC_DELAY         ( 20 )                                      // 软件 IIC 的时钟延时周期 数值越小 IIC 通信速率越快
#define IST8310_SCL_PIN                ( E5 )                                      // 软件 IIC SCL 引脚 连接 DL1A 的 SCL 引脚
#define IST8310_SDA_PIN                ( E6 )                                      // 软件 IIC SDA 引脚 连接 DL1A 的 SDA 引脚
//====================================================软件 IIC 驱动====================================================

#define IST8310_SLAVE_ADDRESS  0x0E
#define IST8310_ID             0x00
#define IST8310_STATUS_1       0x02
#define IST8310_XOUT_L         0x03
#define IST8310_XOUT_H         0x04
#define IST8310_YOUT_L         0x05
#define IST8310_YOUT_H         0x06
#define IST8310_ZOUT_L         0x07
#define IST8310_ZOUT_H         0x08
#define IST8310_STATUS_2       0x09
#define IST8310_CTR_1          0x0A
#define IST8310_CTR_2          0x0B
#define IST8310_TEMPOUT_L      0x1C
#define IST8310_TEMPOUT_H      0x1D
#define IST8310_AVER_CTR       0x41
#define IST8310_PD_CTR         0x42

typedef struct
{
    short int x;
    short int y;
    short int z;
} s16_st;

typedef struct
{
    float x;
    float y;
    float z;
} f_st;

extern s16_st Mag_ADCRaw;
extern f_st   Mag_Raw;

void IST8310Init(void);
void Compass_Read(void);
#endif

