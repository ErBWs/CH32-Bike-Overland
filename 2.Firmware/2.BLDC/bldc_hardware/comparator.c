


#include "ch32v30x_opa.h"
#include "zf_driver_gpio.h"

#include "comparator.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �˷ų�ʼ��
//  @param      motor_index    �������
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void comparator_init(motor_index_enum motor_index)
{
    if(motor_index == MOTOR_1)
    {
        OPA_InitTypeDef  OPA_InitStructure={0};

        gpio_init(B10, GPI, 0, GPI_FLOATING_IN);    // OPA_CHN_PIN ��ʼ��
        gpio_init(B14, GPI, 0, GPI_FLOATING_IN);    // OPA_CHP_PIN ��ʼ��
        gpio_init(A2, GPI, 0, GPI_FLOATING_IN);     // OPA_CHOUT_PIN ��ʼ��

        OPA_InitStructure.OPA_NUM = OPA2;
        OPA_InitStructure.PSEL=     CHP0;
        OPA_InitStructure.NSEL=     CHN0;
        OPA_InitStructure.Mode=     OUT_IO_OUT0;
        OPA_Init(&OPA_InitStructure);               // OPA2��ʼ��

        OPA_Cmd(OPA2,ENABLE);                       // OPA2ʹ��
    }
    else if(motor_index == MOTOR_2)
    {
        OPA_InitTypeDef  OPA_InitStructure={0};

        gpio_init(C4, GPI, 0, GPI_FLOATING_IN);     // OPA_CHN_PIN ��ʼ��
        gpio_init(C3, GPI, 0, GPI_FLOATING_IN);     // OPA_CHP_PIN ��ʼ��
        gpio_init(E8, GPI, 0, GPI_FLOATING_IN);     // OPA_CHOUT_PIN ��ʼ��

        OPA_InitStructure.OPA_NUM = OPA4;
        OPA_InitStructure.PSEL=     CHP1;
        OPA_InitStructure.NSEL=     CHN1;
        OPA_InitStructure.Mode=     OUT_IO_OUT1;
        OPA_Init(&OPA_InitStructure);               // OPA4��ʼ��

        OPA_Cmd(OPA4,ENABLE);                       // OPA4ʹ��
    }
}





