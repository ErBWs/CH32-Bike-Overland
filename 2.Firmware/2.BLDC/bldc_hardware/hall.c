#include "hall.h"
#include "bldc_config.h"

#include "zf_common_headfile.h"

hall_struct motor1_hall;
hall_struct motor2_hall;


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取当前霍尔值
//  @param      *hall   霍尔结构体指针
//  @return     uint8   霍尔值
//  @since      
//-------------------------------------------------------------------------------------------------------------------
uint8 hall_value_read(hall_struct *hall)
{
    uint8 hall_a;
    uint8 hall_b;
    uint8 hall_c;

    hall_a = gpio_get_level(hall->hall_a_pin);
    hall_b = gpio_get_level(hall->hall_b_pin);
    hall_c = gpio_get_level(hall->hall_c_pin);
    return (hall_a*4 + hall_b*2 + hall_c);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取换相时长
//  @param      *hall   霍尔结构体指针
//  @return     uint16  换向时长
//  @since      
//-------------------------------------------------------------------------------------------------------------------
uint16 hall_interval_time(hall_struct *hall)
{
    return TIM_GetCapture1(hall->tim_ch);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      设置延时换相时长
//  @param      *hall       霍尔结构体指针
//  @param      delay_time  设置的时间
//  @return     void
//  @since      
//-------------------------------------------------------------------------------------------------------------------
void hall_delay_set(hall_struct *hall, uint32 delay_time)
{
    //这里应该判断，如果设置的时间小于计数值则直接触发中断
    if((hall->tim_ch->CNT+5) < (delay_time))
    {
        TIM_SetCompare2(hall->tim_ch, delay_time);
    }
    else
    {
        // 延时的时间与定时器的计数值过于接近则直接触发中断
        hall->tim_ch->INTFR = TIM_FLAG_CC2;
    }
    
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      使能或失能延迟换向
//  @param      *hall       霍尔结构体指针
//  @param      state       使能或失能
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void hall_delay_state_set(hall_struct *hall, uint8 state)
{
    TIM_ClearFlag(hall->tim_ch, TIM_FLAG_CC2);
    TIM_ITConfig(hall->tim_ch, TIM_IT_CC2, (FunctionalState)state);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      霍尔采集初始化
//  @param      motor_index 电机索引
//  @param      *hall       霍尔结构体指针
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void hall_init(motor_index_enum motor_index, hall_struct *hall)
{
    if(motor_index == MOTOR_1)
    {
        hall->hall_a_pin = C6;
        hall->hall_b_pin = C7;
        hall->hall_c_pin = C8;
        hall->tim_ch = TIM3;
        hall->irqn = TIM3_IRQn;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);            // 使能AFIO复用功能模块时钟
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);               // 完全重映射

        interrupt_enable(hall->irqn);                                    // 使能中断
        interrupt_set_priority(hall->irqn, 0<<5|0);                      // 抢占优先级0，次优先级0
    }
    else if(motor_index == MOTOR_2)
    {
        hall->hall_a_pin = B6;
        hall->hall_b_pin = B7;
        hall->hall_c_pin = B8;
        hall->tim_ch = TIM4;
        hall->irqn = TIM4_IRQn;

        interrupt_enable(hall->irqn);                                    // 使能中断
        interrupt_set_priority(hall->irqn, 0<<5|0);                      // 抢占优先级0，次优先级0
    }

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};           // 时基初始化结构体
    TIM_ICInitTypeDef       TIM_ICInitStruct = {0};                 // 输入捕获初始化结构体
    TIM_OCInitTypeDef       TIM_OCInitStructure = {0};

    if(hall->tim_ch == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    }
    else if(hall->tim_ch == TIM2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    }
    else if(hall->tim_ch == TIM3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    }
    else if(hall->tim_ch == TIM4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    }
    else if(hall->tim_ch == TIM5)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    }
    else if(hall->tim_ch == TIM6)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    }
    else if(hall->tim_ch == TIM7)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    }
    else if(hall->tim_ch == TIM8)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    }
    else if(hall->tim_ch == TIM9)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    }
    else if(hall->tim_ch == TIM10)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    }
    else
    {
        zf_assert(0);
    }

    gpio_init(hall->hall_a_pin, GPI, 0, GPI_PULL_UP);
    gpio_init(hall->hall_b_pin, GPI, 0, GPI_PULL_UP);
    gpio_init(hall->hall_c_pin, GPI, 0, GPI_PULL_UP);


    //时基参数配置
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;                    // 时钟分割：TDTS = TCK_INT ，采样频率=144M
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_CenterAligned1;    // 中心对齐模式
    TIM_TimeBaseInitStruct.TIM_Period = 50*1000 - 1;                            // 设置超时时长为60ms
    TIM_TimeBaseInitStruct.TIM_Prescaler = SYSTEM_CLOCK/1000000;                // 分频后定时器的频率为1000KHZ
    //时基初始化
    TIM_TimeBaseInit(hall->tim_ch,&TIM_TimeBaseInitStruct);


    //使能Timx霍尔传感器接口，实际上就是完成将CH1、CH2和CH3异或输入
    TIM_SelectHallSensor(hall->tim_ch, ENABLE);

    // hall->tim_ch输入通道1初始化，输入捕获通道1配置
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;                   // 通道1
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_BothEdge;      // 上升沿和下降沿
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;              // 配置输入信号分频，不分频
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_TRC;         // 将IC1映射到 TRC上
    TIM_ICInitStruct.TIM_ICFilter = 15;                             // 滤波长度：15
    TIM_ICInit(hall->tim_ch,&TIM_ICInitStruct);                     // 输入捕获初始化

    TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;                   // 通道2
    TIM_ICInit(hall->tim_ch,&TIM_ICInitStruct);                     // 输入捕获初始化

    TIM_ICInitStruct.TIM_Channel = TIM_Channel_3;                   // 通道3
    TIM_ICInit(hall->tim_ch,&TIM_ICInitStruct);                     // 输入捕获初始化


    // hall->tim_ch输出通道2初始化，延时换向
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1000;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(hall->tim_ch, &TIM_OCInitStructure);
    TIM_CCxCmd(hall->tim_ch, TIM_Channel_2, TIM_CCx_Disable);

    // hall->tim_ch输出通道3初始化，用于检测超时
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;               // TIM输出通道初始化
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseInitStruct.TIM_Period - 1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(hall->tim_ch, &TIM_OCInitStructure);
    TIM_CCxCmd(hall->tim_ch, TIM_Channel_3, TIM_CCx_Disable);
//    TIM_OC3PreloadConfig(hall->tim_ch, TIM_OCPreload_Enable);                      // 定时器预装载配置
//    TIM_OC3FastConfig(hall->tim_ch, TIM_OC3FE);                                    // 比较捕获通道快速使能


    TIM_SelectInputTrigger(hall->tim_ch, TIM_TS_TI1F_ED);                   // 输入触发源选择，选择TI1F_ED
    TIM_SelectSlaveMode(hall->tim_ch, TIM_SlaveMode_Reset);                 // 从模式选择，复位模式
//    TIM_SelectOutputTrigger(hall->tim_ch, TIM_TRGOSource_OC2Ref);         // 选择输出触发模式(TRGO端)
    TIM_SelectMasterSlaveMode(hall->tim_ch, TIM_MasterSlaveMode_Enable);    // 主从模式选择


    TIM_ClearFlag(hall->tim_ch, TIM_FLAG_CC1);
    TIM_ClearFlag(hall->tim_ch, TIM_FLAG_CC3);

    TIM_ITConfig(hall->tim_ch, TIM_IT_CC1, ENABLE);
    TIM_ITConfig(hall->tim_ch, TIM_IT_CC3, ENABLE);

    TIM_Cmd(hall->tim_ch, ENABLE);

}
