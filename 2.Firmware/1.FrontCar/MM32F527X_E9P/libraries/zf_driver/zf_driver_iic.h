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

#ifndef _zf_driver_iic_h_
#define _zf_driver_iic_h_

#include "hal_rcc.h"

#include "zf_common_typedef.h"

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // IIC 1 引脚 SCL
    IIC1_SCL_A8         = 0x00840,                                              // 0x 008[A8]  4[AF4] 0[IIC1]
    IIC1_SCL_A9         = 0x00940,                                              // 0x 009[A9]  4[AF4] 0[IIC1]
    IIC1_SCL_A15        = 0x00F40,                                              // 0x 00F[A15] 4[AF4] 0[IIC1]
    IIC1_SCL_B6         = 0x02640,                                              // 0x 026[B6]  4[AF4] 0[IIC1]
    IIC1_SCL_B8         = 0x02840,                                              // 0x 028[B8]  4[AF4] 0[IIC1]
    IIC1_SCL_C0         = 0x04040,                                              // 0x 040[C0]  4[AF4] 0[IIC1]
    IIC1_SCL_C6         = 0x04640,                                              // 0x 046[C6]  4[AF4] 0[IIC1]
    IIC1_SCL_D10        = 0x06A40,                                              // 0x 06A[D10] 4[AF4] 0[IIC1]

    // IIC 2 引脚 SCL
    IIC2_SCL_B10        = 0x02A41,                                              // 0x 02A[B10] 4[AF4] 1[IIC2]
    IIC2_SCL_C2         = 0x04241,                                              // 0x 042[C2]  4[AF4] 1[IIC2]
    IIC2_SCL_C8         = 0x04841,                                              // 0x 048[C8]  4[AF4] 1[IIC2]
    IIC2_SCL_E5         = 0x08541,                                              // 0x 085[E5]  4[AF4] 1[IIC2]
    IIC2_SCL_F1         = 0x0A141,                                              // 0x 0A1[F1]  4[AF4] 1[IIC2]
}iic_scl_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // IIC 1 引脚 SDA
    IIC1_SDA_A10        = 0x00A40,                                              // 0x 00A[A10] 4[AF4] 0[IIC1]
    IIC1_SDA_A14        = 0x00E40,                                              // 0x 00E[A14] 4[AF4] 0[IIC1]
    IIC1_SDA_B7         = 0x02740,                                              // 0x 027[B7]  4[AF4] 0[IIC1]
    IIC1_SDA_B9         = 0x02940,                                              // 0x 029[B9]  4[AF4] 0[IIC1]
    IIC1_SDA_C1         = 0x04140,                                              // 0x 041[C1]  4[AF4] 0[IIC1]
    IIC1_SDA_C7         = 0x04740,                                              // 0x 047[C7]  4[AF4] 0[IIC1]
    IIC1_SDA_D11        = 0x06B40,                                              // 0x 06B[D11] 4[AF4] 0[IIC1]

    // IIC 2 引脚 SDA
    IIC2_SDA_B11        = 0x02B41,                                              // 0x 02B[B11] 4[AF4] 1[IIC2]
    IIC2_SDA_C3         = 0x04341,                                              // 0x 043[C3]  4[AF4] 1[IIC2]
    IIC2_SDA_C9         = 0x04941,                                              // 0x 049[C9]  4[AF4] 1[IIC2]
    IIC2_SDA_E6         = 0x08641,                                              // 0x 086[E6]  4[AF4] 1[IIC2]
    IIC2_SDA_F0         = 0x0A041,                                              // 0x 0A0[F0]  4[AF4] 1[IIC2]
}iic_sda_pin_enum;

typedef enum                                                                    // 枚举 IIC 工作状态 此枚举定义不允许用户修改
{
    IIC_SUCCESS,
    IIC_WRITE_TIMEOUT,
    IIC_READ_TIMEOUT,
}iic_state_enum;

typedef enum                                                                    // 枚举 IIC 编号 此枚举定义不允许用户修改
{
    IIC_1,
    IIC_2,
}iic_index_enum;

void        iic_write_8bit              (iic_index_enum iic_n, uint8 target_addr, const uint8 data);
void        iic_write_8bit_array        (iic_index_enum iic_n, uint8 target_addr, const uint8 *data, uint32 len);

void        iic_write_16bit             (iic_index_enum iic_n, uint8 target_addr, const uint16 data);
void        iic_write_16bit_array       (iic_index_enum iic_n, uint8 target_addr, const uint16 *data, uint32 len);

void        iic_write_8bit_register     (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 data);
void        iic_write_8bit_registers    (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 *data, uint32 len);

void        iic_write_16bit_register    (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 data);
void        iic_write_16bit_registers   (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 *data, uint32 len);

uint8       iic_read_8bit               (iic_index_enum iic_n, uint8 target_addr);
void        iic_read_8bit_array         (iic_index_enum iic_n, uint8 target_addr, uint8 *data, uint32 len);

uint16      iic_read_16bit              (iic_index_enum iic_n, uint8 target_addr);
void        iic_read_16bit_array        (iic_index_enum iic_n, uint8 target_addr, uint16 *data, uint32 len);

uint8       iic_read_8bit_register      (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name);
void        iic_read_8bit_registers     (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 *data, uint32 len);

uint16      iic_read_16bit_register     (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name);
void        iic_read_16bit_registers    (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, uint16 *data, uint32 len);

void        iic_transfer_8bit_array     (iic_index_enum iic_n, uint8 target_addr, const uint8 *write_data, uint32 write_len, uint8 *read_data, uint32 read_len);
void        iic_transfer_16bit_array    (iic_index_enum iic_n, uint8 target_addr, const uint16 *write_data, uint32 write_len, uint16 *read_data, uint32 read_len);

void        iic_sccb_write_register     (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 data);
uint8       iic_sccb_read_register      (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name);

void        iic_init                    (iic_index_enum iic_n, uint8 addr, uint32 speed, iic_scl_pin_enum scl_pin, iic_sda_pin_enum sda_pin);

#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // 兼容旧版本开源库接口名称

#endif

#endif
