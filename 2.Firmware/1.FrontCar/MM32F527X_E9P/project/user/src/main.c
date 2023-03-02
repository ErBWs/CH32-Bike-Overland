#include "zf_common_headfile.h"

int main(void)
{
    // If using SCEP, go to zf_common_clock.h and change BOARD_XTAL_FREQ to 8MHz
    clock_init(SYSTEM_CLOCK_120M);
    debug_init();

    // User initializations
    MenuInit();
    EasyUIInit(1);

    mt9v03x_init();
    adc_init(ADC1_CH12_C2, ADC_12BIT);

    EasyUITransitionAnim();
    pit_ms_init(TIM6_PIT, 10);
    interrupt_set_priority(TIM6_IRQn, 7);

    while (1)
    {

    }
}