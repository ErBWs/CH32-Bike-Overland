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
* 文件名称          zf_device_scc8660_dvp_dvp
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
*接线定义：
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   TXD                 查看 zf_device_scc8660_dvp.h 中 SCC8660_COF_UART_TX        宏定义
*                   RXD                 查看 zf_device_scc8660_dvp.h 中 SCC8660_COF_UART_RX        宏定义
*                   D0                  查看 zf_device_scc8660_dvp.h 中 SCC8660_D0_PIN             宏定义
*                   D1                  查看 zf_device_scc8660_dvp.h 中 SCC8660_D1_PIN             宏定义
*                   D2                  查看 zf_device_scc8660_dvp.h 中 SCC8660_D2_PIN             宏定义
*                   D3                  查看 zf_device_scc8660_dvp.h 中 SCC8660_D3_PIN             宏定义
*                   D4                  查看 zf_device_scc8660_dvp.h 中 SCC8660_D4_PIN             宏定义
*                   D5                  查看 zf_device_scc8660_dvp.h 中 SCC8660_D5_PIN             宏定义
*                   D6                  查看 zf_device_scc8660_dvp.h 中 SCC8660_D6_PIN             宏定义
*                   D7                  查看 zf_device_scc8660_dvp.h 中 SCC8660_D7_PIN             宏定义
*                   PCLK                查看 zf_device_scc8660_dvp.h 中 SCC8660_PCLK_PIN           宏定义
*                   VSYNC               查看 zf_device_scc8660_dvp.h 中 SCC8660_VSY_PIN            宏定义
*                   HSYNC               查看 zf_device_scc8660_dvp.h 中 SCC8660_HERF_PIN           宏定义
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_device_type.h"
#include "zf_device_camera.h"
#include "zf_driver_dvp.h"
#include "zf_driver_delay.h"
#include "zf_device_scc8660_dvp.h"

vuint8 scc8660_finish_flag = 0;                                                  // 一场图像采集完成标志位
uint16 scc8660_image[SCC8660_H][SCC8660_W];

// 需要配置到摄像头的数据 不允许在这修改参数
static int16 scc8660_set_confing_buffer[SCC8660_CONFIG_FINISH][2]=
{
    {SCC8660_INIT,              0},                                             // 摄像头开始初始化
    {SCC8660_AUTO_EXP,          SCC8660_AUTO_EXP_DEF},                          // 自动曝光
    {SCC8660_BRIGHT,            SCC8660_BRIGHT_DEF},                            // 亮度设置
    {SCC8660_FPS,               SCC8660_FPS_DEF},                               // 图像帧率
    {SCC8660_SET_COL,           SCC8660_W},                                     // 图像列数
    {SCC8660_SET_ROW,           SCC8660_H},                                     // 图像行数
    {SCC8660_PCLK_DIV,          SCC8660_PCLK_DIV_DEF},                          // PCLK分频系数
    {SCC8660_PCLK_MODE,         SCC8660_PCLK_MODE_DEF},                         // PCLK模式
    {SCC8660_COLOR_MODE,        SCC8660_COLOR_MODE_DEF},                        // 图像色彩模式
    {SCC8660_DATA_FORMAT,       SCC8660_DATA_FORMAT_DEF},                       // 输出数据格式
    {SCC8660_MANUAL_WB,         SCC8660_MANUAL_WB_DEF},                         // 手动白平衡

};

