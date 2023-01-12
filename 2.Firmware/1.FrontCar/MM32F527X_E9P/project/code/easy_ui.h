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
#include "user_ips114.h"
#include "profile_photo_erbws.h"
#include <string.h>

#define SCREEN_WIDTH        240
#define SCREEN_HEIGHT       135
#define FONT_WIDTH          6
#define FONT_HEIGHT         8
#define ITEM_HEIGHT         16
#define ANIMATION_SPEED     80      // Represent the time it takes to play the animation, smaller the quicker. Unit: ms

#define EasyUIScreenInit()                                      (ips114_init())
#define EasyUIDisplayStr(x, y, str)                             (IPS114_ShowStr(x, y, str))
#define EasyUIDrawDot(x, y, color)                              (IPS114_DrawPoint(x, y, color))
#define EasyUIDrawBox(x, y, width, height, color)               (IPS114_DrawBox(x, y, width, height, color))
#define EasyUIDrawRFrame(x, y, width, height, color)            (IPS114_DrawRFrame(x, y, width, height, color))
#define EasyUIClearBuffer()                                     (IPS114_ClearBuffer())
#define EasyUISendBuffer()                                      (IPS114_SendBuffer())
#define EasyUISetDrawColor(mode)                                (IPS114_SetDrawColor(mode))
#define EasyUIDisplayBMP(x, y, width, height, pic)              (IPS114_ShowBMP(x, y, width, height, pic))

typedef enum
{
    CALL_FUNCTION,
    JUMP_PAGE
} EasyUIFunc_e;

typedef struct EasyUI_item
{
    struct EasyUI_item *next;

    EasyUIFunc_e funcType;
    uint8_t id;
    char *title;
    uint8_t pageId;
    void (* callback)();
} EasyUIItem_t;

typedef struct EasyUI_page
{
    struct EasyUI_page *next;

    EasyUIItem_t *itemHead, *itemTail;
    uint8_t id;
} EasyUIPage_t;

void EasyUIInit(uint8_t mode);
void EasyUITransitionAnim();
void EasyUIDrawRBoxWithBlur(int16_t x, int16_t y, uint16_t width, uint16_t height);

#ifdef __cplusplus
}
#endif

#endif
