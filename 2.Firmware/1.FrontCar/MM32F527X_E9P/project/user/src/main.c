#include "zf_common_headfile.h"

int main(void)
{
    // If using SCEP, go to zf_common_clock.h and change BOARD_XTAL_FREQ to 8MHz
    clock_init(SYSTEM_CLOCK_120M);
    debug_init();

    // User initializations
    EasyUIInit(1);
    MenuInit();

    mpu6050_init();

    EasyUITransitionAnim();
    pit_ms_init(TIM6_PIT, 10);

    while (1)
    {
        mpu6050_get_acc();
        IPS114_ClearBuffer();
//        IPS114_ShowStr(2, 4, "+ Checkbox1");
//        IPS114_ShowStr(2, 20, "+ Checkbox2");
//        IPS114_DrawCheckbox(71, 1, 14, 3, true);
//        IPS114_DrawCheckbox(71, 17, 14, 3, false);
        IPS114_SendBuffer();

    }
}