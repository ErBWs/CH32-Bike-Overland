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
* 文件名称          zf_driver_iic
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

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"

#include "zf_driver_iic.h"

static  I2C_Type    *iic_index[2]      = {I2C1, I2C2};
static  uint16      iic_speed_count[2];

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 延时
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 返回参数     void
// 使用示例     iic_delay(IIC_1);
// 备注信息     内部调用 不加延时可能导致硬件错误 }:-)
//-------------------------------------------------------------------------------------------------------------------
static void iic_delay (iic_index_enum iic_n)
{
    volatile uint32 i = iic_speed_count[iic_n] * 2;
    while(i --)
    {
        __NOP();
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口写 8bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     iic_write_8bit(IIC_1, 0x7A, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_8bit (iic_index_enum iic_n, uint8 target_addr, const uint8 data)
{
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR = data;
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口写 8bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_write_8bit_array(IIC_1, 0x7A, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_8bit_array (iic_index_enum iic_n, uint8 target_addr, const uint8 *data, uint32 len)
{
    zf_assert(NULL != data);
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    while(len --)
    {
        iic_index[iic_n]->DR = *data ++;
        while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                         // 发送缓冲为空
    }

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口写 16bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     iic_write_16bit(IIC_1, 0x7A, 0x0101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_16bit (iic_index_enum iic_n, uint8 target_addr, const uint16 data)
{
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR = (uint8)((data & 0xFF00) >> 8);
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空
    iic_index[iic_n]->DR = (uint8)(data & 0x00FF);
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口写 16bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_write_16bit_array(IIC_1, 0x7A, data, 6);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_16bit_array (iic_index_enum iic_n, uint8 target_addr, const uint16 *data, uint32 len)
{
    zf_assert(NULL != data);
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    while(len --)
    {
        iic_index[iic_n]->DR = (uint8)((*data & 0xFF00) >> 8);
        while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                         // 发送缓冲为空
        iic_index[iic_n]->DR = (uint8)(*data ++ & 0x00FF);
        while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                         // 发送缓冲为空
    }

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口向传感器寄存器写 8bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     iic_write_8bit_register(IIC_1, 0x7A, 0x01, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_8bit_register (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 data)
{
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR = register_name;
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    iic_index[iic_n]->DR = data;
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口向传感器寄存器写 8bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_write_8bit_registers(IIC_1, 0x7A, 0x01, data, 6);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_8bit_registers (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 *data, uint32 len)
{
    zf_assert(NULL != data);
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR = register_name;
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    while(len --)
    {
        iic_index[iic_n]->DR = *(data ++);
        while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                         // 发送缓冲为空
    }

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口向传感器寄存器写 16bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     iic_write_16bit_register(IIC_1, 0x7A, 0x0101, 0x0101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_16bit_register (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 data)
{
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR = (uint8)((register_name & 0xFF00) >> 8);
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空
    iic_index[iic_n]->DR = (uint8)(register_name & 0x00FF);
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    iic_index[iic_n]->DR = (uint8)((data & 0xFF00) >> 8);
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空
    iic_index[iic_n]->DR = (uint8)(data & 0x00FF);
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口向传感器寄存器写 16bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_write_16bit_registers(IIC_1, 0x7A, 0x0101, data, 6);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_16bit_registers (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 *data, uint32 len)
{
    zf_assert(NULL != data);
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR = (uint8)((register_name & 0xFF00) >> 8);
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空
    iic_index[iic_n]->DR = (uint8)(register_name & 0x00FF);
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    while(len --)
    {
        iic_index[iic_n]->DR = (uint8)((*data & 0xFF00) >> 8);
        while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                         // 发送缓冲为空
        iic_index[iic_n]->DR = (uint8)(*data ++ & 0x00FF);
        while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                         // 发送缓冲为空
    }

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口读取 8bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 返回参数     uint8           返回读取的 8bit 数据
// 使用示例     iic_read_8bit(IIC_1, 0x7A);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_read_8bit (iic_index_enum iic_n, uint8 target_addr)
{
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    uint8 data = 0;

    iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                      // IIC 读
    while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                            // 接收缓冲不为空
    data = iic_index[iic_n]->DR;

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口读取 8bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_read_8bit_array(IIC_1, 0x7A, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_read_8bit_array (iic_index_enum iic_n, uint8 target_addr, uint8 *data, uint32 len)
{
    zf_assert(NULL != data);
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    while(len --)
    {
        iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                  // IIC 读
        while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                        // 接收缓冲不为空
        *data ++ = iic_index[iic_n]->DR;
    }

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口读取 16bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 返回参数     uint16          返回读取的 16bit 数据
// 使用示例     iic_read_16bit(IIC_1, 0x7A);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 iic_read_16bit (iic_index_enum iic_n, uint8 target_addr)
{
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    uint16 data = 0;

    iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                      // IIC 读
    while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                            // 接收缓冲不为空
    data = iic_index[iic_n]->DR;
    iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                      // IIC 读
    while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                            // 接收缓冲不为空
    data = ((data << 8)| iic_index[iic_n]->DR);

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口读取 16bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_read_16bit_array(IIC_1, 0x7A, data, 8);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_read_16bit_array (iic_index_enum iic_n, uint8 target_addr, uint16 *data, uint32 len)
{
    zf_assert(NULL != data);
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    while(len --)
    {
        iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                  // IIC 读
        while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                        // 接收缓冲不为空
        *data = iic_index[iic_n]->DR;
        iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                  // IIC 读
        while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                        // 接收缓冲不为空
        *data = ((*data << 8)| iic_index[iic_n]->DR);
        data ++;
    }

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口从传感器寄存器读取 8bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 返回参数     uint8           返回读取的 8bit 数据
// 使用示例     iic_read_8bit_register(IIC_1, 0x7A, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_read_8bit_register (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name)
{
    uint8 data = 0;
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR = register_name;
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                      // IIC 读
    while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                            // 接收缓冲不为空
    data = iic_index[iic_n]->DR;

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口从传感器寄存器读取 8bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_read_8bit_registers(IIC_1, 0x7A, 0x01, data, 8);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_read_8bit_registers (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 *data, uint32 len)
{
    zf_assert(NULL != data);
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR = register_name;
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    while(len --)
    {
        iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                  // IIC 读
        while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                        // 接收缓冲不为空
        *(data ++) = iic_index[iic_n]->DR;
    }

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口从传感器寄存器读取 16bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 返回参数     uint16          返回读取的 16bit 数据
// 使用示例     iic_read_16bit_register(IIC_1, 0x7A, 0x0101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 iic_read_16bit_register (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name)
{
    uint16 data = 0;
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR = (uint8)((register_name & 0xFF00) >> 8);
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空
    iic_index[iic_n]->DR = (uint8)(register_name & 0x00FF);
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                      // IIC 读
    while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                            // 接收缓冲不为空
    data = iic_index[iic_n]->DR;
    iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                      // IIC 读
    while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                            // 接收缓冲不为空
    data = ((data << 8)| iic_index[iic_n]->DR);

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口从传感器寄存器读取 16bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_read_16bit_registers(IIC_1, 0x7A, 0x0101, data, 8);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_read_16bit_registers (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, uint16 *data, uint32 len)
{
    zf_assert(NULL != data);
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR = (uint8)((register_name & 0xFF00) >> 8);
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空
    iic_index[iic_n]->DR = (uint8)(register_name & 0x00FF);
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    while(len --)
    {
        iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                  // IIC 读
        while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                        // 接收缓冲不为空
        *data = iic_index[iic_n]->DR;
        iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                  // IIC 读
        while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                        // 接收缓冲不为空
        *data = ((*data << 8)| iic_index[iic_n]->DR);
        data ++;
    }

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口传输 8bit 数组 先写后读取
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标器件地址
// 参数说明     *write_data     发送数据存放缓冲区
// 参数说明     write_len       发送缓冲区长度
// 参数说明     *read_data      读取数据存放缓冲区
// 参数说明     read_len        读取缓冲区长度
// 返回参数     void            
// 使用示例     iic_transfer_8bit_array(IIC_1, addr, data, 64, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_transfer_8bit_array (iic_index_enum iic_n, uint8 target_addr, const uint8 *write_data, uint32 write_len, uint8 *read_data, uint32 read_len)
{
    zf_assert(NULL != write_data);
    zf_assert(NULL != read_data);
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    while(write_len --)
    {
        iic_index[iic_n]->DR = *(write_data ++);
        while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                         // 发送缓冲为空
    }

    while(read_len --)
    {
        iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                  // IIC 读
        while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                        // 接收缓冲不为空
        *(read_data ++) = iic_index[iic_n]->DR;
    }

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口传输 16bit 数组 先写后读取
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标器件地址
// 参数说明     *write_data     发送数据存放缓冲区
// 参数说明     write_len       发送缓冲区长度
// 参数说明     *read_data      读取数据存放缓冲区
// 参数说明     read_len        读取缓冲区长度
// 返回参数     void            
// 使用示例     iic_transfer_16bit_array(IIC_1, addr, data, 64, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_transfer_16bit_array (iic_index_enum iic_n, uint8 target_addr, const uint16 *write_data, uint32 write_len, uint16 *read_data, uint32 read_len)
{
    zf_assert(NULL != write_data);
    zf_assert(NULL != read_data);
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空
    while(write_len --)
    {
        iic_index[iic_n]->DR = (uint8)((*write_data & 0xFF00) >> 8);
        while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                         // 发送缓冲为空
        iic_index[iic_n]->DR = (uint8)(*write_data ++ & 0x00FF);
        while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                         // 发送缓冲为空
    }

    while(read_len --)
    {
        iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                  // IIC 读
        while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                        // 接收缓冲不为空
        *read_data = iic_index[iic_n]->DR;
        iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                  // IIC 读
        while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                        // 接收缓冲不为空
        *read_data = ((*read_data << 8)| iic_index[iic_n]->DR);
        read_data ++;
    }

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口 SCCB 模式向传感器寄存器写 8bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     iic_sccb_write_register(IIC_1, 0x7A, 0x01, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_sccb_write_register (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 data)
{
    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR = register_name;
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    iic_index[iic_n]->DR = data;
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口 SCCB 模式从传感器寄存器读取 8bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 返回参数     uint8           返回读取的 8bit 数据
// 使用示例     iic_sccb_read_register(IIC_1, 0x7A, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_sccb_read_register (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name)
{
    uint8 data = 0;

    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR = register_name;
    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输

    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 关闭
    iic_index[iic_n]->TAR = I2C_DR_DAT(target_addr);
    iic_delay(iic_n);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    iic_index[iic_n]->DR |= I2C_DR_CMD(1);                                      // IIC 读
    while(!(iic_index[iic_n]->SR & I2C_SR_RFNE(1)));                            // 接收缓冲不为空
    data = iic_index[iic_n]->DR;

    iic_index[iic_n]->ENR |= I2C_ENR_ABORT(1);                                  // IIC 停止传输
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口初始化 默认 MASTER 模式 不提供 SLAVE 模式
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     addr            IIC 地址 这里需要注意 标准七位地址 最高位忽略 写入时请务必确认无误
// 参数说明     speed           IIC 速率 速率不超过 400Khz 不低于 1KHz 低于 1KHz 时钟的传感器赶紧扔了吧
// 参数说明     scl_pin         IIC 时钟引脚 参照 zf_driver_iic.h 内 iic_scl_pin_enum 枚举体定义
// 参数说明     sda_pin         IIC 数据引脚 参照 zf_driver_iic.h 内 iic_sda_pin_enum 枚举体定义
// 返回参数     void            
// 使用示例     iic_init(IIC_1, 0x7A, 100000, IIC1_SCL_D10, IIC1_SDA_D11);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_init(iic_index_enum iic_n, uint8 addr, uint32 speed, iic_scl_pin_enum scl_pin, iic_sda_pin_enum sda_pin)
{
    zf_assert((1000 <= speed)&&(1000000 >= speed));                             // 至少 1KHz 至多 1MHz 速率
    zf_assert(((scl_pin & 0x0F) == iic_n) && ((sda_pin & 0x0F) == iic_n));      // scl_pin 与 sda_pin 必须与 iic_n 匹配
    uint16 temp = bus_clock / speed / 2;

    afio_init((gpio_pin_enum)((scl_pin & 0xFFF00) >> 8), GPO, (gpio_af_enum)((scl_pin & 0xF0) >> 4), GPO_AF_PUSH_PULL); // 提取对应IO索引 AF功能编码
    afio_init((gpio_pin_enum)((sda_pin & 0xFFF00) >> 8), GPO, (gpio_af_enum)((sda_pin & 0xF0) >> 4), GPO_AF_OPEN_DTAIN);// 提取对应IO索引 AF功能编码
    switch(iic_n)
    {
        case IIC_1: RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_I2C1, ZF_ENABLE);    break;
        case IIC_2: RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_I2C1, ZF_ENABLE);    break;
    }

    iic_index[iic_n]->ENR &= I2C_ENR_ENABLE(0);                                 // IIC 禁止

    iic_speed_count[iic_n] = temp;
    if(100000 >= speed)
    {
        iic_index[iic_n]->SSHR = I2C_SSHR_CNT(temp);                            // 写入高电平持续时长
        iic_index[iic_n]->SSLR = I2C_SSLR_CNT(temp);                            // 写入低电平持续时长
        temp = (iic_index[iic_n]->CR & 0xFFFFFFF9) | 0x00000002;                // 设置标准模式         
    }
    else if(400000 >= speed)
    {
        iic_index[iic_n]->FSHR = I2C_FSHR_CNT(temp);                            // 写入高电平持续时长
        iic_index[iic_n]->FSLR = I2C_FSLR_CNT(temp);                            // 写入低电平持续时长
        temp = (iic_index[iic_n]->CR & 0xFFFFFFF9) | 0x00000004;                // 设置高速模式    
    }

    temp &= 0xFFFFFFEF;                                                         // 七位地址格式
    temp |= 0x00000400;                                                         // 自动 RESTART 信号
    iic_index[iic_n]->CR = temp;

    iic_index[iic_n]->TAR = I2C_DR_DAT(addr);                                   // 写入地址
    iic_index[iic_n]->RXTLR = I2C_RXTLR_TL(0);
    iic_index[iic_n]->TXTLR = I2C_TXTLR_TL(0);
    iic_index[iic_n]->IMR =   I2C_IMR_MRXUNDER(1)   | I2C_IMR_MRXOVER(1)    |\
        I2C_IMR_MRXFULL(1)  | I2C_IMR_MTXOVER(1)    | I2C_IMR_MTXEMPTY(1)   |\
        I2C_IMR_MRDREQ(1)   | I2C_IMR_MTXABRT(1)    | I2C_IMR_MRXDONE(1)    |\
        I2C_IMR_MACTIV(1)   | I2C_IMR_MSTOP(1)      | I2C_IMR_MSTART(1)     |\
        I2C_IMR_MGC(1)      | I2C_IMR_MMSTONHOLD(1) | I2C_IMR_MSCLSTUCK(1);
    iic_index[iic_n]->ENR |= I2C_ENR_ENABLE(1);                                 // IIC 使能

    while(!(iic_index[iic_n]->SR & I2C_SR_TFE(1)));                             // 发送缓冲为空
}
