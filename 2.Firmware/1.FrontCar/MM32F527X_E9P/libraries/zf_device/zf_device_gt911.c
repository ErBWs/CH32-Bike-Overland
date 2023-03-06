/*********************************************************************************************************************
* MM32F527X-E9P Opensourec Library 即（MM32F527X-E9P 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 MM32F527X-E9P 开源库的一部分
* 
* MM32F527X-E9P 开源库 是免费软件
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
* 文件名称          zf_device_gt911
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MDK 5.37
* 适用平台          MM32F527X_E9P
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-08-10        Teternal            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   软件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_gt911.h 中 GT911_SOFT_IIC_SCL_PIN 宏定义
*                   SDA                 查看 zf_device_gt911.h 中 GT911_SOFT_IIC_SDA_PIN 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   硬件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_gt911.h 中 GT911_IIC_SCL_PIN 宏定义
*                   SDA                 查看 zf_device_gt911.h 中 GT911_IIC_SDA_PIN 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_driver_delay.h"
#include "zf_driver_iic.h"
#include "zf_driver_soft_iic.h"

#include "zf_device_gt911.h"

#if GT911_USE_SOFT_IIC
static soft_iic_info_struct gt911_iic_struct;
#endif
static gt911_dir_enum gt911_dir = IPS350_DEFAULT_DIR;
static uint16 gt911_x_max = 320;
static uint16 gt911_y_max = 480;

gt911_data_struct gt911_contact_state[5] = 
{
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gt911 读取寄存器数据
// 参数说明     register_addr   寄存器
// 参数说明     *data           数据缓冲
// 参数说明     len             数据长度
// 返回参数     void
// 使用示例     gt911_read_registers(GT911_READ_ADDR, data_buffer, 1);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void gt911_read_registers (uint16 register_addr, uint8 *data, uint32 len)
{
#if GT911_USE_SOFT_IIC
    soft_iic_write_16bit(&gt911_iic_struct, register_addr);
    soft_iic_read_8bit_array(&gt911_iic_struct, data, len);
#else
    iic_write_16bit(GT911_IIC, GT911_IIC_ADDR, register_addr);
    iic_read_8bit_array(GT911_IIC, GT911_IIC_ADDR, data, len);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gt911 写寄存器数据
// 参数说明     register_addr   寄存器
// 参数说明     *data           数据缓冲
// 参数说明     len             数据长度
// 返回参数     void
// 使用示例     gt911_write_registers(GT911_READ_ADDR, data_buffer+1, 1);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void gt911_write_registers (uint16 register_addr, uint8 *data, uint32 len)
{
    uint8 data_buffer[32];
    memset(data_buffer, 0, 32);
    data_buffer[0] = (register_addr & 0xFF00) >> 8;
    data_buffer[1] = (register_addr & 0x00FF);
    memcpy(&data_buffer[2], data, len);
#if GT911_USE_SOFT_IIC
    soft_iic_write_8bit_array(&gt911_iic_struct, data_buffer, len + 2);
#else
    iic_write_8bit_array(GT911_IIC, GT911_IIC_ADDR, data_buffer, len + 2);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示方向 这个函数只有在初始化屏幕之前调用才生效
// 参数说明     dir             显示方向  参照 zf_device_gt911.h 内 gt911_dir_enum 枚举体定义
// 返回参数     void
// 使用示例     gt911_set_dir(GT911_PORTAIT);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void gt911_set_dir (gt911_dir_enum dir)
{
    gt911_dir = dir;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     GT911 触摸扫描  这个函数放在主循环或者 PIT 中断中
// 参数说明     void
// 返回参数     uint8           触点个数
// 使用示例     gt911_scanner();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 gt911_scanner (void)
{
    uint16 addr_temp = GT911_TOUCH_DATA_ADDR;
    uint16 x_temp = 0, y_temp = 0;
    uint8 loop_temp = 0, contact_index = 0;
    uint8 data_buffer[4] = {0, 0, 0, 0};

    gt911_read_registers(GT911_READ_ADDR, data_buffer, 1);
    if((data_buffer[0] & 0x80) && (6 > (data_buffer[0] & 0x0F)))
    {
        gt911_write_registers(GT911_READ_ADDR, data_buffer + 1, 1);
    }
    if((data_buffer[0] & 0x0F) && (6 > (data_buffer[0] & 0x0F)))
    {
        for(loop_temp = ((data_buffer[0] & 0x0F)); 0 < loop_temp; loop_temp --)
        {
            gt911_read_registers(addr_temp, data_buffer, 4);
            addr_temp += 8;
            x_temp = ((uint16)data_buffer[1] << 8) + data_buffer[0];
            y_temp = ((uint16)data_buffer[3] << 8) + data_buffer[2];
            
            if(x_temp < gt911_x_max && y_temp < gt911_y_max)
            {
                switch(gt911_dir)
                {
                    case GT911_PORTAIT:
                    {
                        gt911_contact_state[contact_index].x_axis = x_temp;
                        gt911_contact_state[contact_index].y_axis = y_temp;
                    }break;
                    case GT911_PORTAIT_180:
                    {
                        gt911_contact_state[contact_index].x_axis = gt911_x_max - x_temp;
                        gt911_contact_state[contact_index].y_axis = gt911_y_max - y_temp;
                    }break;
                    case GT911_CROSSWISE:
                    {
                        gt911_contact_state[contact_index].x_axis = gt911_y_max - y_temp;
                        gt911_contact_state[contact_index].y_axis = x_temp;
                    }break;
                    case GT911_CROSSWISE_180:
                    {
                        gt911_contact_state[contact_index].x_axis = y_temp;
                        gt911_contact_state[contact_index].y_axis = gt911_x_max - x_temp;
                    }break;
                }
                contact_index ++;
            }
        }
    }
    if(0x80 == (data_buffer[0] & 0x8F))
    {
        for(loop_temp = 0; 5 > loop_temp; loop_temp ++)
        {
            gt911_contact_state[loop_temp].x_axis = 0;
            gt911_contact_state[loop_temp].y_axis = 0;
        }
    }
    return contact_index;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     初始化 GT911
// 参数说明     void
// 返回参数     uint8           1-初始化失败 0-初始化成功
// 使用示例     gt911_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 gt911_init (void)
{
    uint8 loop_count = 0;
    uint8 data_buffer[4] = {0, 0, 0, 0};
#if GT911_USE_SOFT_IIC
    soft_iic_init(&gt911_iic_struct, GT911_IIC_ADDR, GT911_SOFT_IIC_DELAY, GT911_SCL_PIN, GT911_SDA_PIN);
#else
    iic_init(GT911_IIC, GT911_IIC_ADDR, GT911_IIC_SPEED, GT911_SCL_PIN, GT911_SDA_PIN);
#endif
    gpio_init(GT911_RST_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(GT911_INT_PIN, GPO, GPIO_HIGH, GPO_OPEN_DTAIN);

    do{
        GT911_RST(0);
        system_delay_ms(10);
        GT911_RST(1);
        system_delay_ms(10);

        GT911_INT(1);
        GT911_RST(1);
        system_delay_ms(20);
        GT911_INT(0);
        GT911_RST(0);
        system_delay_ms(20);
        GT911_INT((GT911_IIC_ADDR == 0x14));
        system_delay_ms(20);
        GT911_RST(1);

        GT911_INT(0);
        system_delay_ms(50);
        gpio_init(GT911_INT_PIN, GPI, GPIO_HIGH, GPI_FLOATING_IN);

        gt911_read_registers(GT911_ID_ADDR, data_buffer, 4);
        loop_count ++;
    }while(0x39 != data_buffer[0] && GT911_TIMEOUT_COUNT >= loop_count);

    return ((GT911_TIMEOUT_COUNT >= loop_count) ? 0 : 1);
}
