#include "en_switch.h"
#include "zf_common_headfile.h"

enable_switch_struct motor1_enable_switch;
enable_switch_struct motor2_enable_switch;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ʹ�ܿ���״̬
//  @param      *enable_switch  ʹ�ܿ��ؽṹ��ָ��
//  @return     uint8 0���� 1���ر�
//  @since
//-------------------------------------------------------------------------------------------------------------------
uint8 switch_check(enable_switch_struct *enable_switch)
{
    return(!gpio_get_level(enable_switch->switch_en_pin));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ʹ�ܿ��س�ʼ��
//  @param      motor_index     �������
//  @param      *enable_switch  ʹ�ܿ��ؽṹ��ָ��
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
