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
* 文件名称          zf_driver_spi
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

#include "zf_driver_gpio.h"
#include "zf_driver_spi.h"

const uint32 spi_index[3] = {SPI1_BASE, SPI2_BASE, SPI3_BASE};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口写 8bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     data            数据
// 返回参数     void
// 使用示例     spi_write_8bit(SPI_1,0x11);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit (spi_index_enum spi_n, const uint8 dat)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = dat;                                   // 发送数据
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);    // 发送为空
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口写 8bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void
// 使用示例     spi_write_8bit_array(SPI_1,data,64);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_array (spi_index_enum spi_n, const uint8 *dat, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = *(dat++);
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口写 16bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     data            数据
// 返回参数     void
// 使用示例     spi_write_16bit(SPI_1,0x1101);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit (spi_index_enum spi_n, const uint16 dat)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((dat & 0xFF00)>>8);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(dat & 0x00FF);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口写 16bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void
// 使用示例     spi_write_16bit_array(SPI_1,data,64);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_array (spi_index_enum spi_n, const uint16 *dat, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((*dat & 0xFF00)>>8);
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(*dat++ & 0x00FF);
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口向传感器的寄存器写 8bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     data            数据
// 返回参数     void
// 使用示例     spi_write_8bit_register(SPI_1,0x11,0x01);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_register (spi_index_enum spi_n, const uint8 register_name, const uint8 dat)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = register_name;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY));
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = dat;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY));
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口向传感器的寄存器写 8bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void
// 使用示例     spi_write_8bit_registers(SPI_1,0x11,data,32);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_registers (spi_index_enum spi_n, const uint8 register_name, const uint8 *dat, uint32 len)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = register_name;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = *dat++;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口向传感器的寄存器写 16bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     data            数据
// 返回参数     void
// 使用示例     spi_write_16bit_register(SPI_1,0x1011,0x0101);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_register (spi_index_enum spi_n, const uint16 register_name, const uint16 dat)
{

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((register_name & 0xFF00)>>8);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(register_name & 0x00FF);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((dat & 0xFF00)>>8);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(dat & 0x00FF);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口向传感器的寄存器写 16bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void
// 使用示例     spi_write_16bit_registers(SPI_1,0x1011,data,32);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_registers (spi_index_enum spi_n, const uint16 register_name, const uint16 *dat, uint32 len)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((register_name & 0xFF00)>>8);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(register_name & 0x00FF);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((*dat & 0xFF00)>>8);
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(*dat++ & 0x00FF);
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    }

}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口读 8bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 返回参数     uint8         数据
// 使用示例     spi_read_8bit(SPI_1);
//-------------------------------------------------------------------------------------------------------------------
uint8 spi_read_8bit (spi_index_enum spi_n)
{
    uint8 dat = 0;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
    dat = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

    return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口读 8bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             发送缓冲区长度
// 返回参数     void
// 使用示例     spi_read_8bit_array(SPI_1,data,64);
//-------------------------------------------------------------------------------------------------------------------
void spi_read_8bit_array (spi_index_enum spi_n, uint8 *dat, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
        *dat++ = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口读 16bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 返回参数     uint16        数据
// 使用示例     spi_read_16bit(SPI_1);
//-------------------------------------------------------------------------------------------------------------------
uint16 spi_read_16bit (spi_index_enum spi_n)
{
    uint16 dat = 0;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    dat = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    dat = ((dat << 8)| ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR);

    return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口读 16bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             发送缓冲区长度
// 返回参数     void
// 使用示例     spi_read_16bit_array(SPI_1,data,64);
//-------------------------------------------------------------------------------------------------------------------
void spi_read_16bit_array (spi_index_enum spi_n, uint16 *dat, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
        *dat = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
        *dat = ((*dat << 8)| ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR);
        dat++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口从传感器的寄存器读 8bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 返回参数     uint8         数据
// 使用示例     spi_read_8bit_register(SPI_1,0x11);
 //-------------------------------------------------------------------------------------------------------------------
uint8 spi_read_8bit_register (spi_index_enum spi_n, const uint8 register_name)
{
    uint8 dat;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = register_name;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY));
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 2;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY));
    dat = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;


    return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口从传感器的寄存器读 8bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             发送缓冲区长度
// 返回参数     void
// 使用示例     spi_read_8bit_registers(SPI_1,0x11,data,32);
//-------------------------------------------------------------------------------------------------------------------
void spi_read_8bit_registers (spi_index_enum spi_n, const uint8 register_name, uint8 *dat, uint32 len)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = register_name;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY));
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY));
        *dat++ = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口从传感器的寄存器读 16bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 返回参数     uint16        数据
