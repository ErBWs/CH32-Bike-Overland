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
* 文件名称          zf_driver_spi
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

#include "hal_rcc.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"

#include "zf_driver_spi.h"

static SPI_Type *spi_index[3] = {SPI1, SPI2, SPI3};

#define SPI_CTRL_CS(x, e)           ((e) ? (spi_index[x]->NSSR &= ~SPI_I2S_NSSR_NSS(1)) : (spi_index[x]->NSSR |= SPI_I2S_NSSR_NSS(1)))      // SPI 片选 ENABLE/DISABLE 控制片选 拉低/拉高
#define SPI_CTRL_RX(x, e)           ((e) ? (spi_index[x]->GCTL |= SPI_I2S_GCTL_RXEN(1)) : (spi_index[x]->GCTL &= ~SPI_I2S_GCTL_RXEN(1)))    // SPI RX 使能 ENABLE/DISABLE

#define SPI_DATA_RX(x)              (spi_index[x]->RXREG)                       // SPI 读数据
#define SPI_DATA_TX(x, data)        (spi_index[x]->TXREG = (data))              // SPI 写数据

#define SPI_STATE_BUY(x)            (spi_index[x]->CSTAT & SPI_I2S_CSTAT_BUSY(1))           // SPI 忙 正在传输中
#define SPI_STATE_RX_FIFO_COUNT(x)  ((spi_index[x]->CSTAT & SPI_I2S_CSTAT_RXFADDR(15)) >> 8)// SPI 接收缓冲器内数据个数
#define SPI_STATE_TX_FIFO_COUNT(x)  ((spi_index[x]->CSTAT & SPI_I2S_CSTAT_TXFADDR(15)) >> 4)// SPI 发送缓冲器内数据个数
#define SPI_STATE_RX_FIFO_4(x)      (spi_index[x]->CSTAT & SPI_I2S_CSTAT_RXAVL4BYTE(1))     // SPI 接收缓冲器内数据个数超过四个了
#define SPI_STATE_TX_FIFO_FULL(x)   (spi_index[x]->CSTAT & SPI_I2S_CSTAT_TXFULL(1))         // SPI 发送缓冲器满了
#define SPI_STATE_RX_AVAILABLE(x)   (spi_index[x]->CSTAT & SPI_I2S_CSTAT_RXAVL(1))          // SPI 接收缓冲器收到一个有效数据
#define SPI_STATE_TX_EMPTY(x)       (spi_index[x]->CSTAT & SPI_I2S_CSTAT_TXEPT(1))          // SPI 发送缓冲器空了

#ifndef SPI_SPEED_PRIORITY
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 SPI 8bit 数据读写
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     data            数据
// 返回参数     uint8           读取的数据
// 使用示例     spi_8bit_data_handler(spi_n, 5);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 spi_8bit_data_handler (spi_index_enum spi_n, const uint8 data)
{
    uint8 read_data = 0;

    SPI_CTRL_RX(spi_n, ZF_ENABLE);
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, data);                                                   // 发送数据
    while(!SPI_STATE_RX_AVAILABLE(spi_n));                                      // 接收到有效数据
    read_data = SPI_DATA_RX(spi_n);                                             // 读取数据

    SPI_CTRL_CS(spi_n, ZF_DISABLE);
    SPI_CTRL_RX(spi_n, ZF_DISABLE);

    return read_data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 SPI 16bit 数据读写
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     data            数据
// 返回参数     uint16          读取的数据
// 使用示例     spi_16bit_data_handler(spi_n, 5);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint16 spi_16bit_data_handler (spi_index_enum spi_n, const uint16 data)
{
    uint16 read_data = 0;
 
    SPI_CTRL_RX(spi_n, ZF_ENABLE);
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, (uint8)((data & 0xFF00) >> 8));                          // 发送数据
    while(!SPI_STATE_RX_AVAILABLE(spi_n));                                      // 接收到有效数据
    read_data = SPI_DATA_RX(spi_n);                                             // 读取数据

    SPI_DATA_TX(spi_n, (uint8)(data & 0x00FF));                                 // 发送数据
    while(!SPI_STATE_RX_AVAILABLE(spi_n));                                      // 接收到有效数据
    read_data = ((read_data << 8) | SPI_DATA_RX(spi_n));                        // 读取数据

    SPI_CTRL_CS(spi_n, ZF_DISABLE);
    SPI_CTRL_RX(spi_n, ZF_DISABLE);

    return read_data;
}
#endif

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口写 8bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     data            数据
// 返回参数     void
// 使用示例     spi_write_8bit(SPI_1, 0x11);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit (spi_index_enum spi_n, const uint8 data)
{
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, data);                                                   // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    while(SPI_STATE_BUY(spi_n));                                                // 等待传输完毕
    SPI_CTRL_CS(spi_n, ZF_DISABLE);
