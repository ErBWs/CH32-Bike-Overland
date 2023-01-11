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

#define SCREEN_WIDTH        240
#define SCREEN_HEIGHT       135
#define FONT_WIDTH          6
#define FONT_HEIGHT         8
#define ITEM_HEIGHT         16
#define ANIMATION_SPEED     80      // Represent the time it takes to play the animation, smaller the quicker. Unit: ms

#define EasyUI_DisplayStr(x, y, str)                            (IPS114_ShowStr(x, y, str))
#define EasyUI_DrawDot(x, y, color)                             (IPS114_DrawPoint(x, y, color))
#define EasyUI_FillWithColor(x, y, width, height, color)        (IPS114_FillBoxWithColor(x, y, width, height, color))
#define EasyUI_DrawRBox(x, y, width, height, color)                    (IPS114_DrawRBox(x, y, width, height, color))

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

void EasyUITransitionAnim();
void EasyUIDrawRBoxWithBlur();

#ifdef __cplusplus
}
#endif

#endif
