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
* 文件名称          zf_device_sdcard_spi
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
*                   硬件SPI通信
*                   SPC                 查看 SDCARD_SCK_PIN       宏定义
*                   SDI                 查看 SDCARD_MOSI_PIN  宏定义
*                   SDO                 查看 SDCARD_MISO_PIN  宏定义
*                   CS                  查看 SDCARD_CS_PIN        宏定义
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_font.h"
#include "zf_common_function.h"
#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_driver_soft_spi.h"
#include "zf_driver_spi.h"

#include "zf_device_sdcard_spi.h"

#if SDCARD_USER_SOFT_SPI
soft_spi_info_struct sdcard_spi_struct;
#define sdcard_spi_mosi(a,b,c,d)        soft_spi_transfer_8bit(&sdcard_spi_struct,b,c,d)
#else
#define sdcard_spi_mosi(a,b,c,d)        spi_transfer_8bit(a,b,c,d)
#endif

static volatile uint8 stat = STA_NOINIT;                                                // 卡状态
static uint8 card_type;                                                                 // 卡类型 0:MMC / 1:SDC / 2:Block addressing
static uint8 power_flag = 0;                                                            // Power flag

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SD-Card 发送命令
// 参数说明     cmd             命令
// 参数说明     arg             命令参数
// 返回参数     uint8           响应
// 使用示例     sd_send_cmd(CMD0, 0)
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 sd_send_cmd (uint8 cmd, uint32 arg)
{
    uint8 n = 10;
    uint8 args[6];

    /* wait SD ready */
    memset(args, 0xff, 6);
    sdcard_spi_mosi(SDCARD_SPI, &args[0], &args[1], 1);                                 // 查看状态
    if (args[1] != 0xFF)                                                                // SD-card 不在 Ready
        return 0xFF;

    args[0] = cmd;
    args[1] = (uint8_t)(arg >> 24);
    args[2] = (uint8_t)(arg >> 16);
    args[3] = (uint8_t)(arg >> 8);
    args[4] = (uint8_t)arg;
    if(cmd == CMD0)
        args[5] = 0x95;                                                                 // CRC for CMD0(0)
    else if(cmd == CMD8)
        args[5] = 0x87;                                                                 // CRC for CMD8(0x1AA)
    else
        args[5] = 1;
    sdcard_spi_mosi(SDCARD_SPI, args, NULL, 6);                                         // 发送命令

    memset(args, 0xff, 6);
    if (cmd == CMD12)                                                                   // 当 STOP_TRANSMISSION 时跳过一个 stuff 字节
    {
        sdcard_spi_mosi(SDCARD_SPI, args, NULL, 1);
    }

    do {
        sdcard_spi_mosi(SDCARD_SPI, &args[0], &args[1], 1);                             // 获取响应
    } while ((args[1] & 0x80) && --n);

    return args[1];
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SD-Card 开启供电
// 参数说明     void
// 返回参数     void
// 使用示例     sd_power_on();
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void sd_power_on (void) 
{
    uint8 args[10];
    uint32 cnt = 0x1FFF;
    memset(args, 0xff, 10);

    sd_power_on();
    SDCARD_CS(1);
    sdcard_spi_mosi(SDCARD_SPI, args, NULL, 10);                                        // 唤醒

    args[0] = CMD0;                                                                     // CMD0:GO_IDLE_STATE
    args[1] = 0;
    args[2] = 0;
    args[3] = 0;
    args[4] = 0;
    args[5] = 0x95;                                                                     // CRC

    SDCARD_CS(0);
    sdcard_spi_mosi(SDCARD_SPI, args, NULL, 6);

    args[0] = 0xff;
    while ((args[1] != 0x01) && cnt)                                                    // 等待响应
    {
        sdcard_spi_mosi(SDCARD_SPI, &args[0], &args[1], 1);                             // 读取
        cnt--;
    }

    SDCARD_CS(1);
    sdcard_spi_mosi(SDCARD_SPI, args, NULL, 1);                                         // 空闲

    power_flag = 1;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SD-Card 关闭供电
// 参数说明     void
// 返回参数     void
// 使用示例     sd_power_off();
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void sd_power_off(void) 
{
    power_flag = 0;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SD-Card 确认供电状态
// 参数说明     void
// 返回参数     void
// 使用示例     sd_check_power();
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 sd_check_power(void) 
{
    return power_flag;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SD-Card SPI 初始化并获取卡数据
// 参数说明     void
// 返回参数     uint8           初始化状态
// 使用示例     sdcard_spi_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 sdcard_spi_init (void)
{
    uint32 timer1 = 0;
    uint8 n, type, ocr[4];

    system_delay_ms(100);                                                               //上电延时

#if SDCARD_USER_SOFT_SPI
    soft_spi_init(&sdcard_spi_struct, SPI_MODE0, 1, SDCARD_SCK_PIN,
        SDCARD_MOSI_PIN, SDCARD_MISO_PIN, SOFT_SPI_PIN_NULL);
#else
    spi_init(SDCARD_SPI, SPI_MODE0, SDCARD_BAUDRATE,                                    // 硬件SPI初始化
        SDCARD_SCK_PIN, SDCARD_MOSI_PIN, SDCARD_MISO_PIN, SPI_CS_NULL);
#endif
    gpio_init(SDCARD_CS_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);

    type = 0;                                                                           // 未获取卡类型
    SDCARD_CS(0);                                                                       // 片选使能 选中卡

    if (sd_send_cmd(CMD0, 0) == 1)                                                      // 进入空闲模式
    {
        timer1 = 1000;                                                                  // 一秒左右的初始化时间

        if (sd_send_cmd(CMD8, 0x1AA) == 1)                                              // SDC V2+ 接受 CMD8 命令 http://elm-chan.org/docs/mmc/mmc_e.html
        {
            memset(ocr, 0xff, 4);
            sdcard_spi_mosi(SDCARD_SPI, ocr, ocr, 4);                                   // 操作条件寄存器

            if (ocr[2] == 0x01 && ocr[3] == 0xAA)                                       // 电压等级 2.7-3.6V
            {
                do {
                    if (sd_send_cmd(CMD55, 0) <= 1 &&
                        sd_send_cmd(CMD41, 1UL << 30) == 0)                             // 带有 HCS 位的 ACMD41
                        break;
                    system_delay_ms(1);
                } while (timer1--);

                if (timer1-- && sd_send_cmd(CMD58, 0) == 0)
                {
                    memset(ocr, 0xff, 4);
                    sdcard_spi_mosi(SDCARD_SPI, ocr, ocr, 4);                           // 读取 CCS

                    type = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;                // 判断类型 SDv2 (HC or SC)
                    system_delay_ms(1);
                }
            }
        }
        else
        {
            type = (sd_send_cmd(CMD55, 0) <= 1 && sd_send_cmd(CMD41, 0) <= 1) ? CT_SD1 : CT_MMC; // 判断类型 SDC V1 or MMC

            do
            {
                if (type == CT_SD1)
                {
                    if (sd_send_cmd(CMD55, 0) <= 1 && sd_send_cmd(CMD41, 0) == 0)       // 等待响应 ACMD41
                        break;
                }
                else
                {
                    if (sd_send_cmd(CMD1, 0) == 0)                                      // 等待响应 CMD1
                        break;
                }

            } while (timer1--);

            if (!timer1 || sd_send_cmd(CMD16, 512) != 0)                                // 如果没识别出来什么卡 或者获取到扇区信息
                type = 0;
        }
    }
    card_type = type;

    /* Idle */
    SDCARD_CS(1);
    memset(ocr, 0xff, 4);
    sdcard_spi_mosi(SDCARD_SPI, ocr, NULL, 1);                                          // 空字节读取

    if (type)
        stat &= ~STA_NOINIT;                                                            // 初始化成功 清空状态
    else
        sd_power_off();                                                                 // 初始化失败 取消上电状态

    return stat;
}









