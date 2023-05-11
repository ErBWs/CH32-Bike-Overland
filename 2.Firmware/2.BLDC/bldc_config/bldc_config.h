#ifndef _bldc_config_h_
#define _bldc_config_h_


typedef enum
{
    MOTOR_1 = 0,
    MOTOR_2 = 1
}motor_index_enum;


// 系统时钟，不可更改
#define SYSTEM_CLOCK                ((uint32)144000000)

// 互补PWM频率
#define PWM_FREQUENCY               ((uint16)40000)

// PWM周期值
#define PWM_PERIOD                  (uint16)(SYSTEM_CLOCK / PWM_FREQUENCY / 2) 

// PWM死区设置
#define PWM_DEADTIME                (0x1)

// 刹车时占空比 不可更改
#define BLDC_BRAKE_DUTY             (PWM_PERIOD / 100 * BLDC_BRAKE_PERCENT)

//0：不开启刹车功能     1：开启
#define BLDC_BRAKE_ENABLE           (1)

// 单节电池低压保护阈值（单位伏），例如设置3.4时使用3S供电则当电压小于3*3.4=10.2V的时候开始报警, 设置范围3.0-3.6
#define BLDC_LOW_VOLTAGE            (3.4f)

// 电压过低时自动刹车 0：不自动刹车 1：自动刹车  
#define BLDC_LOW_VOLTAGE_BRAKE      (0)

// 定义最大换相时间 一般不用修改
#define BLDC_COMMUTATION_TIME_MAX   (10000)

//0：不开启速度闭环     1：开启  一般不需要开启闭环
#define BLDC_CLOSE_LOOP_ENABLE      (0)       

// 开启缓慢加减速功能
#define BLDC_SPEED_CURVE_ENABLE     (0)

// 设置最大转速
#define BLDC_MAX_SPEED              (6000)


// 刹车力度设置，范围0-100，数值越大刹车力度越大
#define BLDC_BRAKE_PERCENT          (50)

#if BLDC_CLOSE_LOOP_ENABLE==1

    // 闭环缓慢加减速系数
    // BLDC_STEP_SPEED作用是使得电机缓慢加速，避免出现电流过大的，值越小电机加速越慢
    // 如果不需要可以通过将BLDC_SPEED_CURVE_ENABLE设置为0，来关闭这个功能
    #define BLDC_STEP_SPEED         (100)
#else
    // 开环缓慢加减速系数
    #define BLDC_STEP_SPEED         (1000)
#endif

    
#endif










