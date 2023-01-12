#include "zf_common_headfile.h"

int main(void)
{
    // If using SCEP, go to zf_common_clock.h and change BOARD_XTAL_FREQ to 8MHz
    clock_init(SYSTEM_CLOCK_120M);
    debug_init();

    // User initializations
    EasyUIInit(1);

    EasyKey_t keyLeft, keyRight, keyCenter;
    EasyKeyInit(&keyLeft, C6, 20);
    EasyKeyInit(&keyRight, C7, 20);
    EasyKeyInit(&keyCenter, G8, 20);

    mpu6050_init();

    system_delay_ms(1000);
    EasyUITransitionAnim();

    float w = 83, wTarget = 83;
    float y = 0, yTarget = 0;
    uint8_t index = 0, a = 0;
    float wL, yL;

    while (1)
    {
        EasyKeyHandler();
        system_delay_ms(10);
        mpu6050_get_acc();
        IPS114_ClearBuffer();

        char *str[8] = {"- Start",
                        "+ Servo PID param",
                        "+ Speed PID param",
                        "+ Config camera threshold",
                        "+ Show image",
                        "- MultiClick switch",
                        "- Dark mode",
                        "+ About"};

        if (keyRight.state == press)
        {
            wL = wTarget;
            yL = yTarget;
            if (index < 7)
                index++;
            else
                index = 0;
        }
        if (keyLeft.state == press)
        {
            wL = wTarget;
            yL = yTarget;
            if (index > 0)
                index--;
            else
                index = 7;
        }
        wTarget = strlen(str[index]) * 6 + 5;
        yTarget = index * 16;
//        ips114_show_int(0, 16, mpu6050_acc_x, 5);
//        ips114_show_int(0, 32, mpu6050_acc_y, 5);
//        ips114_show_int(0, 48, mpu6050_acc_z, 5);

//        ips114_draw_line(1, 0, 82 ,0, RGB565_WHITE);
//        ips114_draw_line(0, 1, 0 ,15, RGB565_WHITE);
//        ips114_draw_line(1, 15, 82 ,15, RGB565_WHITE);
//        ips114_draw_line(82, 1, 82 ,15, RGB565_WHITE);
//        IPS114_ClearRBox(0, y, w, 16);
        if (w < wTarget)
        {
            w += fabsf(wTarget - wL) / 5;
            if (w > wTarget)
                w = wTarget;
        }
        if (w > wTarget)
        {
            w -= fabsf(wTarget - wL) / 5;
            if (w < wTarget)
                w = wTarget;
        }
        if (y < yTarget)
        {
            y += fabsf(yTarget - yL) / 5;
            if (y > yTarget)
                y = yTarget;
        }
        if (y > yTarget)
        {
            y -= fabsf(yTarget - yL) / 5;
            if (y < yTarget)
                y = yTarget;
        }


        EasyUIDisplayStr(2, 4, str[0]);
        EasyUIDisplayStr(2, 20, str[1]);
        EasyUIDisplayStr(2, 36, str[2]);
        EasyUIDisplayStr(2, 52, str[3]);
        EasyUIDisplayStr(2, 68, str[4]);
        EasyUIDisplayStr(2, 84, str[5]);
        EasyUIDisplayStr(2, 100, str[6]);
        EasyUIDisplayStr(2, 116, str[7]);
        EasyUIDisplayStr(2, 132, "+ I don't know what to write");
        EasyUIDisplayStr(226, 125, "12");
        EasyUIDisplayStr(229, 116, "/");
        IPS114_ShowUint(229, 108, index + 1, 1);   //232

        IPS114_SetDrawColor(XOR);
        IPS114_DrawRBox(0, (int16_t) y, (int16_t) w, 16, IPS114_penColor);
        IPS114_SetDrawColor(NORMAL);

        if (keyCenter.state == press)
        {
            EasyUIDrawRBoxWithBlur(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3);
//            EasyUITransitionAnim();
            while (1);
        }

        IPS114_SendBuffer();

        uart_write_string(UART_1, "hello");
    }
}