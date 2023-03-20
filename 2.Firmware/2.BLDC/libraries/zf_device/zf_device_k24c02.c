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
* 文件名称          zf_device_k24c02
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
* 接线定义：
*                   ------------------------------------
*                   模块管脚                                        单片机管脚
*                   软件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_k24c02.h 中 K24C02_SCL_PIN 宏定义
*                   SDA                 查看 zf_device_k24c02.h 中 K24C02_SDA_PIN 宏定义
*                   硬件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_k24c02.h 中 K24C02_SCL_PIN 宏定义
*                   SDA                 查看 zf_device_k24c02.h 中 K24C02_SDA_PIN 宏定义
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_delay.h"
#include "zf_driver_iic.h"
#include "zf_driver_soft_iic.h"

#include "zf_device_k24c02.h"

#if K24C02_USE_SOFT_IIC
static soft_iic_info_struct k24c02_iic_struct;

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     K24C02 IIC 写寄存器数据
// 参数说明     reg             寄存器
// 参数说明     *data           数据缓冲区
// 参数说明     len             数据长度
// 返回参数     void
// 使用示例     k24c02_write_registers(page_num*8, (uint8 *)&k24c02_union_buffer[0], K24C02_PAGE_SIZE);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define k24c02_write_registers(reg, data, len)  (soft_iic_write_8bit_registers(&k24c02_iic_struct, (reg), (data), (len)))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     K24C02 IIC 读寄存器数据
// 参数说明     reg             寄存器
// 参数说明     *data           数据缓冲区
// 参数说明     len             数据长度
// 返回参数     void
// 使用示例     k24c02_read_registers(page_num*8, (uint8 *)&k24c02_union_buffer[0], K24C02_PAGE_SIZE);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define k24c02_read_registers(reg, data, len)   (soft_iic_read_8bit_registers(&k24c02_iic_struct, (reg), (data), (len)))
#else
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     K24C02 IIC 写寄存器数据
// 参数说明     reg             寄存器
// 参数说明     *data           数据缓冲区
// 参数说明     len             数据长度
// 返回参数     void
// 使用示例     k24c02_write_registers(page_num*8, (uint8 *)&k24c02_union_buffer[0], K24C02_PAGE_SIZE);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define k24c02_write_registers(reg, data, len)  (iic_write_8bit_registers(K24C02_IIC, K24C02_DEV_ADDR, (reg), (data), (len)))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     K24C02 IIC 读寄存器数据
// 参数说明     reg             寄存器
// 参数说明     *data           数据缓冲区
// 参数说明     len             数据长度
// 返回参数     void
// 使用示例     k24c02_read_registers(page_num*8, (uint8 *)&k24c02_union_buffer[0], K24C02_PAGE_SIZE);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define k24c02_read_registers(reg, data, len)   (iic_read_8bit_registers(K24C02_IIC, K24C02_DEV_ADDR, (reg), (data), (len)))
#endif

k24c02_data_union k24c02_union_buffer[K24C02_DATA_BUFFER_SIZE];

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     K24C02 读指定的页码数据到缓冲区
// 参数说明     page_num        指定的页码
// 返回参数     void
// 使用示例     k24c02_read_page_to_buffer(K24C02_PAGE_0);
// 备注信息     数据更新到缓冲区 调用本函数后直接读取缓冲区即可
//-------------------------------------------------------------------------------------------------------------------
void k24c02_read_page_to_buffer (k24c02_page_enum page_num)
{
    k24c02_read_registers(page_num*8, (uint8 *)&k24c02_union_buffer[0], K24C02_PAGE_SIZE);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     K24C02 将缓冲区数据写入指定页码
// 参数说明     page_num        指定的页码
// 返回参数     void
// 使用示例     k24c02_write_page_from_buffer(K24C02_PAGE_0);
// 备注信息     将数据缓冲区的数据写入 K24C02 的指定页码
//-------------------------------------------------------------------------------------------------------------------
uint8 k24c02_write_page_from_buffer (k24c02_page_enum page_num)
{
    uint8 return_state = 0;
    k24c02_write_registers(page_num*8, (uint8 *)&k24c02_union_buffer[0], K24C02_PAGE_SIZE);
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// brief		初始化 K24C02
// param		void
// return		uint8           1-初始化失败 0-初始化成功
// 使用示例     k24c02_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 k24c02_init (void)
{
    uint8 return_state = 0;
#if K24C02_USE_SOFT_IIC
    soft_iic_init(&k24c02_iic_struct, K24C02_DEV_ADDR, K24C02_SOFT_IIC_DELAY, K24C02_SCL_PIN, K24C02_SDA_PIN);
#else
    iic_init(K24C02_IIC, K24C02_DEV_ADDR, K24C02_IIC_SPEED, K24C02_SCL_PIN, K24C02_SDA_PIN);
#endif
    return return_state;
}
