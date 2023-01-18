#include "zf_common_headfile.h"

int main(void)
{
    // If using SCEP, go to zf_common_clock.h and change BOARD_XTAL_FREQ to 8MHz
    clock_init(SYSTEM_CLOCK_120M);
    debug_init();

    // User initializations
    MenuInit();
    EasyUIInit(1);

    mpu6050_init();

    EasyUITransitionAnim();
    pit_ms_init(TIM6_PIT, 10);

    while (1)
    {
        mpu6050_get_acc();

    }
}