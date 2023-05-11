#include "moto.h"
#include "inc_all.h"
// PID parameter array: *Param[5] = {kp, ki, kd, target_value, limitation}


void motoInit(void)
{
    pwm_init(SERVO_PIN, SERVO_FREQ, SERVO_MID);
    pwm_init(MOTOR_FLY_PIN, 1000, 0);
    gpio_init(MOTOR_FLY_DIR_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
    pwm_init(MOTOR_BACK_PIN, 1000, 0);
    gpio_init(MOTOR_BACK_DIR_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
}



void motoDutySet(pwm_channel_enum pin,int32_t duty)
{
    if(pin==MOTOR_BACK_PIN)
    {
        if(duty<0)
        {
            duty =-duty;
            gpio_set_level(MOTOR_BACK_DIR_PIN,GPIO_HIGH);
        }
        else if(duty>0)
		gpio_set_level(MOTOR_BACK_DIR_PIN,GPIO_LOW);
        pwm_set_duty(MOTOR_BACK_PIN,duty>PWM_DUTY_MAX?PWM_DUTY_MAX:duty);
    }
    else if(pin==MOTOR_FLY_PIN)
    {
        if(duty<0)
        {
            duty =-duty;
            gpio_set_level(MOTOR_FLY_DIR_PIN,GPIO_HIGH);
        }
        else if(duty>0)
        gpio_set_level(MOTOR_FLY_DIR_PIN,GPIO_LOW);
        pwm_set_duty(MOTOR_FLY_PIN,duty>PWM_DUTY_MAX?PWM_DUTY_MAX:duty);
    }
}
static uint16_t duty_target=0;
static int32_t servo_step_duty;
static int32_t duty_err;
uint8 servo_sport_update_flag = 0;//若该标志位置1，则外部不能有强行修改servo_current_duty的行为；
uint16 servo_current_duty = GetServoDuty(0);
void ServoSportSet(uint16_t duty_value,int32_t ticks)
{
    duty_target = duty_value;
    duty_err = duty_value- servo_current_duty;
    servo_step_duty = duty_err/ticks;
    servo_step_duty = servo_step_duty!=0?servo_step_duty:duty_err>0?1:-1;
    servo_sport_update_flag = 1;
}
void ServoSportHandler(uint16 *duty_input)
{
    static uint32 last_ticks=1LL << 31;
    uint16 input_pwm_duty=servo_current_duty;//(TIM2->CH1CVR*PWM_DUTY_MAX)/TIM2->ATRLR;
    if(now_tick>last_ticks&&servo_sport_update_flag==1)
    {
        last_ticks = now_tick;
        duty_err-=servo_step_duty;
        if((servo_step_duty<0&&duty_err>=0)||(servo_step_duty>0&&duty_err<=0))
        {
            servo_sport_update_flag = 0;
            duty_err = 0;
            input_pwm_duty = duty_target;
        }
        else{
            input_pwm_duty += servo_step_duty;
            input_pwm_duty = input_pwm_duty<0?0:input_pwm_duty>=PWM_DUTY_MAX?PWM_DUTY_MAX-1:input_pwm_duty;
        }
    }
    *duty_input = input_pwm_duty;
    servo_current_duty = input_pwm_duty;
}
