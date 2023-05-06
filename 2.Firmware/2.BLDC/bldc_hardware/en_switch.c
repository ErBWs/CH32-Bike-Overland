#include "en_switch.h"
#include "zf_common_headfile.h"

enable_switch_struct motor1_enable_switch;
enable_switch_struct motor2_enable_switch;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      检测使能开关状态
//  @param      *enable_switch  使能开关结构体指针
//  @return     uint8 0：打开 1：关闭
//  @since
//-------------------------------------------------------------------------------------------------------------------
uint8 switch_check(enable_switch_struct *enable_switch)
{
    return(!gpio_get_level(enable_switch->switch_en_pin));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      使能开关初始化
//  @param      motor_index     电机索引
//  @param      *enable_switch  使能开关结构体指针
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void switch_init(motor_index_enum motor_index, enable_switch_struct *enable_switch)
{
    if(motor_index == MOTOR_1)
    {
        enable_switch->switch_en_pin = C11;
    }
    else if(motor_index == MOTOR_2)
    {
        enable_switch->switch_en_pin = E9;
    }

    gpio_init(enable_switch->switch_en_pin, GPI, 0, GPI_PULL_UP);
}
