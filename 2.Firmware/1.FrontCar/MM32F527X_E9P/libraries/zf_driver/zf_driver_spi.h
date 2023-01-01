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

#ifndef _zf_driver_spi_h_
#define _zf_driver_spi_h_

#include "hal_spi.h"

#include "zf_common_typedef.h"

#define SPI_SPEED_PRIORITY                                                      // SPI 通信速度优先

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // SPI1 引脚 SCK
    SPI1_SCK_A5         = 0x00550,                                              // 0x 005[A5]  5[AF5] 0[SPI1]
    SPI1_SCK_B3         = 0x02350,                                              // 0x 023[B3]  5[AF5] 0[SPI1]
    SPI1_SCK_E12        = 0x08C50,                                              // 0x 08C[E12] 5[AF5] 0[SPI1]
    SPI1_SCK_F7         = 0x0A750,                                              // 0x 0A7[F7]  5[AF5] 0[SPI1]

    // SPI2 引脚 SCK
    SPI2_SCK_B10        = 0x02A51,                                              // 0x 02A[B10] 5[AF5] 1[SPI2]
    SPI2_SCK_B13        = 0x02D51,                                              // 0x 02D[B13] 5[AF5] 1[SPI2]
    SPI2_SCK_D3         = 0x06351,                                              // 0x 063[D3]  5[AF5] 1[SPI2]
    SPI2_SCK_E2         = 0x08251,                                              // 0x 082[E2]  5[AF5] 1[SPI2]
    SPI2_SCK_F1         = 0x0A151,                                              // 0x 0A1[F1]  5[AF5] 1[SPI2]
    SPI2_SCK_G13        = 0x0CD51,                                              // 0x 0CD[G13] 5[AF5] 1[SPI2]

    // SPI3 引脚 SCK
    SPI3_SCK_B3         = 0x02362,                                              // 0x 023[B3]  6[AF6] 2[SPI3]
    SPI3_SCK_C10        = 0x04A62,                                              // 0x 04A[C10] 6[AF6] 2[SPI3]
    SPI3_SCK_D4         = 0x06452,                                              // 0x 064[D4]  5[AF5] 2[SPI3]
    SPI3_SCK_D12        = 0x06C62,                                              // 0x 06C[D12] 6[AF6] 2[SPI3]
}spi_sck_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // SPI1 引脚 MOSI
    SPI1_MOSI_A7        = 0x00750,                                              // 0x 007[A7]  5[AF5] 0[SPI1]
    SPI1_MOSI_B5        = 0x02550,                                              // 0x 025[B5]  5[AF5] 0[SPI1]
    SPI1_MOSI_E14       = 0x08E50,                                              // 0x 08E[E14] 5[AF5] 0[SPI1]
    SPI1_MOSI_F9        = 0x0A950,                                              // 0x 0A9[F9]  5[AF5] 0[SPI1
    SPI1_MOSI_F11       = 0x0AB50,                                              // 0x 0AB[F11] 5[AF5] 0[SPI1]

    // SPI2 引脚 MOSI
    SPI2_MOSI_B15       = 0x02F51,                                              // 0x 02F[B15] 5[AF5] 1[SPI2]
    SPI2_MOSI_C3        = 0x04351,                                              // 0x 043[C3]  5[AF5] 1[SPI2]
    SPI2_MOSI_E6        = 0x08651,                                              // 0x 086[E6]  5[AF5] 1[SPI2]
    SPI2_MOSI_G14       = 0x0CE51,                                              // 0x 0CE[G14] 5[AF5] 1[SPI2]

    // SPI3 引脚 MOSI
    SPI3_MOSI_B5        = 0x02562,                                              // 0x 025[B5]  6[AF6] 2[SPI3]
    SPI3_MOSI_C12       = 0x04C62,                                              // 0x 04C[C12] 6[AF6] 2[SPI3]
    SPI3_MOSI_D6        = 0x06652,                                              // 0x 066[D6]  5[AF5] 2[SPI3]
    SPI3_MOSI_D14       = 0x06E62,                                              // 0x 06E[D14] 6[AF6] 2[SPI3]
}spi_mosi_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    SPI_MISO_NULL       = 0xFFFFF,                                              // 不使用硬件 MISO 引脚就填这个

    // SPI1 引脚 MISO
    SPI1_MISO_A6        = 0x00650,                                              // 0x 006[A6]  5[AF5] 0[SPI1]
    SPI1_MISO_B4        = 0x02450,                                              // 0x 024[B4]  5[AF5] 0[SPI1]
    SPI1_MISO_E13       = 0x08D50,                                              // 0x 08D[E13] 5[AF5] 0[SPI1]
    SPI1_MISO_F8        = 0x0A850,                                              // 0x 0A8[F8]  5[AF5] 0[SPI1]

    // SPI2 引脚 MISO
    SPI2_MISO_B14       = 0x02E51,                                              // 0x 02E[B14] 5[AF5] 1[SPI2]
    SPI2_MISO_C2        = 0x04251,                                              // 0x 042[C2]  5[AF5] 1[SPI2]
    SPI2_MISO_C6        = 0x04651,                                              // 0x 046[C6]  5[AF5] 1[SPI2]
    SPI2_MISO_E5        = 0x08551,                                              // 0x 085[E5]  5[AF5] 1[SPI2]
    SPI2_MISO_G12       = 0x0CC51,                                              // 0x 0CC[G12] 5[AF5] 1[SPI2]

    // SPI3 引脚 MISO
    SPI3_MISO_B4        = 0x02462,                                              // 0x 024[B4]  6[AF6] 2[SPI3]
    SPI3_MOSI_C7        = 0x04752,                                              // 0x 047[C7]  5[AF5] 2[SPI3]
    SPI3_MOSI_C11       = 0x04B62,                                              // 0x 04B[C11] 6[AF6] 2[SPI3]
    SPI3_MOSI_D5        = 0x06552,                                              // 0x 065[D5]  5[AF5] 2[SPI3]
    SPI3_MOSI_D13       = 0x06D62,                                              // 0x 06D[D13] 6[AF6] 2[SPI3]
}spi_miso_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    SPI_CS_NULL         = 0xFFFFF,                                              // 不使用硬件 CS 引脚就填这个

    // SPI1 引脚 CS
    SPI1_CS_A4         = 0x00450,                                               // 0x 004[A4]  5[AF5] 0[SPI1]
    SPI1_CS_A15        = 0x00F50,                                               // 0x 00F[A15] 5[AF5] 0[SPI1]
    SPI1_CS_B6         = 0x02650,                                               // 0x 026[B6]  5[AF5] 0[SPI1]
    SPI1_CS_E11        = 0x08B50,                                               // 0x 08B[E11] 5[AF5] 0[SPI1]
    SPI1_CS_F6         = 0x0A650,                                               // 0x 0A6[F6]  5[AF5] 0[SPI1]

    // SPI2 引脚 CS
    SPI2_CS_B9         = 0x02951,                                               // 0x 029[B9]  5[AF5] 1[SPI2]
    SPI2_CS_B12        = 0x02C51,                                               // 0x 02C[B12] 5[AF5] 1[SPI2]
    SPI2_CS_E3         = 0x08351,                                               // 0x 083[E3]  5[AF5] 1[SPI2]
    SPI2_CS_E4         = 0x08451,                                               // 0x 084[E4]  5[AF5] 1[SPI2]
    SPI2_CS_F0         = 0x0A051,                                               // 0x 0A0[F0]  5[AF5] 1[SPI2]
    SPI2_CS_G8         = 0x0C851,                                               // 0x 0C8[G8]  5[AF5] 1[SPI2]

    // SPI3 引脚 CS
    SPI3_CS_A4         = 0x00462,                                               // 0x 004[A4]  6[AF6] 2[SPI3]
    SPI3_CS_A15        = 0x00F62,                                               // 0x 00F[A15] 6[AF6] 2[SPI3]
    SPI3_CS_B6         = 0x02662,                                               // 0x 026[B6]  6[AF6] 2[SPI2]
    SPI3_CS_D7         = 0x06752,                                               // 0x 067[D7]  5[AF5] 2[SPI3]
    SPI3_CS_D15        = 0x06F62,                                               // 0x 06F[D15] 6[AF6] 2[SPI3]
}spi_cs_pin_enum;

