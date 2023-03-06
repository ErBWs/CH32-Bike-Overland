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
* 文件名称          zf_device_key
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
*                   // 一般是主板按键对应的引脚
*                   KEY1/S1             查看 zf_device_key.h 中 KEY_LIST[0]
*                   KEY2/S2             查看 zf_device_key.h 中 KEY_LIST[1]
*                   KEY3/S3             查看 zf_device_key.h 中 KEY_LIST[2]
*                   KEY4/S4             查看 zf_device_key.h 中 KEY_LIST[3]
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_key_h_
#define _zf_device_key_h_

#include "zf_common_debug.h"

#include "zf_driver_gpio.h"

// 定义按键引脚 用户可以新增可以修改 默认定义四个按键
// 定义按键顺序对应下方 key_index_enum 枚举体中定义的顺序
// 如果用户可以新增按键 那么需要同步在下方 key_index_enum 枚举体中新增按键
#define KEY_LIST                    { E0 , E1 , E2 , E3 }

#define KEY_RELEASE_LEVEL           ( GPIO_HIGH )                               // 按键的默认状态 也就是按键释放状态的电平
#define KEY_MAX_SHOCK_PERIOD        ( 10        )                               // 按键消抖检测时长 单位毫秒 低于这个时长的信号会被认为是杂波抖动
#define KEY_LONG_PRESS_PERIOD       ( 1000      )                               // 最小长按时长 单位毫秒 高于这个时长的信号会被认为是长按动作

typedef enum
{
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_NUMBER,
}key_index_enum;                                                                // 按键索引 对应上方定义的按键引脚个数 默认定义四个按键

typedef enum
{
    KEY_RELEASE,                                                                // 按键释放状态
    KEY_SHORT_PRESS,                                                            // 按键短按状态
    KEY_LONG_PRESS,                                                             // 按键长按状态
}key_state_enum;

void            key_scanner             (void);
key_state_enum  key_get_state           (key_index_enum key_n);
void            key_clear_state         (key_index_enum key_n);
void            key_clear_all_state     (void);
void            key_init                (uint32 period);

#endif
