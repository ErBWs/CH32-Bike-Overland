#include "encoder.h"
void encoderInit(void)
{
	// �˴���д�û����� ���������ʼ�������
    encoder_dir_init(ENCODER_FLY_WHEEL_TIM, ENCODER_FLY_WHEEL_DIR_PIN, ENCODER_FLY_WHEEL_SPD_PIN);
    encoder_dir_init(ENCODER_BACK_WHEEL_TIM, ENCODER_BACK_WHEEL_DIR_PIN, ENCODER_BACK_WHEEL_SPD_PIN);
}