typedef enum                                                                    // 枚举 SPI 模式 此枚举定义不允许用户修改
{
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3,
}spi_mode_enum;

typedef enum                                                                    // 枚举 SPI 编号 此枚举定义不允许用户修改
{
    SPI_1 = 0,
    SPI_2,
    SPI_3,
}spi_index_enum;

void        spi_write_8bit                  (spi_index_enum spi_n, const uint8 data);
void        spi_write_8bit_array            (spi_index_enum spi_n, const uint8 *data, uint32 len);

void        spi_write_16bit                 (spi_index_enum spi_n, const uint16 data);
void        spi_write_16bit_array           (spi_index_enum spi_n, const uint16 *data, uint32 len);

void        spi_write_8bit_register         (spi_index_enum spi_n, const uint8 register_name, const uint8 data);
void        spi_write_8bit_registers        (spi_index_enum spi_n, const uint8 register_name, const uint8 *data, uint32 len);

void        spi_write_16bit_register        (spi_index_enum spi_n, const uint16 register_name, const uint16 data);
void        spi_write_16bit_registers       (spi_index_enum spi_n, const uint16 register_name, const uint16 *data, uint32 len);

uint8       spi_read_8bit                   (spi_index_enum spi_n);
void        spi_read_8bit_array             (spi_index_enum spi_n, uint8 *data, uint32 len);

uint16      spi_read_16bit                  (spi_index_enum spi_n);
void        spi_read_16bit_array            (spi_index_enum spi_n, uint16 *data, uint32 len);

uint8       spi_read_8bit_register          (spi_index_enum spi_n, const uint8 register_name);
void        spi_read_8bit_registers         (spi_index_enum spi_n, const uint8 register_name, uint8 *data, uint32 len);

uint16      spi_read_16bit_register         (spi_index_enum spi_n, const uint16 register_name);
void        spi_read_16bit_registers        (spi_index_enum spi_n, const uint16 register_name, uint16 *data, uint32 len);

void        spi_transfer_8bit               (spi_index_enum spi_n, const uint8 *write_buffer, uint8 *read_buffer, uint32 len);
void        spi_transfer_16bit              (spi_index_enum spi_n, const uint16 *write_buffer, uint16 *read_buffer, uint32 len);

void        spi_init                        (spi_index_enum spi_n, spi_mode_enum mode, uint32 baud, spi_sck_pin_enum sck_pin, spi_mosi_pin_enum mosi_pin, spi_miso_pin_enum miso_pin, spi_cs_pin_enum cs_pin);

#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // 兼容旧版本开源库接口名称
#define spi_mosi(spi_n, mosi, miso, len)    (spi_transfer_8bit((spi_n), (mosi), (miso), (len)))
#endif

#endif
