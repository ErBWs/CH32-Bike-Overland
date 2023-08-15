


#include "ch32v30x_opa.h"
#include "zf_driver_gpio.h"

#include "comparator.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      运放初始化
//  @param      motor_index    电机索引
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void comparator_init(motor_index_enum motor_index)
{
    if(motor_index == MOTOR_1)
    {
        OPA_InitTypeDef  OPA_InitStructure={0};

        gpio_init(B10, GPI, 0, GPI_FLOATING_IN);    // OPA_CHN_PIN 初始化
        gpio_init(B14, GPI, 0, GPI_FLOATING_IN);    // OPA_CHP_PIN 初始化
        gpio_init(A2, GPI, 0, GPI_FLOATING_IN);     // OPA_CHOUT_PIN 初始化

        OPA_InitStructure.OPA_NUM = OPA2;
        OPA_InitStructure.PSEL=     CHP0;
        OPA_InitStructure.NSEL=     CHN0;
        OPA_InitStructure.Mode=     OUT_IO_OUT0;
        OPA_Init(&OPA_InitStructure);               // OPA2初始化

        OPA_Cmd(OPA2,ENABLE);                       // OPA2使能
    }
    else if(motor_index == MOTOR_2)
    {
        OPA_InitTypeDef  OPA_InitStructure={0};

        gpio_init(C4, GPI, 0, GPI_FLOATING_IN);     // OPA_CHN_PIN 初始化
        gpio_init(C3, GPI, 0, GPI_FLOATING_IN);     // OPA_CHP_PIN 初始化
        gpio_init(E8, GPI, 0, GPI_FLOATING_IN);     // OPA_CHOUT_PIN 初始化

        OPA_InitStructure.OPA_NUM = OPA4;
        OPA_InitStructure.PSEL=     CHP1;
        OPA_InitStructure.NSEL=     CHN1;
        OPA_InitStructure.Mode=     OUT_IO_OUT1;
        OPA_Init(&OPA_InitStructure);               // OPA4初始化

        OPA_Cmd(OPA4,ENABLE);                       // OPA4使能
    }
}





