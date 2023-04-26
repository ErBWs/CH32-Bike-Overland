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
* 文件名称          zf_device_dm1xa
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                             备注
* 2023-03-18        大W            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   有去模块(无MCU版本 模块标识型号<DM1TA>)
*                   模块管脚            单片机管脚
*                   FB                  查看 zf_device_dm1xa.h 中 DM1XA_FB_PIN 宏定义
*                   EN                  查看 zf_device_dm1xa.h 中 DM1XA_EN_PIN 宏定义
*                   5V                  5V 电源
*                   GND                 电源地
*                   ------------------------------------
*                   ------------------------------------
*                   有来模块(无MCU版本 模块标识型号<DM1RA>)
*                   模块管脚            单片机管脚
*                   S                   查看 zf_device_dm1xa.h 中 DM1XA_S_PIN  宏定义
*                   L                   查看 zf_device_dm1xa.h 中 DM1XA_L_PIN  宏定义
*                   5V                  5V 电源
*                   GND                 电源地
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _ZF_DEVICE_DM1XA_H_
#define _ZF_DEVICE_DM1XA_H_

#include "zf_common_typedef.h"

// 需要注意 dm1xa_transmitter_ranging / dm1xa_receiver_ranging 的调用周期
// 务必控制在 10-20ms 这个区间
// 
// 调用周期决定了最大测距距离 换算公式基本等于 period * 343.2 mm
// 那么 10-20ms 的调用周期区间对应 3432-6864mm 的最大测距范围
// 
// 如果 dm1xa_transmitter_ranging / dm1xa_receiver_ranging
// 的调用周期不在 10-20ms 这个区间
// 那么可能出现本驱动的测距信息异常

// DM1TA 模块 引脚对应
#define DM1XA_FB_PIN                        ( E15 )
#define DM1XA_EN_PIN                        ( E14 )

// DM1RA 模块 引脚对应
#define DM1XA_S_PIN                         ( E15 )
#define DM1XA_L_PIN                         ( E14 )

#define DM1XA_TIM_INDEX                     ( TIM_7 )                           // 固定使用一个定时器

#define DM1XA_SOUND_SPEED_MM_PER_US         ( 0.34 )                            // 定义声速 340M/s = 0.34 mm/us

#define DM1XA_FB_SEND                       ( 10 )                              // 每次测距 EN 上脉冲时长为 DM1XA_FB_SEND * 1000 / 38 微秒
#if (DM1XA_FB_SEND < 6 || DM1XA_FB_SEND > 100)                                  // 每次测距的载波数 最小 6 最大 100
#error "DM1XA_FB_SEND error,  it must be between 6 and 100"
#endif

#define DM1XA_INIT_MAX_COUNT                ( 100 )                             // 初始化尝试次数
#define DM1XA_RECEIVER_TIMEROUT_US          ( 30000 )                           // 超时设置 这里不允许用户修改

// DM1XA 模块错误识别码 用户不允许更改
typedef enum
{
    DM1XA_NO_ERROR,
    DM1XA_TYPE_ERROR,
}dm1xa_error_code_enum;

// DM1XA 模块错误识别码 用户不允许更改
typedef enum
{
    DM1XA_RECEIVER_RANGING_NO_SIGNAL,
    DM1XA_RECEIVER_RANGING_WAIT_SOUND,
    DM1XA_RECEIVER_RANGING_SUCCESS,
}dm1xa_ranging_state_enum;

// DM1XA 模块类型 用户不允许更改
typedef enum
{
    DM1XA_NO_INIT,
    DM1XA_CHECK_TYPE,
    DM1XA_TRANSMITTER,
    DM1XA_RECEIVER,
}dm1xa_type_enum;

void                    dm1xa_sound_callback        (void);
void                    dm1xa_light_callback        (void);
    
uint16                  dm1xa_receiver_ranging      (void);
void                    dm1xa_transmitter_ranging   (void);
dm1xa_error_code_enum   dm1xa_init                  (void);

#endif