#else
    spi_8bit_data_handler(spi_n, data);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口写 8bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void
// 使用示例     spi_write_8bit_array(SPI_1, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_array (spi_index_enum spi_n, const uint8 *data, uint32 len)
{
    zf_assert(NULL != data);
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    while(len --)
    {
        SPI_DATA_TX(spi_n, *data ++);                                           // 发送数据
        while(!SPI_STATE_TX_EMPTY(spi_n));                                      // 发送为空
    }

    while(SPI_STATE_BUY(spi_n));                                                // 等待传输完毕
    SPI_CTRL_CS(spi_n, ZF_DISABLE);
#else
    while(len --)
    {
        spi_8bit_data_handler(spi_n, *data ++);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口写 16bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     data            数据
// 返回参数     void
// 使用示例     spi_write_16bit(SPI_1, 0x1101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit (spi_index_enum spi_n, const uint16 data)
{
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, (uint8)((data & 0xFF00) >> 8));                          // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    SPI_DATA_TX(spi_n, (uint8)(data & 0x00FF));                                 // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    while(SPI_STATE_BUY(spi_n));                                                // 等待传输完毕
    SPI_CTRL_CS(spi_n, ZF_DISABLE);
#else
    spi_16bit_data_handler(spi_n, data);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口写 16bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void
// 使用示例     spi_write_16bit_array(SPI_1, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_array (spi_index_enum spi_n, const uint16 *data, uint32 len)
{
    zf_assert(NULL != data);
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    while(len --)
    {
        SPI_DATA_TX(spi_n, (uint8)((*data & 0xFF00) >> 8));                     // 发送数据
        while(!SPI_STATE_TX_EMPTY(spi_n));                                      // 发送为空

        SPI_DATA_TX(spi_n, (uint8)(*data ++ & 0x00FF));                         // 发送数据
        while(!SPI_STATE_TX_EMPTY(spi_n));                                      // 发送为空
    }

    while(SPI_STATE_BUY(spi_n));                                                // 等待传输完毕
    SPI_CTRL_CS(spi_n, ZF_DISABLE);
#else
    while(len --)
    {
        spi_16bit_data_handler(spi_n, *data ++);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口向传感器的寄存器写 8bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     data            数据
// 返回参数     void
// 使用示例     spi_write_8bit_register(SPI_1, 0x11, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_register (spi_index_enum spi_n, const uint8 register_name, const uint8 data)
{
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, register_name);                                          // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    SPI_DATA_TX(spi_n, data);                                                   // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    while(SPI_STATE_BUY(spi_n));                                                // 等待传输完毕
    SPI_CTRL_CS(spi_n, ZF_DISABLE);
#else
    spi_8bit_data_handler(spi_n, register_name);
    spi_8bit_data_handler(spi_n, data);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口向传感器的寄存器写 8bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void
// 使用示例     spi_write_8bit_registers(SPI_1, 0x11, data, 32);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_registers (spi_index_enum spi_n, const uint8 register_name, const uint8 *data, uint32 len)
{
    zf_assert(NULL != data);
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, register_name);                                          // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    while(len --)
    {
        SPI_DATA_TX(spi_n, *data ++);                                           // 发送数据
        while(!SPI_STATE_TX_EMPTY(spi_n));                                      // 发送为空
    }

    while(SPI_STATE_BUY(spi_n));                                                // 等待传输完毕
    SPI_CTRL_CS(spi_n, ZF_DISABLE);
#else
    spi_8bit_data_handler(spi_n, register_name);
    while(len --)
    {
        spi_8bit_data_handler(spi_n, *data ++);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口向传感器的寄存器写 16bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     data            数据
// 返回参数     void
// 使用示例     spi_write_16bit_register(SPI_1, 0x1011, 0x0101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_register (spi_index_enum spi_n, const uint16 register_name, const uint16 data)
{
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, (uint8)((register_name & 0xFF00) >> 8));                 // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    SPI_DATA_TX(spi_n, (uint8)(register_name & 0x00FF));                        // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    SPI_DATA_TX(spi_n, (uint8)((data & 0xFF00) >> 8));                          // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    SPI_DATA_TX(spi_n, (uint8)(data & 0x00FF));                                 // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    while(SPI_STATE_BUY(spi_n));                                                // 等待传输完毕
    SPI_CTRL_CS(spi_n, ZF_DISABLE);
#else
    spi_16bit_data_handler(spi_n, register_name);
    spi_16bit_data_handler(spi_n, data);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口向传感器的寄存器写 16bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void
// 使用示例     spi_write_16bit_registers(SPI_1, 0x1011, data, 32);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_registers (spi_index_enum spi_n, const uint16 register_name, const uint16 *data, uint32 len)
{
    zf_assert(NULL != data);
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, (uint8)((register_name & 0xFF00) >> 8));                 // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    SPI_DATA_TX(spi_n, (uint8)(register_name & 0x00FF));                        // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    while(len --)
    {
        SPI_DATA_TX(spi_n, (uint8)((*data & 0xFF00) >> 8));                     // 发送数据
        while(!SPI_STATE_TX_EMPTY(spi_n));                                      // 发送为空

        SPI_DATA_TX(spi_n, (uint8)(*data ++ & 0x00FF));                         // 发送数据
        while(!SPI_STATE_TX_EMPTY(spi_n));                                      // 发送为空
    }

    while(SPI_STATE_BUY(spi_n));                                                // 等待传输完毕
    SPI_CTRL_CS(spi_n, ZF_DISABLE);
#else
    spi_16bit_data_handler(spi_n, register_name);
    while(len--)
    {
        spi_16bit_data_handler(spi_n, *data++);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口读 8bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 返回参数     uint8           数据
// 使用示例     spi_read_8bit(SPI_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 spi_read_8bit (spi_index_enum spi_n)
{
#ifdef SPI_SPEED_PRIORITY
    uint8 data = 0;

    SPI_CTRL_RX(spi_n, ZF_ENABLE);
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, 0);                                                      // 发送数据
    while(!SPI_STATE_RX_AVAILABLE(spi_n));                                      // 接收到有效数据
    data = SPI_DATA_RX(spi_n);                                                  // 读取数据

    SPI_CTRL_CS(spi_n, ZF_DISABLE);
    SPI_CTRL_RX(spi_n, ZF_DISABLE);
    return data;
#else
    return spi_8bit_data_handler(spi_n, 0);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口读 8bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             发送缓冲区长度
// 返回参数     void
// 使用示例     spi_read_8bit_array(SPI_1, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_read_8bit_array (spi_index_enum spi_n, uint8 *data, uint32 len)
{
    zf_assert(NULL != data);
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_RX(spi_n, ZF_ENABLE);
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    while(len --)
    {
        SPI_DATA_TX(spi_n, 0);                                                  // 发送数据
        while(!SPI_STATE_RX_AVAILABLE(spi_n));                                  // 接收到有效数据
        *data ++ = SPI_DATA_RX(spi_n);                                          // 读取数据
    }

    SPI_CTRL_CS(spi_n, ZF_DISABLE);
    SPI_CTRL_RX(spi_n, ZF_DISABLE);
#else
    while(len --)
    {
        *data ++ = spi_8bit_data_handler(spi_n, 0);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口读 16bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 返回参数     uint16          数据
// 使用示例     spi_read_16bit(SPI_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 spi_read_16bit (spi_index_enum spi_n)
{
#ifdef SPI_SPEED_PRIORITY
    uint16 data = 0;

    SPI_CTRL_RX(spi_n, ZF_ENABLE);
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, 0);                                                      // 发送数据
    while(!SPI_STATE_RX_AVAILABLE(spi_n));                                      // 接收到有效数据
    data = SPI_DATA_RX(spi_n);                                                  // 读取数据

    SPI_DATA_TX(spi_n, 0);                                                      // 发送数据
    while(!SPI_STATE_RX_AVAILABLE(spi_n));                                      // 接收到有效数据
    data = ((data << 8)| SPI_DATA_RX(spi_n));                                   // 读取数据

    SPI_CTRL_CS(spi_n, ZF_DISABLE);
    SPI_CTRL_RX(spi_n, ZF_DISABLE);
    return data;
#else
    return spi_16bit_data_handler(spi_n, 0);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口读 16bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             发送缓冲区长度
// 返回参数     void
// 使用示例     spi_read_16bit_array(SPI_1, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_read_16bit_array (spi_index_enum spi_n, uint16 *data, uint32 len)
{
    zf_assert(NULL != data);
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_RX(spi_n, ZF_ENABLE);
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    while(len --)
    {
        SPI_DATA_TX(spi_n, 0);                                                  // 发送数据
        while(!SPI_STATE_RX_AVAILABLE(spi_n));                                  // 接收到有效数据
        *data = SPI_DATA_RX(spi_n);                                             // 读取数据

        SPI_DATA_TX(spi_n, 0);                                                  // 发送数据
        while(!SPI_STATE_RX_AVAILABLE(spi_n));                                  // 接收到有效数据
        *data = ((*data << 8)| SPI_DATA_RX(spi_n));                             // 读取数据
        data ++;
    }

    SPI_CTRL_CS(spi_n, ZF_DISABLE);
    SPI_CTRL_RX(spi_n, ZF_DISABLE);
#else
    while(len --)
    {
        *data ++ = spi_16bit_data_handler(spi_n, 0);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口从传感器的寄存器读 8bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 返回参数     uint8           数据
// 使用示例     spi_read_8bit_register(SPI_1, 0x11);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 spi_read_8bit_register (spi_index_enum spi_n, const uint8 register_name)
{
#ifdef SPI_SPEED_PRIORITY
    uint8 data = 0;

    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, register_name);                                          // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    SPI_CTRL_RX(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, 0);                                                      // 发送数据
    while(!SPI_STATE_RX_AVAILABLE(spi_n));                                      // 等待读取一个数据
    data = SPI_DATA_RX(spi_n);                                                  // 读取数据

    SPI_CTRL_CS(spi_n, ZF_DISABLE);
    SPI_CTRL_RX(spi_n, ZF_DISABLE);
    return data;
#else
    spi_8bit_data_handler(spi_n, register_name);
    return spi_8bit_data_handler(spi_n, 0);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口从传感器的寄存器读 8bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             发送缓冲区长度
// 返回参数     void
// 使用示例     spi_read_8bit_registers(SPI_1, 0x11, data, 32);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_read_8bit_registers (spi_index_enum spi_n, const uint8 register_name, uint8 *data, uint32 len)
{
    zf_assert(NULL != data);
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, register_name);                                          // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    SPI_CTRL_RX(spi_n, ZF_ENABLE);

    while(len --)
    {
        SPI_DATA_TX(spi_n, 0);                                                  // 发送数据
        while(!SPI_STATE_RX_AVAILABLE(spi_n));                                  // 等待读取一个数据
        *data ++ = SPI_DATA_RX(spi_n);                                          // 读取数据
    }

    SPI_CTRL_CS(spi_n, ZF_DISABLE);
    SPI_CTRL_RX(spi_n, ZF_DISABLE);
#else
    spi_8bit_data_handler(spi_n, register_name);
    while(len --)
    {
        *data ++ = spi_8bit_data_handler(spi_n, 0);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口从传感器的寄存器读 16bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 返回参数     uint16          数据
// 使用示例     spi_read_16bit_register(SPI_1, 0x1011);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 spi_read_16bit_register (spi_index_enum spi_n, const uint16 register_name)
{
#ifdef SPI_SPEED_PRIORITY
    uint16 data = 0;
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, (uint8)((register_name & 0xFF00) >> 8));                 // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    SPI_DATA_TX(spi_n, (uint8)(register_name & 0x00FF));                        // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    SPI_CTRL_RX(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, 0);                                                      // 发送数据
    while(!SPI_STATE_RX_AVAILABLE(spi_n));                                      // 等待读取一个数据
    data = SPI_DATA_RX(spi_n);                                                  // 读取数据

    SPI_DATA_TX(spi_n, 0);                                                      // 发送数据
    while(!SPI_STATE_RX_AVAILABLE(spi_n));                                      // 等待读取一个数据
    data = ((data << 8)| SPI_DATA_RX(spi_n));                                   // 读取数据

    SPI_CTRL_CS(spi_n, ZF_DISABLE);
    SPI_CTRL_RX(spi_n, ZF_DISABLE);
    return data;
#else
    spi_16bit_data_handler(spi_n, register_name);
    return spi_16bit_data_handler(spi_n, 0);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口从传感器的寄存器读 16bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             发送缓冲区长度
// 返回参数     void
// 使用示例     spi_read_16bit_registers(SPI_1, 0x1101, data, 32);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_read_16bit_registers (spi_index_enum spi_n, const uint16 register_name, uint16 *data, uint32 len)
{
    zf_assert(NULL != data);
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    SPI_DATA_TX(spi_n, (uint8)((register_name & 0xFF00) >> 8));                 // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    SPI_DATA_TX(spi_n, (uint8)(register_name & 0x00FF));                        // 发送数据
    while(!SPI_STATE_TX_EMPTY(spi_n));                                          // 发送为空

    SPI_CTRL_RX(spi_n, ZF_ENABLE);
 
    while(len --)
    {
        SPI_DATA_TX(spi_n, 0);                                                  // 发送数据
        while(!SPI_STATE_RX_AVAILABLE(spi_n));                                  // 等待读取一个数据
        *data = SPI_DATA_RX(spi_n);                                             // 读取数据

        SPI_DATA_TX(spi_n, 0);                                                  // 发送数据
        while(!SPI_STATE_RX_AVAILABLE(spi_n));                                  // 等待读取一个数据
        *data = ((*data << 8)| SPI_DATA_RX(spi_n));                             // 读取数据
        data ++;
    }

    SPI_CTRL_CS(spi_n, ZF_DISABLE);
    SPI_CTRL_RX(spi_n, ZF_DISABLE);
#else
    spi_16bit_data_handler(spi_n, register_name);
    while(len --)
    {
        *data ++ = spi_16bit_data_handler(spi_n, 0);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 8bit 数据传输 发送与接收数据是同时进行的
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     write_buffer    发送的数据缓冲区地址
// 参数说明     read_buffer     发送数据时接收到的数据的存储地址(不需要接收则传 NULL)
// 参数说明     len             缓冲区长度
// 返回参数     void
// 使用示例     spi_transfer_8bit(SPI_1, buf, buf, 1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_transfer_8bit (spi_index_enum spi_n, const uint8 *write_buffer, uint8 *read_buffer, uint32 len)
{
    zf_assert(NULL != write_buffer);
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_RX(spi_n, ZF_ENABLE);
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    while(len --)                                                               // 判断长度
    {
        SPI_DATA_TX(spi_n, *write_buffer ++);                                   // 发送数据
        if(NULL != read_buffer)                                                 // 接收有效
        {
            while(!SPI_STATE_RX_AVAILABLE(spi_n));                              // 等待读取一个数据
            *read_buffer ++ = SPI_DATA_RX(spi_n);                               // 读取数据
        }
        else
        {
            while(!SPI_STATE_TX_EMPTY(spi_n));                                  // 发送为空
        }
    }

    while(SPI_STATE_BUY(spi_n));                                                // 等待传输完毕
    SPI_CTRL_CS(spi_n, ZF_DISABLE);
    SPI_CTRL_RX(spi_n, ZF_DISABLE);
#else
    while(len --)
    {
        if(NULL != read_buffer)
        {
            *read_buffer = spi_8bit_data_handler(spi_n, *write_buffer);
            write_buffer ++;
            read_buffer ++;
        }
        else
        {
            spi_8bit_data_handler(spi_n, *write_buffer);
            write_buffer ++;
        }
    }
}
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 16bit 数据传输 发送与接收数据是同时进行的
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     write_buffer    发送的数据缓冲区地址
// 参数说明     read_buffer     发送数据时接收到的数据的存储地址(不需要接收则传 NULL)
// 参数说明     len             缓冲区长度
// 返回参数     void
// 使用示例     spi_transfer_16bit(SPI_1, buf, buf, 1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_transfer_16bit (spi_index_enum spi_n, const uint16 *write_buffer, uint16 *read_buffer, uint32 len)
{
    zf_assert(NULL != write_buffer);
#ifdef SPI_SPEED_PRIORITY
    SPI_CTRL_RX(spi_n, ZF_ENABLE);
    SPI_CTRL_CS(spi_n, ZF_ENABLE);

    while(len --)                                                               // 判断长度
    {
        if(NULL != read_buffer)                                                 // 接收有效
        {
            SPI_DATA_TX(spi_n, (*write_buffer & 0xFF00) >> 8);                  // 发送数据
            while(!SPI_STATE_RX_AVAILABLE(spi_n));                              // 等待读取一个数据
            *read_buffer = (SPI_DATA_RX(spi_n) & 0x00FF);                       // 读取数据

            SPI_DATA_TX(spi_n, (*write_buffer & 0x00FF));                       // 发送数据
            while(!SPI_STATE_RX_AVAILABLE(spi_n));                              // 等待读取一个数据
            *read_buffer = (*read_buffer << 8) | (SPI_DATA_RX(spi_n)& 0x00FF);  // 读取数据

            write_buffer ++;
            read_buffer ++;
        }
        else
        {
            SPI_DATA_TX(spi_n, (*write_buffer & 0xFF00) >> 8);                  // 发送数据
            while(!SPI_STATE_TX_EMPTY(spi_n));                                  // 发送为空

            SPI_DATA_TX(spi_n, (*write_buffer & 0x00FF));                     	// 发送数据
            while(!SPI_STATE_TX_EMPTY(spi_n));                                  // 发送为空

            write_buffer ++;
        }
    }

    while(SPI_STATE_BUY(spi_n));                                                // 等待传输完毕
    SPI_CTRL_CS(spi_n, ZF_DISABLE);
    SPI_CTRL_RX(spi_n, ZF_DISABLE);
#else
    while(len --)
    {
        if(NULL != read_buffer)
        {
            *read_buffer = spi_16bit_data_handler(spi_n, *write_buffer);
            write_buffer ++;
            read_buffer ++;
        }
        else
        {
            spi_16bit_data_handler(spi_n, *write_buffer);
            write_buffer ++;
        }
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口初始化
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     mode            SPI 模式 参照 zf_driver_spi.h 内 spi_mode_enum 枚举体定义
// 参数说明     baud            设置 SPI 的波特率 不超过系统时钟的一半 部分速率会被适配成相近的速率
// 参数说明     sck_pin         选择 SCK 引脚 参照 zf_driver_spi.h 内 spi_sck_pin_enum 枚举体定义
// 参数说明     mosi_pin        选择 MOSI 引脚 参照 zf_driver_spi.h 内 spi_mosi_pin_enum 枚举体定义
// 参数说明     miso_pin        选择 MISO 引脚 参照 zf_driver_spi.h 内 spi_miso_pin_enum 枚举体定义
// 参数说明     cs_pin          选择 CS 引脚 参照 zf_driver_spi.h 内 spi_cs_pin_enum 枚举体定义
// 返回参数     void
// 使用示例     spi_init(SPI_1, 0, 1*1000*1000, SPI1_SCK_A05, SPI1_MOSI_A07, SPI1_MISO_A06, SPI1_NSS_A04);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_init (spi_index_enum spi_n, spi_mode_enum mode, uint32 baud, spi_sck_pin_enum sck_pin, spi_mosi_pin_enum mosi_pin, spi_miso_pin_enum miso_pin, spi_cs_pin_enum cs_pin)
{
    zf_assert((sck_pin & spi_n) == spi_n);                                      // sck_pin  与 spi_n 匹配
    zf_assert((mosi_pin & spi_n) == spi_n);                                     // mosi_pin 与 spi_n 匹配
    zf_assert(((miso_pin & spi_n) == spi_n) || (SPI_MISO_NULL == miso_pin));    // miso_pin 与 spi_n 匹配
    zf_assert(((cs_pin & spi_n) == spi_n) || (SPI_CS_NULL == cs_pin));          // cs_pin   与 spi_n 匹配

    afio_init((gpio_pin_enum)((sck_pin & 0xFFF00) >> 8), GPO, (gpio_af_enum)((sck_pin & 0xF0) >> 4), GPO_AF_PUSH_PULL);      // 提取对应IO索引 AF功能编码
    afio_init((gpio_pin_enum)((mosi_pin & 0xFFF00) >> 8), GPO, (gpio_af_enum)((mosi_pin & 0xF0) >> 4), GPO_AF_PUSH_PULL);    // 提取对应IO索引 AF功能编码
    if(SPI_MISO_NULL != miso_pin)
    {
        afio_init((gpio_pin_enum)((miso_pin & 0xFFF00) >> 8), GPI, (gpio_af_enum)((miso_pin & 0xF0) >> 4), GPI_FLOATING_IN); // 提取对应IO索引 AF功能编码
    }
    if(SPI_CS_NULL != cs_pin)
    {
        afio_init((gpio_pin_enum)((cs_pin & 0xFFF00) >> 8), GPO, (gpio_af_enum)((cs_pin & 0xF0) >> 4), GPO_AF_PUSH_PULL);    // 提取对应IO索引 AF功能编码
    }

    switch(spi_n)
    {
        case SPI_1: RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_SPI1, ZF_ENABLE);    break;
        case SPI_2: RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_SPI2, ZF_ENABLE);    break;
        case SPI_3: RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_SPI3, ZF_ENABLE);    break;
    }

    SPI_Master_Init_Type spi_master_init;
    spi_master_init.ClockFreqHz     = bus_clock;
    spi_master_init.BaudRate        = baud;
    switch(mode)
    {
        default:
        case SPI_MODE0: spi_master_init.PolPha  = SPI_PolPha_Alt1;  break;      // SCK 空闲时低电平 第一个时钟边沿开始采样
        case SPI_MODE1: spi_master_init.PolPha  = SPI_PolPha_Alt0;  break;      // SCK 空闲时低电平 第二个时钟边沿开始采样
        case SPI_MODE2: spi_master_init.PolPha  = SPI_PolPha_Alt3;  break;      // SCK 空闲时高电平 第一个时钟边沿开始采样
        case SPI_MODE3: spi_master_init.PolPha  = SPI_PolPha_Alt2;  break;      // SCK 空闲时高电平 第二个时钟边沿开始采样
    }
    spi_master_init.DataWidth       = SPI_DataWidth_8b;                         // 8bits 数据
    spi_master_init.XferMode        = SPI_XferMode_TxRx;
    spi_master_init.AutoCS          = false;
    spi_master_init.LSB             = ZF_DISABLE;
    switch(spi_n)
    {
        case SPI_1:
        {
            SPI_InitMaster(SPI1, &spi_master_init);
            SPI_Enable(SPI1, ZF_ENABLE);
        }break;
        case SPI_2:
        {
            SPI_InitMaster(SPI2, &spi_master_init);
            SPI_Enable(SPI2, ZF_ENABLE);
        }break;
        case SPI_3:
        {
            SPI_InitMaster(SPI3, &spi_master_init);
            SPI_Enable(SPI3, ZF_ENABLE);
        }break;
    }

    SPI_CTRL_RX(spi_n, ZF_DISABLE);
    while(SPI_STATE_BUY(spi_n));                                                // 等待传输完毕
}