// 从摄像头内部获取到的配置数据 不允许在这修改参数
static int16 scc8660_get_confing_buffer[SCC8660_CONFIG_FINISH - 1][2]=
{
    {SCC8660_AUTO_EXP,          0},
    {SCC8660_BRIGHT,            0},                                             // 亮度设置
    {SCC8660_FPS,               0},                                             // 图像帧率
    {SCC8660_SET_COL,           0},                                             // 图像列数
    {SCC8660_SET_ROW,           0},                                             // 图像行数
    {SCC8660_PCLK_DIV,          0},                                             // PCLK分频系数
    {SCC8660_PCLK_MODE,         0},                                             // PCLK模式
    {SCC8660_COLOR_MODE,        0},                                             // 图像色彩模式
    {SCC8660_DATA_FORMAT,       0},                                             // 输出数据格式
    {SCC8660_MANUAL_WB,         0},                                             // 白平衡设置
};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     配置摄像头内部配置信息 内部调用
// 参数说明     buff            发送配置信息的地址
// 返回参数     uint8           1-失败 0-成功
// 使用示例     if(scc8660_set_config(scc8660_set_confing_buffer)){}
// 备注信息     调用该函数前请先初始化串口
//-------------------------------------------------------------------------------------------------------------------
static uint8 scc8660_set_config (int16 buff[SCC8660_CONFIG_FINISH][2])
{
    uint8 return_state = 1;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 loop_count = 0;
    uint32 uart_buffer_index = 0;

    // 设置参数  具体请参看问题锦集手册
    // 开始配置摄像头并重新初始化
    for(loop_count = SCC8660_MANUAL_WB; loop_count < SCC8660_SET_REG_DATA; loop_count --)
    {
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = buff[loop_count][0];
        temp = buff[loop_count][1];
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;
        uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

        system_delay_ms(2);
    }

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            if((0xff == uart_buffer[1]) || (0xff == uart_buffer[2]))
            {
                return_state = 0;
                break;
            }
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);

    // 以上部分对摄像头配置的数据全部都会保存在摄像头上51单片机的eeprom中
    // 利用set_exposure_time函数单独配置的曝光数据不存储在eeprom中
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取摄像头内部配置信息 内部调用
// 参数说明     buff            接收配置信息的地址
// 返回参数     uint8           1-失败 0-成功
// 使用示例     if(scc8660_get_config(scc8660_get_confing_buffer)){}
// 备注信息     调用该函数前请先初始化串口
//-------------------------------------------------------------------------------------------------------------------
static uint8 scc8660_get_config (int16 buff[SCC8660_CONFIG_FINISH-1][2])
{
    uint8 return_state = 0;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 loop_count = 0;
    uint32 uart_buffer_index = 0;

    for(loop_count = SCC8660_MANUAL_WB - 1; loop_count >= 1; loop_count --)
    {
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = SCC8660_GET_STATUS;
        temp = buff[loop_count][0];
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;
        uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

        timeout_count = 0;
        do
        {
            if(3 <= fifo_used(&camera_receiver_fifo))
            {
                uart_buffer_index = 3;
                fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
                buff[loop_count][1] = uart_buffer[1] << 8 | uart_buffer[2];
                break;
            }
            system_delay_ms(1);
        }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
        if(timeout_count > SCC8660_INIT_TIMEOUT)                                // 超时
        {
            return_state = 1;
            break;
        }
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SCC8660 通信串口回调函数
// 参数说明     void
// 返回参数     void
// 使用示例     scc8660_uart_handler();
// 备注信息     通过 zf_device_type.c 的接口调用 用户在使用默认设置时不需要关心
//-------------------------------------------------------------------------------------------------------------------
static void scc8660_uart_handler (void)
{
    uint8 data = 0;
    uart_query_byte(SCC8660_COF_UART, &data);
    if(0xA5 == data)
    {
        fifo_clear(&camera_receiver_fifo);
    }
    fifo_write_element(&camera_receiver_fifo, data);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SCC8660 场中断回调函数
// 参数说明     void
// 返回参数     void
// 使用示例     scc8660_vsync_handler();
// 备注信息     通过 zf_device_type.c 的接口调用 用户在使用默认设置时不需要关心
//-------------------------------------------------------------------------------------------------------------------
static void scc8660_dvp_handler (void)
{
    //已经修改为循环采集模式。不需要设置地址和开启DVP
    //DVP->DMA_BUF0 = (uint32)camera_buffer_addr;       // 恢复DMA地址
    scc8660_finish_flag = 1;                            // 摄像头采集完成标志位置1
    //已经修改为循环采集模式。不需要设置地址和开启DVP
    //DVP->CR0 |= RB_ENABLE;                            // 重新打开DVP，采集下一副图像
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取摄像头 ID
// 参数说明     void
// 返回参数     uint16          0-获取错误 N-版本号
// 使用示例     scc8660_get_id();                               // 调用该函数前请先初始化串口
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_get_id (void)
{
    uint16 temp;
    uint8  uart_buffer[4];
    uint16 timeout_count = 0;
    uint16 return_value = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_GET_WHO_AM_I;
    temp = 0;
    uart_buffer[2] = temp >> 8;
    uart_buffer[3] = (uint8)temp;
    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            return_value = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     单独设置摄像头曝光时间
// 参数说明     light           设置曝光时间越大图像越亮，摄像头收到后会根据分辨率及FPS计算最大曝光时间如果设置的数据过大，那么摄像头将会设置这个最大值
// 返回参数     uint16          数据
// 使用示例     scc8660_get_parameter(config);                                  // 调用该函数前请先初始化串口
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_get_parameter (uint16 config)
{
    uint8  uart_buffer[4];
    uint16 timeout_count = 0;
    uint16 return_value = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_GET_WHO_AM_I;
    uart_buffer[2] = 0x00;
    uart_buffer[3] = config;
    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            return_value = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取彩色摄像头固件版本
// 参数说明     void
// 返回参数     uint16          版本号
// 使用示例     scc8660_get_version();                                          // 调用该函数前请先初始化摄像头配置串口
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_get_version (void)
{
    uint16 temp;
    uint8  uart_buffer[4];
    uint16 timeout_count = 0;
    uint16 return_value = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_GET_STATUS;
    temp           = SCC8660_GET_VERSION;
    uart_buffer[2] = temp >> 8;
    uart_buffer[3] = (uint8)temp;

    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            return_value = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     单独设置图像亮度
// 参数说明     data            需要设置的亮度值
// 返回参数     uint8           1-失败 0-成功
// 使用示例     scc8660_set_bright(data);                                       // 通过该函数设置的参数，不会被51单片机保存
// 备注信息     调用该函数前请先初始化摄像头配置串口
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_set_bright (uint16 data)
{
    uint8 return_state = 0;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_SET_BRIGHT;
    uart_buffer[2] = data >> 8;
    uart_buffer[3] = (uint8)data;

    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            temp = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
    if((temp != data) || (SCC8660_INIT_TIMEOUT <= timeout_count))
    {
        return_state = 1;
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     单独设置白平衡
// 参数说明     data            需要设置的亮度值
// 返回参数     uint8           1-失败 0-成功
// 使用示例     scc8660_set_white_balance(data);                // 调用该函数前请先初始化摄像头配置串口
// 备注信息     通过该函数设置的参数，不会被51单片机保存
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_set_white_balance (uint16 data)
{
    uint8 return_state = 0;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_SET_MANUAL_WB;
    uart_buffer[2] = data >> 8;
    uart_buffer[3] = (uint8)data;

    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            temp = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
    if((temp != data) || (SCC8660_INIT_TIMEOUT <= timeout_count))
    {
        return_state = 1;
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     对摄像头内部寄存器进行写操作
// 参数说明     addr            摄像头内部寄存器地址
// 参数说明     data            需要写入的数据
// 返回参数     uint8           1-失败 0-成功
// 使用示例     scc8660_set_reg(addr, data);                    // 调用该函数前请先初始化串口
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_set_reg (uint8 addr, uint16 data)
{
    uint8 return_state = 0;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_SET_REG_ADDR;
    uart_buffer[2] = 0x00;
    uart_buffer[3] = (uint8)addr;
    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    system_delay_ms(10);
    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_SET_REG_DATA;
    temp           = data;
    uart_buffer[2] = temp >> 8;
    uart_buffer[3] = (uint8)temp;
    uart_write_buffer(SCC8660_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            temp = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_INIT_TIMEOUT > timeout_count ++);
    if((temp != data) || (SCC8660_INIT_TIMEOUT <= timeout_count))
    {
        return_state = 1;
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SCC8660(凌瞳摄像头)初始化 使用DVP接口
// 参数说明     NULL
// 返回参数     void
//  @since      v1.0
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_init(void)
{

    uint8 return_state = 0;

    // 初始换串口 配置摄像头
    uart_init(SCC8660_COF_UART, SCC8660_COF_BAUR, SCC8660_COF_UART_RX, SCC8660_COF_UART_TX);
    uart_rx_interrupt(SCC8660_COF_UART, 1);
    system_delay_ms(200);

    set_camera_type(CAMERA_COLOR, scc8660_uart_handler, scc8660_dvp_handler);
    camera_fifo_init();

    // 等待摄像头上电初始化成功 方式有两种：延时或者通过获取配置的方式 二选一
    // system_delay_ms(1000);                                                   // 延时方式

//    if(scc8660_set_config(scc8660_set_confing_buffer))
//    {
//        set_camera_type(NO_CAMERE, NULL, NULL, NULL);
//        return 1;
//    }
    scc8660_get_version();                                                      // 获取配置的方式

    do
    {
        if(scc8660_set_config(scc8660_set_confing_buffer))
        {
            // 如果程序在输出了断言信息 并且提示出错位置在这里
            // 那么就是串口通信出错并超时退出了
            // 检查一下接线有没有问题 如果没问题可能就是坏了
            zf_log(0, "SCC8660 set config error.");
            set_camera_type(NO_CAMERE, NULL, NULL);
            return_state = 1;
            break;
        }

        // 获取配置便于查看配置是否正确
        if(scc8660_get_config(scc8660_get_confing_buffer))
        {
            // 如果程序在输出了断言信息 并且提示出错位置在这里
            // 那么就是串口通信出错并超时退出了
            // 检查一下接线有没有问题 如果没问题可能就是坏了
            zf_log(0, "SCC8660 get config error.");
            set_camera_type(NO_CAMERE, NULL, NULL);
            return_state = 1;
            break;
        }

        // DVP引脚初始化
        dvp_gpio_init(
                SCC8660_D0_PIN, SCC8660_D1_PIN, SCC8660_D2_PIN, SCC8660_D3_PIN,
                SCC8660_D4_PIN, SCC8660_D5_PIN, SCC8660_D6_PIN, SCC8660_D7_PIN,
                SCC8660_PCLK_PIN, SCC8660_VSY_PIN, SCC8660_HERF_PIN);

        // DVP接口初始化
        dvp_camera_init((uint32 *)&scc8660_image[0], NULL, SCC8660_IMAGE_SIZE, 1);
    }while(0);

    return return_state;

}

