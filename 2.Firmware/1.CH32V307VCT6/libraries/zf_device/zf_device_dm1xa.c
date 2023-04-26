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

#include "zf_common_debug.h"
#include "zf_driver_delay.h"
#include "zf_driver_exti.h"
#include "zf_driver_timer.h"

#include "zf_device_dm1xa.h"

static uint16                   dm1xa_distance_mm   = 6800;
static uint32                   dm1xa_plus_count    = 0;
//static uint32                   dm1xa_match_count   = 0;
static dm1xa_type_enum          dm1xa_type          = DM1XA_NO_INIT;
static dm1xa_ranging_state_enum dm1xa_ranging_state = DM1XA_RECEIVER_RANGING_NO_SIGNAL;

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DM1XA 声信号 / 反馈信号 外部中断回调函数
// 参数说明     void        无
// 参数说明     void        无
// 使用示例     dm1xa_sound_callback();
// 备注信息     这个函数需要放在 DM1XA_FB_PIN / DM1XA_S_PIN 对应的外部中断服务函数里
//-------------------------------------------------------------------------------------------------------------------
void dm1xa_sound_callback (void)
{
    switch(dm1xa_type)
    {
        case DM1XA_NO_INIT:                                                     // 未初始化 退出
        {
        }break;
        case DM1XA_CHECK_TYPE:                                                  // 初始化阶段
        {
            dm1xa_plus_count ++;                                                // 对 FB 或者 sound 信号计数
        }break;
        case DM1XA_TRANSMITTER:                                                 // DM1TA 模块发起测距
        {
            dm1xa_plus_count ++;                                                // 对 FB 信号计数
            if(DM1XA_FB_SEND <= dm1xa_plus_count)                               // 达到规定的 DM1XA_FB_SEND 计数
            {
                gpio_low(DM1XA_EN_PIN);                                         // 停止发送测距信号
                dm1xa_plus_count = 0;                                           // 清空计数
            }
        }break;
        case DM1XA_RECEIVER:                                                    // DM1RA 获取测距信号
        {
            if(DM1XA_RECEIVER_RANGING_WAIT_SOUND == dm1xa_ranging_state)        // 已经获取光信号 证明本次信号有效
            {
                if(gpio_get_level(DM1XA_S_PIN))                                 // 声信号为高 是一个完整脉冲
                {
                    if(150 < timer_get(DM1XA_TIM_INDEX) - dm1xa_plus_count)     // 判断这个声信号脉冲是否是低于 150us 的干扰噪声
                    {
                        timer_clear(DM1XA_TIM_INDEX);                           // 清空时间
                        dm1xa_distance_mm = (float)dm1xa_plus_count * DM1XA_SOUND_SPEED_MM_PER_US;	// 计算距离值 毫米单位
                        dm1xa_ranging_state = DM1XA_RECEIVER_RANGING_SUCCESS;   // 测距信息更新为完成测距
                    }
                }
                else                                                            // 声信号为低 证明是脉冲起始
                {
                    dm1xa_plus_count = timer_get(DM1XA_TIM_INDEX);              // 记录声光时间差
                }
            }
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DM1XA 光信号 外部中断回调函数
// 参数说明     void        无
// 参数说明     void        无
// 使用示例     dm1xa_light_callback();
// 备注信息     这个函数需要放在 DM1XA_EN_PIN / DM1XA_L_PIN 对应的外部中断服务函数里
//-------------------------------------------------------------------------------------------------------------------
void dm1xa_light_callback (void)
{
    switch(dm1xa_type)
    {
        case DM1XA_NO_INIT:                                                     // 未初始化 退出
        case DM1XA_CHECK_TYPE:                                                  // 初始化阶段
        case DM1XA_TRANSMITTER:                                                 // DM1TA 模块发起测距
        {
        }break;
        case DM1XA_RECEIVER:                                                    // DM1RA 获取测距信号
        {
            timer_clear(DM1XA_TIM_INDEX);                                       // 清空时间 准备获取声光时间差
            dm1xa_ranging_state = DM1XA_RECEIVER_RANGING_WAIT_SOUND;            // 标记获取到光信号
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DM1RA 模块 获取测距结果数据
// 参数说明     void        无
// 返回参数     uint16      距离信息 6800 为超时默认距离
// 使用示例     uint16 distance_mm = dm1xa_receiver_ranging();
// 备注信息     更新距离信息
//
//              需要注意 dm1xa_receiver_ranging 的调用周期务必控制在 10-20ms 这个区间
//              调用周期决定了最大测距距离 换算公式基本等于 period * 343.2 mm
//              那么 10-20ms 的调用周期区间对应 3432-6864mm 的最大测距范围
//              如果 dm1xa_receiver_ranging 的调用周期不在这个范围
//              那么可能出现本驱动的测距信息异常
//-------------------------------------------------------------------------------------------------------------------
uint16 dm1xa_receiver_ranging (void)
{
    switch(dm1xa_ranging_state)
    {
        case DM1XA_RECEIVER_RANGING_NO_SIGNAL:                                  // 无测距信号
        case DM1XA_RECEIVER_RANGING_WAIT_SOUND:                                 // 正获取测距信号
        {
            if(DM1XA_RECEIVER_TIMEROUT_US <= timer_get(DM1XA_TIM_INDEX))        // 如果距离上次光信号不超过 30ms
            {
                dm1xa_distance_mm = 6800;                                       // 恢复默认最大输出值
            }
        }break;
        case DM1XA_RECEIVER_RANGING_SUCCESS:                                    // 完成测距信息
        {
            dm1xa_ranging_state = DM1XA_RECEIVER_RANGING_NO_SIGNAL;             // 标记测距信号恢复默认
        }break;
        default:
        {
        }break;
    }
    return dm1xa_distance_mm;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DM1TA 模块 发送一组测距信号
// 参数说明     void        无
// 返回参数     void        无
// 使用示例     dm1xa_transmitter_ranging();
// 备注信息     发送完成后它会自己通过定时器控制
//              这个函数用于使用 DM1TA 发起一次测距
//              随后 DM1RA 将自动触发一次测距更新距离信息
//
//              需要注意 dm1xa_transmitter_ranging 的调用周期务必控制在 10-20ms 这个区间
//              调用周期决定了最大测距距离 换算公式基本等于 period * 343.2 mm
//              那么 10-20ms 的调用周期区间对应 3432-6864mm 的最大测距范围
//              如果 dm1xa_transmitter_ranging 的调用周期不在这个范围
//              那么可能出现本驱动的测距信息异常
//-------------------------------------------------------------------------------------------------------------------
void dm1xa_transmitter_ranging (void)
{
    gpio_high(DM1XA_EN_PIN);                                                    // 拉高 EN 开启一次测距信息发送
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     初始化 超声波 模块
// 参数说明     void                    无
// 返回参数     dm1xa_error_code_enum   DM1XA_NO_ERROR-初始化成功
// 使用示例     dm1xa_init();
// 备注信息     会自动识别是 DM1TA 模块还是 DM1RA 模块
//-------------------------------------------------------------------------------------------------------------------
dm1xa_error_code_enum dm1xa_init (void)
{
    dm1xa_error_code_enum return_state = DM1XA_NO_ERROR;

    do
    {
        dm1xa_distance_mm = 0;
        dm1xa_type = DM1XA_CHECK_TYPE;                                          // 模块状态标记为类型确认模式

        gpio_init(DM1XA_S_PIN, GPI, GPIO_LOW, GPI_PULL_DOWN);                   // 两个引脚设置为下拉输入模式
        gpio_init(DM1XA_L_PIN, GPI, GPIO_LOW, GPI_PULL_DOWN);                   // 两个引脚设置为下拉输入模式

        int16 i = DM1XA_INIT_MAX_COUNT;
        while(i --)
        {
            if(gpio_get_level(DM1XA_S_PIN) && gpio_get_level(DM1XA_L_PIN))      // 两个都是高电平 那么可能是 DM1RA 模块
            {
                dm1xa_type = DM1XA_RECEIVER;
                dm1xa_ranging_state = DM1XA_RECEIVER_RANGING_NO_SIGNAL;
                exti_init(DM1XA_S_PIN, EXTI_TRIGGER_BOTH);                      // 引脚初始化为外部中断输入
                exti_init(DM1XA_L_PIN, EXTI_TRIGGER_FALLING);                   // 引脚初始化为外部中断输入
                timer_init(DM1XA_TIM_INDEX, TIMER_US);                          // 微秒计时
                timer_clear(DM1XA_TIM_INDEX);                                   // 清空计数
                timer_start(DM1XA_TIM_INDEX);                                   // 启动定时器
                break;
            }
            system_delay_us(100);
        }
        if(0 > i)
        {
            exti_init(DM1XA_FB_PIN, EXTI_TRIGGER_FALLING);
            gpio_init(DM1XA_EN_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
            dm1xa_plus_count = 0;
            gpio_high(DM1XA_EN_PIN);
            system_delay_us(210);
            gpio_low(DM1XA_EN_PIN);
            if(6 < dm1xa_plus_count && 10 > dm1xa_plus_count)
            {
                dm1xa_type = DM1XA_TRANSMITTER;
                dm1xa_plus_count = 0;
            }
            else
            {
                dm1xa_type = DM1XA_NO_INIT;
                return_state = DM1XA_TYPE_ERROR;
                break;
            }
        }
    }while(0);

    return return_state;
}