// 使用示例     spi_read_16bit_register(SPI_1,0x1011);
//-------------------------------------------------------------------------------------------------------------------
uint16 spi_read_16bit_register (spi_index_enum spi_n, const uint16 register_name)
{

    uint16 dat = 0;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((register_name & 0xFF00)>>8);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(register_name & 0x00FF);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
    dat = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
     while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
     //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
     dat = ((dat << 8)|  ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR);

     return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口从传感器的寄存器读 16bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             发送缓冲区长度
// 返回参数     void
// 使用示例     spi_read_16bit_registers(SPI_1,0x1101,data,32);
//-------------------------------------------------------------------------------------------------------------------
void spi_read_16bit_registers (spi_index_enum spi_n, const uint16 register_name, uint16 *dat, uint32 len)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((register_name & 0xFF00)>>8);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(register_name & 0x00FF);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
        *dat = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
        *dat = ((*dat << 8)|  ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR);
        dat++;
    }

}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 8bit 数据传输 发送与接收数据是同时进行的
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     write_buffer    发送的数据缓冲区地址
// 参数说明     read_buffer     发送数据时接收到的数据的存储地址(不需要接收则传 NULL)
// 参数说明     len             缓冲区长度
// 返回参数     void
// 使用示例     spi_transfer_8bit(SPI_1,buf,buf,1);
//-------------------------------------------------------------------------------------------------------------------
void spi_transfer_8bit (spi_index_enum spi_n,const uint8 *write_buffer, uint8 *read_buffer, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = *(write_buffer++);
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        if(read_buffer != NULL)
        {
            //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
            *read_buffer++ = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 16bit 数据传输 发送与接收数据是同时进行的
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     write_buffer    发送的数据缓冲区地址
// 参数说明     read_buffer     发送数据时接收到的数据的存储地址(不需要接收则传 NULL)
// 参数说明     len             缓冲区长度
// 返回参数     void
// 使用示例     spi_transfer_16bit(SPI_1,buf,buf,1);
//-------------------------------------------------------------------------------------------------------------------
void spi_transfer_16bit (spi_index_enum spi_n, const uint16 *write_buffer, uint16 *read_buffer, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (*write_buffer&0xFF00)>>8;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        if(read_buffer != NULL)
        {
            //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
            *read_buffer++ = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
        }

        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (*write_buffer&0x00FF);
         while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
         if(read_buffer != NULL)
         {
             //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
             *read_buffer = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
         }
         write_buffer++;
         read_buffer++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      SPI 接口初始化
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     mode            SPI 模式 参照 zf_driver_spi.h 内 spi_mode_enum 枚举体定义
// 参数说明     baud            设置 SPI 的波特率 不超过系统时钟的一半 部分速率会被适配成相近的速率
// 参数说明     sck_pin         选择 SCK 引脚 参照 zf_driver_spi.h 内 spi_pin_enum 枚举体定义
// 参数说明     mosi_pin        选择 MOSI 引脚 参照 zf_driver_spi.h 内 spi_pin_enum 枚举体定义
// 参数说明     miso_pin        选择 MISO 引脚 参照 zf_driver_spi.h 内 spi_pin_enum 枚举体定义
// 参数说明     cs_pin          选择 CS 引脚 参照 zf_driver_gpio.h 内 gpio_pin_enum 枚举体定义
// 返回参数     void
// 使用示例     spi_init(SPI_1, 0, 1*1000*1000, SPI1_SCK_A5, SPI1_MOSI_A7, SPI1_MISO_A6, A4);  //硬件SPI初始化  模式0 波特率为1Mhz
//-------------------------------------------------------------------------------------------------------------------
void spi_init(spi_index_enum spi_n, spi_mode_enum mode, uint32 baud, spi_pin_enum sck_pin, spi_pin_enum mosi_pin, spi_pin_enum miso_pin, gpio_pin_enum cs_pin)
{
    SPI_I2S_DeInit((SPI_TypeDef *)(spi_index[spi_n]));

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                                           // 复用总线使能

    if(sck_pin == SPI1_MAP1_SCK_B3 && mosi_pin == SPI1_MAP1_MOSI_B5)
    {
        GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);
    }
    else if(sck_pin == SPI3_MAP1_SCK_C10 && mosi_pin == SPI3_MAP1_MOSI_C12)
    {
        GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);
    }

         if(SPI_1 == spi_n)   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);                // SPI1时钟使能
    else if(SPI_2 == spi_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);                // SPI2时钟使能
    else if(SPI_3 == spi_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);                // SPI3时钟使能

    gpio_init(sck_pin  & 0xFF,  GPO, 1, SPEED_50MHZ|GPO_AF_PUSH_PULL);
    gpio_init(mosi_pin & 0xFF,  GPO, 1, SPEED_50MHZ|GPO_AF_PUSH_PULL);
    if(miso_pin != SPI_MISO_NULL)
    {
        gpio_init(miso_pin & 0xFF,  GPI, 1, SPEED_50MHZ|GPI_PULL_UP);
    }
    if(cs_pin != PIN_NULL)
    {
        gpio_init(cs_pin & 0xFF,  GPO, 0, SPEED_50MHZ|GPO_PUSH_PULL);
    }

    SPI_InitTypeDef  SPI_InitStructure = {0};
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;      // SPI设置为双线双向全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                           // 设置SPI工作模式:设置为主SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                       // 设置SPI的数据大小:SPI发送接收8位帧结构

    switch(mode)
    {
        case SPI_MODE0:
        {
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                      // 串行同步时钟的空闲状态为低电平
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                    // 串行同步时钟的第一个跳变沿（上升或下降）数据被采样
        }break;
        case SPI_MODE1:
        {
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                      // 串行同步时钟的空闲状态为低电平
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                    // 串行同步时钟的第二个跳变沿（上升或下降）数据被采样
        }break;
        case SPI_MODE2:
        {
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                     // 串行同步时钟的空闲状态为高电平
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                    // 串行同步时钟的第一个跳变沿（上升或下降）数据被采样
        }break;
        case SPI_MODE3:
        {
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                     // 串行同步时钟的空闲状态为高电平
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                    // 串行同步时钟的第二个跳变沿（上升或下降）数据被采样
        }break;
    }

    uint16 psc = 0;
    psc = system_clock / baud;                                              // 计算分频值
    if((system_clock % baud)== 0)
    {
        psc = psc - 1;
    }
         if(psc >= 128) psc = SPI_BaudRatePrescaler_256;                    // CLK_0.5625M
    else if(psc >= 64)  psc = SPI_BaudRatePrescaler_128;                    // CLK_1.125M
    else if(psc >= 32)  psc = SPI_BaudRatePrescaler_64;                     // CLK_2.25M
    else if(psc >= 16)  psc = SPI_BaudRatePrescaler_32;                     // CLK_4.5M
    else if(psc >= 8)   psc = SPI_BaudRatePrescaler_16;                     // CLK_9M
    else if(psc >= 4)   psc = SPI_BaudRatePrescaler_8;                      // CLK_18M
    else if(psc >= 2)   psc = SPI_BaudRatePrescaler_4;                      // CLK_36M
    else if(psc >= 1)   psc = SPI_BaudRatePrescaler_2;                      // CLK_72M
    else zf_assert(0);

    SPI_InitStructure.SPI_BaudRatePrescaler = psc;                          // 定义波特率预分频的值
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                               // 主机模式，使用软件控制NSS引脚
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                      // 指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI_InitStructure.SPI_CRCPolynomial = 7;                                // CRC值计算的多项式
    SPI_Init((SPI_TypeDef *)(spi_index[spi_n]), &SPI_InitStructure);        // 根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

    SPI_Cmd(((SPI_TypeDef *)(spi_index[spi_n])), ENABLE);                   // 使能SPI外设
}
