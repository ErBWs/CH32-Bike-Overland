/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library 即（CH32V307VCT6 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是CH32V307VCT6 开源库的一部分
*
* CH32V307VCT6 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          zf_device_aht20
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                             备注
* 2022-09-15        大W            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* 接线定义:
*                   ------------------------------------
*                   模块管脚                                 单片机管脚
*                   软件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_aht20.h 中 AHT20_SOFT_IIC_SCL 宏定义
*                   SDA                 查看 zf_device_aht20.h 中 AHT20_SOFT_IIC_SDA 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*
*                   硬件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_aht20.h 中 AHT20_IIC_SCL 宏定义
*                   SDA                 查看 zf_device_aht20.h 中 AHT20_IIC_SDA 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
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
// 函数简介      AHT20 自检函数
// 参数说明     NULL
// 返回参数     uint8           0 - 初始化成功 1 - 初始化失败
// 使用示例     调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
static uint8 aht20_self1_check(void)
{
    uint8 return_state = 0;
    uint16 timeout_count = 0;
    uint8 send_data[2] = {0x08, 0x00};
    while((AHT20_CAL_ENABLE & aht20_read_register(AHT20_READ_STATE)) != AHT20_CAL_ENABLE)
    {
        //卡在这里原因有以下几点
        //1 AHT20 坏了，如果是新的这样的概率极低
        //2 接线错误或者没有接好
        //3 可能你需要外接上拉电阻，上拉到3.3V
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
// 函数简介      获取 AHT20 温湿度数据
// 参数说明     void
// 返回参数     void
// 使用示例     aht20_read_data();                              // 执行该函数后，直接查看对应的变量即可
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
// 函数简介      初始化 AHT20
// 参数说明     NULL
// 返回参数     uint8           0 - 初始化成功 1 - 初始化失败
// 使用示例     调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
uint8 aht20_init (void)
{
    uint8 return_state = 0;
#if AHT20_USE_SOFT_IIC
    soft_iic_init(&aht20_iic_struct, AHT20_DEV_ADDR, AHT20_SOFT_IIC_DELAY, AHT20_SCL_PIN, AHT20_SDA_PIN);
#else
    iic_init(AHT20_IIC, AHT20_DEV_ADDR, AHT20_IIC_SPEED, AHT20_SCL_PIN, AHT20_SDA_PIN);
#endif
    system_delay_ms(40);                                                        // 上电延时

    return_state = aht20_self1_check();
    return return_state;
}
