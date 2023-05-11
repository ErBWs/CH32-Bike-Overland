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
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                             备注
* 2023-03-31        大W            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "user_header.h"

#include "hall.h"
#include "pwm_output.h"
#include "pwm_input.h"
#include "led.h"
#include "operational_amplifier.h"
#include "comparator.h"
#include "motor.h"
#include "en_switch.h"
#include "encoder.h"
#include "move_filter.h"
#include "battery_adc.h"
#include "virtual_oscilloscope.h"




int main (void)
{
    // 初始化芯片时钟 工作频率为 144MHz
    clock_init(SYSTEM_CLOCK_144M);
    // 初始化默认 Debug UART
    debug_init();

    //------------------------电机1初始化-------------------------//
    // 初始化LED引脚
    led_init(MOTOR_1, &motor1_led);

    // 初始化运放，将采样电阻的电压进行放大，然后传递给比较器
    operational_amplifier_init(MOTOR_1);

    // 初始化比较器，用于实现堵转保护，比较器触发时自动关闭PWM输出，无需代码手动关闭
    comparator_init(MOTOR_1);

    // 滑动滤波初始化
    move_filter_init(&motor1_speed_filter);

    // 霍尔初始化
    hall_init(MOTOR_1, &motor1_hall);

    // pi闭环初始化
    closed_loop_pi_init(&motor1_closed_loop);

    // 速度曲线初始化
    motor_speed_curve_init(&motor1_control, &motor1_speed_filter);

    // 初始化输出速度与方向信息的引脚
    encoder_init(MOTOR_1, &motor1_encoder_out);

    // 输入信号捕获初始化
    pwm_input_init(MOTOR_1, &motor1_pwm_input_value);

    // 使能开关初始化
    switch_init(MOTOR_1, &motor1_enable_switch);

    // 电机adc引脚初始化
    motor_init(MOTOR_1, &motor1_control);

    // 设置电机1为N车飞轮电机
    motor_set_type(&motor1_control, BLDC_MOTOR_MOMENTUM);

    // N车飞轮极对数为7
    motor_set_polepairs(&motor1_control, 7);

    // 设置电机超前角度，60度
    motor_set_commutation_angle(&motor1_control, 60);

    // 初始化定时器1，用于输出互补PWM
    pwm_complementary_init(MOTOR_1, &motor1_pwm_output);

    //------------------------电机1初始化-------------------------//

    //------------------------电机2初始化-------------------------//
    // 初始化LED引脚
    led_init(MOTOR_2, &motor2_led);

    // 初始化运放，将采样电阻的电压进行放大，然后传递给比较器
    operational_amplifier_init(MOTOR_2);

    // 初始化比较器，用于实现堵转保护，比较器触发时自动关闭PWM输出，无需代码手动关闭
    comparator_init(MOTOR_2);

    // 滑动滤波初始化
    move_filter_init(&motor2_speed_filter);

    // 霍尔初始化
    hall_init(MOTOR_2, &motor2_hall);

    // pi闭环初始化
    closed_loop_pi_init(&motor2_closed_loop);

    // 速度曲线初始化
    motor_speed_curve_init(&motor2_control, &motor2_speed_filter);

    // 初始化输出速度与方向信息的引脚
    encoder_init(MOTOR_2, &motor2_encoder_out);

    // 输入信号捕获初始化
    pwm_input_init(MOTOR_2, &motor2_pwm_input_value);

    // 使能开关初始化
    switch_init(MOTOR_2, &motor2_enable_switch);

    // 电机adc引脚初始化
    motor_init(MOTOR_2, &motor2_control);

    // 设置电机2为N车飞轮电机
    motor_set_type(&motor2_control, BLDC_MOTOR_MOMENTUM);

    // N车飞轮极对数为7
    motor_set_polepairs(&motor2_control, 7);

    // 设置电机超前角度，60度
    motor_set_commutation_angle(&motor2_control, 60);

    // 初始化定时器9，用于输出互补PWM
    pwm_complementary_init(MOTOR_2, &motor2_pwm_output);
    //------------------------电机2初始化-------------------------//

//    // 初始化adc通道，adc用于采集电源电压
//    battery_adc_init();

    // 初始化定时器6，用于PI闭环计算
    pit_ms_init(TIM6_PIT, 1);

    while(1)
    {

//        // 发送数据到虚拟示波器 虚拟示波器下载链接 https://pan.baidu.com/s/198CMXTZsbI3HAEqNXDngBw
//        virtual_oscilloscope_data_conversion(motor1_control.speed_now/10, motor1_pwm_input_value.cycle*1000,
//                                             motor2_control.speed_now/10, motor2_pwm_input_value.cycle*1000);
//        uart_write_buffer(DEBUG_UART_INDEX, virtual_oscilloscope_data, sizeof(virtual_oscilloscope_data));

        vofaData[0] = motor1_control.speed_now/10;          // Motor1 speed
        vofaData[1] = motor1_pwm_input_value.cycle*1000;    // Motor1 speed input
        vofaData[2] = motor2_control.speed_now/10;          // Motor2 speed
        vofaData[3] = motor2_pwm_input_value.cycle*1000;    // Motor2 speed input

        // 检查电机状态然后控制对应的LED灯点亮或熄灭
        led_control(&motor1_led, &motor1_control, &motor1_pwm_output);
        led_control(&motor2_led, &motor2_control, &motor2_pwm_output);

//        VofaLittleEndianSendFrame();
    }
}