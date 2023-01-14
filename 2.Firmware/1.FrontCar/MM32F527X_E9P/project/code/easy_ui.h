/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef _EASY_UI_H
#define _EASY_UI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "easy_key.h"
#include "zf_device_ips114.h"
#include "zf_driver_uart.h"
#include "user_ips114.h"
#include "profile_photo_erbws.h"
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#include "menu.h"

// Modify this to fit your EasyKeyInit
#define KEY_UP          C7
#define KEY_DOWN        C6
#define KEY_FORWARD     C7
#define KEY_BACKWARD    C6
#define KEY_CONFIRM     G8

extern EasyKey_t keyUp, keyDown;           // Used to control value up and down
extern EasyKey_t keyForward, keyBackward;  // Used to control indicator movement
extern EasyKey_t keyConfirm;               // Used to change page or call function

#define SCREEN_WIDTH            240
#define SCREEN_HEIGHT           135
#define FONT_WIDTH              6
#define FONT_HEIGHT             8
#define ITEM_HEIGHT             16
#define ITEM_LINES              ((uint8_t)(SCREEN_HEIGHT / ITEM_HEIGHT))

// Represent the time it takes to play the animation, smaller the quicker. Unit: ms
#define INDICATOR_MOVE_TIME     60
#define ITEM_MOVE_TIME          60

#define EasyUIScreenInit()                                      (ips114_init())
#define EasyUIDisplayStr(x, y, str)                             (IPS114_ShowStr(x, y, str))
#define EasyUIDisplayUint(x, y, dat, num)                       (IPS114_ShowUint(x, y, dat, num))
#define EasyUIDrawDot(x, y, color)                              (IPS114_DrawPoint(x, y, color))
#define EasyUIDrawBox(x, y, width, height, color)               (IPS114_DrawBox(x, y, width, height, color))
#define EasyUIDrawRFrame(x, y, width, height, color)            (IPS114_DrawRFrame(x, y, width, height, color))
#define EasyUIDrawRBox(x, y, width, height, color)              (IPS114_DrawRBox(x, y, width, height, color))
#define EasyUIClearBuffer()                                     (IPS114_ClearBuffer())
#define EasyUISendBuffer()                                      (IPS114_SendBuffer())
#define EasyUISetDrawColor(mode)                                (IPS114_SetDrawColor(mode))
#define EasyUIDisplayBMP(x, y, width, height, pic)              (IPS114_ShowBMP(x, y, width, height, pic))

typedef enum
{
    CALL_FUNCTION,
    JUMP_PAGE,
    PAGE_DESCRIPTION
} EasyUIFunc_e;

typedef struct EasyUI_item
{
    struct EasyUI_item *next;

    EasyUIFunc_e funcType;
    uint8_t id;
    int16_t lineId;
    uint8_t pageId;
    float posForCal;
    float step;
    int16_t position;
    char *title;
    void (* Event)(uint8_t cnt, ...);    // Arg "cnt" is used to define the amount of variable args
} EasyUIItem_t;

typedef struct EasyUI_page
{
    struct EasyUI_page *next;

    EasyUIItem_t *itemHead, *itemTail;
    uint8_t id;
} EasyUIPage_t;

void EasyUIAddItem(EasyUIPage_t *page, EasyUIItem_t *item, char *_title, EasyUIFunc_e func, ...);
void EasyUIAddPage(EasyUIPage_t *page);
void EasyUITransitionAnim();
void EasyUIDrawRBoxWithBlur(int16_t x, int16_t y, uint16_t width, uint16_t height);
void EasyUIInit(uint8_t mode);
void EasyUI(uint8_t timer);

#ifdef __cplusplus
}
#endif

#endif
