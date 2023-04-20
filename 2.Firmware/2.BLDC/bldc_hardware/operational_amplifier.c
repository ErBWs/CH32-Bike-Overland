
#include "ch32v30x_opa.h"
#include "zf_driver_gpio.h"
#include "operational_amplifier.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief      运放初始化
//  @param      motor_index    电机索引
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void operational_amplifier_init(motor_index_enum motor_index)
{
    if(motor_index == MOTOR_1)
    {
        OPA_InitTypeDef  OPA_InitStructure={0};

        gpio_init(B11, GPI, 0, GPI_FLOATING_IN);    // OPA_CHN_PIN 初始化
        gpio_init(B15, GPI, 0, GPI_FLOATING_IN);    // OPA_CHP_PIN 初始化
        gpio_init(A3, GPI, 0, GPI_FLOATING_IN);     // OPA_CHOUT_PIN 初始化

        OPA_InitStructure.OPA_NUM = OPA1;
        OPA_InitStructure.PSEL=     CHP0;
        OPA_InitStructure.NSEL=     CHN0;
        OPA_InitStructure.Mode=     OUT_IO_OUT0;
        OPA_Init(&OPA_InitStructure);               // OPA1初始化

        OPA_Cmd(OPA1, ENABLE);                      // OPA1使能
    }
    else if(motor_index == MOTOR_2)
    {
        OPA_InitTypeDef  OPA_InitStructure={0};

        gpio_init(C2, GPI, 0, GPI_FLOATING_IN);     // OPA_CHN_PIN 初始化
        gpio_init(C5, GPI, 0, GPI_FLOATING_IN);     // OPA_CHP_PIN 初始化
        gpio_init(E7, GPI, 0, GPI_FLOATING_IN);     // OPA_CHOUT_PIN 初始化

        OPA_InitStructure.OPA_NUM = OPA3;
        OPA_InitStructure.PSEL=     CHP1;
        OPA_InitStructure.NSEL=     CHN1;
        OPA_InitStructure.Mode=     OUT_IO_OUT1;
        OPA_Init(&OPA_InitStructure);               // OPA3初始化

        OPA_Cmd(OPA3,ENABLE);                       // OPA3使能
    }
}





