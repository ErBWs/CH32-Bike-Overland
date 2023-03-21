#include "encoder.h"
void encoderInit(void)
{
	// 此处编写用户代码 例如外设初始化代码等
    encoder_dir_init(ENCODER_FLY_WHEEL_TIM, ENCODER_FLY_WHEEL_DIR_PIN, ENCODER_FLY_WHEEL_SPD_PIN);
    encoder_dir_init(ENCODER_BACK_WHEEL_TIM, ENCODER_BACK_WHEEL_DIR_PIN, ENCODER_BACK_WHEEL_SPD_PIN);
}

