/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-09-09     WCH        the first version
 */
#include <drv_es8388.h>
#include "drivers/i2c.h"
#include "drivers/pin.h"

#define DBG_TAG              "drv.es8388"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>


#define ES8388_ADDR 0x10

struct es8388_device
{
    struct rt_i2c_bus_device *i2c;
    rt_uint16_t pin_dir;           /* 用于切换数据方向 ，PA8*/
};

static struct es8388_device es_dev={0};


/* i2c 读寄存器  */
static rt_uint16_t reg_read( rt_uint8_t addr )
{
    struct rt_i2c_msg msg[2]={0};
    rt_uint8_t val = 0xff;

    RT_ASSERT(es_dev.i2c != RT_NULL);

    msg[0].addr  = ES8388_ADDR;
    msg[0].flags = RT_I2C_WR;
    msg[0].len   = 1;
    msg[0].buf   = &addr;

    msg[1].addr  = ES8388_ADDR;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = 1;
    msg[1].buf   = &val;

    if(rt_i2c_transfer(es_dev.i2c, msg, 2) !=2 ) //两次传输
    {
        rt_kprintf("I2C read data failed, reg = 0x%02x.\r\n",addr);
        return 0xff;
    }
    return val;
}

/* i2c 写数据寄存器  */
static void reg_write(rt_uint8_t addr, rt_uint8_t val)
{
    struct rt_i2c_msg msg[1]={0};
    rt_uint8_t buff[2] = {0};

    RT_ASSERT(es_dev.i2c != RT_NULL);

    buff[0] = addr;
    buff[1] = val;

    msg[0].addr  = ES8388_ADDR;
    msg[0].flags = RT_I2C_WR;
    msg[0].len   = 2;
    msg[0].buf   = buff;

    if (rt_i2c_transfer(es_dev.i2c, msg, 1) != 1)  //一次传输
    {
        rt_kprintf("I2C write data failed, reg = 0x%2x. \r\n", addr);
        return;
    }
}


void es8388_dir_select(rt_bool_t player)
{
    rt_pin_mode(es_dev.pin_dir, PIN_MODE_OUTPUT);

    if (player)
    {
        rt_pin_write(es_dev.pin_dir, PIN_LOW);
    }
    else
    {
        rt_pin_write(es_dev.pin_dir, PIN_HIGH);
    }
}

rt_err_t ES8388_Init(const char *i2c_name, rt_uint16_t pin)
{
    es_dev.i2c = rt_i2c_bus_device_find(i2c_name);
    if (es_dev.i2c == RT_NULL)
    {
        rt_kprintf("%s bus not found\n", i2c_name);
        return -RT_ERROR;
    }
    es_dev.pin_dir= pin;

    es8388_dir_select(0); //设置为接收

    reg_write(0, 0x80);
    reg_write(0, 0x00);
    rt_thread_delay(100); //等待复位

    reg_write(0x01, 0x58);
    reg_write(0x01, 0x50);
    reg_write(0x02, 0xF3);
    reg_write(0x02, 0xF0);

    reg_write(0x03, 0x09);   //麦克风偏置电源关闭
    reg_write(0x00, 0x06);   //使能参考      500K驱动使能
    reg_write(0x04, 0x00);   //DAC电源管理，不打开任何通道
    reg_write(0x08, 0x00);   //MCLK不分频
    reg_write(0x2B, 0x80);   //DAC控制 DACLRC与ADCLRC相同

    reg_write(0x09, 0x88);   //ADC L/R PGA增益配置为+24dB
    reg_write(0x0C, 0x4C);   //ADC   数据选择为left data = left ADC, right data = left ADC    音频数据为16bit
    reg_write(0x0D, 0x12);   //ADC配置 MCLK/采样率=250
    reg_write(0x10, 0x00);   //ADC数字音量控制将信号衰减 L  设置为最小！！！
    reg_write(0x11, 0x00);   //ADC数字音量控制将信号衰减 R  设置为最小！！！

    reg_write(0x17, 0x18);   //DAC 音频数据为16bit
    reg_write(0x18, 0x02);   //DAC   配置 MCLK/采样率=256
    reg_write(0x1A, 0x00);   //DAC数字音量控制将信号衰减 L  设置为最小！！！
    reg_write(0x1B, 0x00);   //DAC数字音量控制将信号衰减 R  设置为最小！！！
    reg_write(0x27, 0xB8);   //L混频器
    reg_write(0x2A, 0xB8);   //R混频器
    rt_thread_delay(100);

//    rt_kprintf("reg:%x\r\n",reg_read(0x2A));

    return RT_EOK;

}



/*
 * @brief   设置I2S工作模式
 *
 * @param   fmt     0,飞利浦标准I2S;1,MSB(左对齐);2,LSB(右对齐);3,PCM/DSP
 * @param   len     0,24bit;1,20bit;2,18bit;3,16bit;4,32bit
 *
 * @return  void
 */
void ES8388_I2S_Cfg(rt_uint8_t fmt, rt_uint8_t len)
{
    fmt &= 0X03;
    len &= 0X07; //限定范围
    reg_write(23, (fmt << 1) | (len << 3));  //R23,ES8388工作模式设置
}


/*
 * @brief   设置音量大小，音量慢慢增加到最大
 *
 * @param   volume      音量大小(0-33)
 *                      0 – -30dB
 *                      1 – -29dB
 *                      2 – -28dB
 *                      …
 *                      30 – 0dB
 *                      31 – 1dB
 *                      …
 *                      33 – 3dB
 *
 * @return  void
 */
void ES8388_Set_Volume(rt_uint8_t volume)
{
    for(u8 i = 0; i < volume; i++)
    {
        reg_write(0x2E, i);
        reg_write(0x2F, i);
    }
}


/*
 * @brief   ES8388 DAC/ADC配置
 *
 * @param   dacen   dac使能(0)/关闭(1)
 * @param   adcen   adc使能(0)/关闭(1)
 *
 * @return  void
 */
void ES8388_ADDA_Cfg(rt_uint8_t dacen,rt_uint8_t adcen)
{
    rt_uint8_t res = 0;

    res |= (dacen<<0);
    res |= (adcen<<1);
    res |= (dacen<<2);
    res |= (adcen<<3);

    reg_write(0x02, res);
}


/*
 * @brief   ES8388 DAC输出通道配置
 *
* @param   out      0:通道2输出，1:通道1输出
 *
 * @return  void
 */
void ES8388_Output_Cfg(rt_uint8_t out)
{
    reg_write(0x04, 3<<(out*2+2));
}


/*
 * @brief   ES8388 ADC输出通道配置
 *
* @param   in       0:通道1输入，1:通道2输入
 *
 * @return  void
 */
void ES8388_Input_Cfg(rt_uint8_t in)
{
    reg_write(0x0A,(5*in)<<4);   //ADC1 输入通道选择L/R    INPUT1
}





