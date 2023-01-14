/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "easy_ui.h"


EasyUIPage_t *pageHead = NULL, *pageTail = NULL;

/*!
 * @brief   Add page to UI
 *
 * @param   page    EasyUI page struct
 * @return  void
 *
 * @note    Do not modify, the first page should always be the fist one to be added.
 */
void EasyUIAddPage(EasyUIPage_t *page)
{
    page->itemHead = NULL;
    page->itemTail = NULL;
    page->next = NULL;

    if (pageHead == NULL)
    {
        page->id = 0;
        pageHead = page;
        pageTail = page;
    } else
    {
        page->id = pageTail->id + 1;
        pageTail->next = page;
        pageTail = pageTail->next;
    }
}


/*!
 * @brief   Add item to page
 *
 * @param   page        EasyUI page struct
 * @param   item        EasyUI item struct
 * @param   _title      String of item title
 * @param   func        CALL_FUNCTION / JUMP_PAGE
 * @param   ...         If CALL_FUNCTION, just fill this with a function
 *                      If JUMP_PAGE, just fill this with target page's id
 * @return  void
 */
void EasyUIAddItem(EasyUIPage_t *page, EasyUIItem_t *item, char *_title, EasyUIFunc_e func, ...)
{
    va_list variableArg;
    va_start(variableArg, func);
    item->funcType = func;
    switch (item->funcType)
    {
        case CALL_FUNCTION:
            item->Event = va_arg(variableArg, void (* )(uint8_t, ...));
            break;
        case JUMP_PAGE:
            item->pageId = va_arg(variableArg, int);
            break;
        default:
            break;
    }
    va_end(variableArg);

    item->next = NULL;
    item->title = _title;

    if (page->itemHead == NULL)
    {
        item->id = 0;
        page->itemHead = item;
        page->itemTail = item;
    } else
    {
        item->id = page->itemTail->id + 1;
        page->itemTail->next = item;
        page->itemTail = page->itemTail->next;
    }

    item->lineId = item->id;
    item->posForCal = 0;
    item->step = 0;
    item->position = 0;
}


/*!
 * @brief   Blur transition animation
 *
 * @param   void
 * @return  void
 *
 * @note    Use before clearing the buffer
 *          Also use after all the initialization is done for better experience
 */
void EasyUITransitionAnim()
{
    for (int j = 1; j < SCREEN_HEIGHT + 1; j += 2)
    {
        for (int i = 0; i < SCREEN_WIDTH + 1; i += 2)
        {
            EasyUIDrawDot(i, j, IPS114_backgroundColor);
        }
    }
    EasyUISendBuffer();
    for (int j = 1; j < SCREEN_HEIGHT + 1; j += 2)
    {
        for (int i = 1; i < SCREEN_WIDTH + 1; i += 2)
        {
            EasyUIDrawDot(i, j, IPS114_backgroundColor);
        }
    }
    EasyUISendBuffer();
    for (int j = 0; j < SCREEN_HEIGHT + 1; j += 2)
    {
        for (int i = 1; i < SCREEN_WIDTH + 1; i += 2)
        {
            EasyUIDrawDot(i, j, IPS114_backgroundColor);
        }
    }
    EasyUISendBuffer();
    for (int j = 1; j < SCREEN_HEIGHT + 1; j += 2)
    {
        for (int i = 1; i < SCREEN_WIDTH + 1; i += 2)
        {
            EasyUIDrawDot(i - 1, j - 1, IPS114_backgroundColor);
        }
    }
    EasyUISendBuffer();
}


/*!
 * @brief   Blur the background for rounded box
 *
 * @param   x
 * @param   y
 * @param   width
 * @param   height
 * @return  void
 *
 * @note    Use before clearing the buffer
 */
void EasyUIDrawRBoxWithBlur(int16_t x, int16_t y, uint16_t width, uint16_t height)
{
    // Background blur
    for (int j = 1; j < SCREEN_HEIGHT + 1; j += 2)
    {
        for (int i = 1; i < SCREEN_WIDTH + 1; i += 2)
        {
            EasyUIDrawDot(i, j, IPS114_backgroundColor);
        }
    }
    EasyUISendBuffer();
    for (int j = 1; j < SCREEN_HEIGHT + 1; j += 2)
    {
        for (int i = 1; i < SCREEN_WIDTH + 1; i += 2)
        {
            EasyUIDrawDot(i - 1, j - 1, IPS114_backgroundColor);
        }
    }
    EasyUISendBuffer();

    // Draw rounded frame filled with background color
    EasyUISetDrawColor(NORMAL);
    EasyUIDrawRFrame(x, y, width, height, IPS114_penColor);
    EasyUIDrawBox(x + 1, y + 1, width - 2, height - 2, IPS114_backgroundColor);
    EasyUISendBuffer();
}


