#include "zf_common_headfile.h"

int main (void)
{
    // If using SCEP, go to zf_common_clock.h and change BOARD_XTAL_FREQ to 8MHz
    clock_init(SYSTEM_CLOCK_120M);
    debug_init();

    // User initializations
    ips114_init();
    ips114_show_string(0, 0, "Hello SCEP!");

    EasyKey_t keyLeft, keyRight, keyCenter;
    EasyKeyInit(&keyLeft, C6, 20);
    EasyKeyInit(&keyRight, C7, 20);
    EasyKeyInit(&keyCenter, G8, 20);

    mpu6050_init();
    ips114_clear();

    float w = 83, wTarget = 83;
    float y = 0, yTarget = 0;
    uint8_t index = 0;
    float wL, yL;

    while(1)
    {
        EasyKeyHandler();
        system_delay_ms(10);
        mpu6050_get_acc();

        char *str[8] = {"+ 1.Start",
        "+ 2.Config camera threshold",
        "+ 3.Show image",
        "- 4.MultiClick switch",
        "- 5.Dark mode",
        "+ 6.Servo PID param",
        "+ 7.Speed PID param",
        "+ 8.About"};

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
        IPS114_ClearRBox(0, y, w, 16);
        if (w < wTarget)
        {
            w += fabsf(wTarget - wL)/8;
            if (w > wTarget)
                w = wTarget;
        }
        if (w > wTarget)
        {
            w -= fabsf(wTarget - wL)/8;
            if (w < wTarget)
                w = wTarget;
        }
        if (y < yTarget)
        {
            y += fabsf(yTarget - yL)/8;
            if (y > yTarget)
                y = yTarget;
        }
        if (y > yTarget)
        {
            y -= fabsf(yTarget - yL)/8;
            if (y < yTarget)
                y = yTarget;
        }

        IPS114_DrawRBox(0, (int16_t)y, (int16_t)w, 16);
//        IPS114_DrawRBox(0, 16, 167, 16);

        ips114_show_string(2, 4, str[0]);
        ips114_show_string(2, 20, str[1]);
        ips114_show_string(2, 36, str[2]);
        ips114_show_string(2, 52, str[3]);
        ips114_show_string(2, 68, str[4]);
        ips114_show_string(2, 84, str[5]);
        ips114_show_string(2, 100, str[6]);
        ips114_show_string(2, 116, str[7]);
        ips114_show_string(226, 123, "12");
        ips114_show_string(229, 114, "/");
        ips114_show_uint(229, 106, index + 1, 1);   //232


        uart_write_string(UART_1, "hello");
    }
}