void EasyUIGetItemPos(EasyUIPage_t *page, EasyUIItem_t *item, uint8_t index, uint8_t timer)
{
    static uint8_t itemHeightOffset = (ITEM_HEIGHT - FONT_HEIGHT) / 2;
    static uint16_t time = 0;
    static int16_t move = 0, target;
    static uint8_t lastIndex = 0;
    uint8_t speed = ITEM_MOVE_TIME / timer;

    // Item need to move or not
        for (EasyUIItem_t *itemTmp = page->itemHead; itemTmp != NULL; itemTmp = itemTmp->next)
        {
            if (index == itemTmp->id && itemTmp->lineId < 0)
            {
                move = itemTmp->lineId;
                break;
            } else if (index == itemTmp->id && itemTmp->lineId > ITEM_LINES - 1)
            {
                move = itemTmp->lineId - ITEM_LINES + 1;
                break;
            }
        }

    // Change the item lineId and get target position
    item->lineId -= move;
    if (item->next == NULL)
    {
        move = 0;
    }
    target = itemHeightOffset + item->lineId * ITEM_HEIGHT;

    // Calculate current position
    if (time == 0 || index != lastIndex)
    {
        item->step = ((float) target - (float) item->position) / (float) speed;
    }
    if (time < ITEM_MOVE_TIME)
    {
        item->posForCal += item->step;
        if (time >= ITEM_MOVE_TIME)
        {
            item->posForCal = target;
        }
    }


    item->position = (int16_t) item->posForCal;
    lastIndex = index;

    // Time counter
    if (item->next == NULL)
    {
        if (target == item->position)
            time = 0;
        else
            time += timer;
    }
}


void EasyUIDrawIndicator(EasyUIPage_t *page, uint8_t index, uint8_t timer)
{
    static float stepLength = 0, stepHeight, length = 0, height = 0;
    static uint16_t time = 0;
    static uint8_t moveFlag = 0;
    static int16_t move = 0;
    static uint16_t lengthTarget = 0, heightTarget = 0;
    uint8_t speed = INDICATOR_MOVE_TIME / timer;

    // Get Initial length
    if (length == 0)
        length = (float) (strlen(page->itemHead->title) + 2) * FONT_WIDTH + 5;

    // Get target length and height
    for (EasyUIItem_t *itemTmp = page->itemHead; itemTmp != NULL; itemTmp = itemTmp->next)
    {
        if (index == itemTmp->id)
        {
            lengthTarget = (strlen(itemTmp->title) + 2) * FONT_WIDTH + 5;
            heightTarget = itemTmp->lineId * ITEM_HEIGHT;
            break;
        }
    }

    // Calculate current position
    if (time == 0)
    {
        stepLength = ((float) lengthTarget - (float) length) / (float) speed;
        stepHeight = ((float) heightTarget - (float) length) / (float) speed;
    } else if (time <= ITEM_MOVE_TIME)
    {
        length += stepLength;
        height += stepHeight;
        if (time == ITEM_MOVE_TIME)
        {
            length = lengthTarget;
            height = heightTarget;
        }
    }

    // Time counter
    if ((int) stepHeight == 0 && (int) stepLength == 0)
        time = 0;
    else
        time += timer;

    EasyUISetDrawColor(XOR);
    EasyUIDrawRBox(0, (int16_t) height, (int16_t) length, ITEM_HEIGHT, IPS114_penColor);
    EasyUISetDrawColor(NORMAL);
}


EasyKey_t keyUp, keyDown, keyForward, keyBackward, keyConfirm;

/*!
 * @brief   Welcome Page with two size of photo
 *
 * @param   mode    choose the size of photo (0 for smaller one and 1 for bigger one)
 * @return  void
 */
void EasyUIInit(uint8_t mode)
{
    EasyUIScreenInit();
    EasyUIClearBuffer();

    EasyKeyInit(&keyUp, KEY_UP);
    EasyKeyInit(&keyDown, KEY_DOWN);
    EasyKeyInit(&keyForward, KEY_FORWARD);
    EasyKeyInit(&keyBackward, KEY_BACKWARD);
    EasyKeyInit(&keyConfirm, KEY_CONFIRM);

    // Display the welcome photo and info
    if (mode)
        EasyUIDisplayBMP((SCREEN_WIDTH - 58) / 2, (SCREEN_HEIGHT - 56) / 2, 58, 56, ErBW_s_5856);
    else
        EasyUIDisplayBMP((SCREEN_WIDTH - 29) / 2, (SCREEN_HEIGHT - 28) / 2, 29, 28, ErBW_s_2928);
    if (SCREEN_WIDTH > (25 * FONT_WIDTH + 1))
        EasyUIDisplayStr(SCREEN_WIDTH - 1 - 25 * FONT_WIDTH, SCREEN_HEIGHT - 1 - FONT_HEIGHT,
                         "Powered by EasyUI(ErBW_s)");
    else if (SCREEN_WIDTH > (14 * FONT_WIDTH + 1))
        EasyUIDisplayStr(SCREEN_WIDTH - 1 - 25 * FONT_WIDTH, SCREEN_HEIGHT - 1 - FONT_HEIGHT, "EasyUI(ErBW_s)");
    EasyUISendBuffer();
}


void EasyUI(uint8_t timer)
{
    static uint8_t pageIndex[20] = {0};     // Page id (stack)
    static uint8_t itemIndex[20] = {0};     // Item id (stack)
    static uint8_t layer = 0;               // pageIndex[layer] / itemIndex[layer]
    static uint8_t index = 0, itemSum = 0;

    EasyUIClearBuffer();
    EasyUISetDrawColor(NORMAL);

    // Get current page by id
    EasyUIPage_t *page = pageHead;
    while (page->id != pageIndex[layer])
    {
        page = page->next;
    }
    // Display every item in current page
    for (EasyUIItem_t *item = page->itemHead; item != NULL; item = item->next)
    {
        EasyUIGetItemPos(page, item, index, timer);
        switch (item->funcType)
        {
            case CALL_FUNCTION:
                EasyUIDisplayStr(2, item->position, "- ");
                break;
            case JUMP_PAGE:
                EasyUIDisplayStr(2, item->position, "+ ");
                break;
            default:
                break;
        }
        EasyUIDisplayStr(2 + 2 * FONT_WIDTH, item->position, item->title);
    }
    // Draw indicator
//    EasyUIDrawIndicator(page, index, timer);
    // Display navigation
    itemSum = page->itemTail->id + 1;
    if (itemSum > 9)
    {
        EasyUIDisplayUint(SCREEN_WIDTH - 1 - 2 * FONT_WIDTH, SCREEN_HEIGHT - 1 - FONT_HEIGHT, itemSum, 2);
        EasyUIDisplayStr(SCREEN_WIDTH - 1 - 3 * FONT_WIDTH / 2, SCREEN_HEIGHT - 1 - 2 * FONT_HEIGHT, "/");
        if (index + 1 > 9)
            EasyUIDisplayUint(SCREEN_WIDTH - 1 - 2 * FONT_WIDTH, SCREEN_HEIGHT - 1 - 3 * FONT_HEIGHT, index + 1, 2);
        else
            EasyUIDisplayUint(SCREEN_WIDTH - 1 - 3 * FONT_WIDTH / 2, SCREEN_HEIGHT - 1 - 3 * FONT_HEIGHT, index + 1, 1);
    } else
    {
        EasyUIDisplayUint(SCREEN_WIDTH - 1 - 3 * FONT_WIDTH / 2, SCREEN_HEIGHT - 1 - FONT_HEIGHT, itemSum, 1);
        EasyUIDisplayStr(SCREEN_WIDTH - 1 - 3 * FONT_WIDTH / 2, SCREEN_HEIGHT - 1 - 2 * FONT_HEIGHT, "/");
        EasyUIDisplayUint(SCREEN_WIDTH - 1 - 3 * FONT_WIDTH / 2, SCREEN_HEIGHT - 1 - 3 * FONT_HEIGHT, index + 1, 1);
    }

    // Key move reaction
    if (keyForward.isPressed)
    {
        if (index < itemSum - 1)
            index++;
        else
            index = 0;
    }
    if (keyBackward.isPressed)
    {
        if (index > 0)
            index--;
        else
            index = itemSum - 1;
    }
    if (keyConfirm.isPressed)
    {
        EasyUIDrawRBoxWithBlur(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3);
    }
    if (keyConfirm.isHold)
    {
        EasyUITransitionAnim();
    }

    EasyUISendBuffer();
}