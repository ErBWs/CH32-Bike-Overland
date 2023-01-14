/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "easy_ui.h"


EasyUIPage_t *pageHead = NULL, *pageTail = NULL;

/*!
 * @brief   Add item to page
 *
 * @param   page        EasyUI page struct
 * @param   item        EasyUI item struct
 * @param   _title      String of item title
 * @param   func        CALL_FUNCTION / JUMP_PAGE
 * @param   ...         If CALL_FUNCTION, just fill this with a function
 *                      If JUMP_PAGE, just fill this with target page's id
 *                      If PAGE_DESCRIPTION, ignore this
 * @return  void
 *
 * @note    Do not modify
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
 * @param   x       X of the rounded box
 * @param   y       Y of the rounded box
 * @param   width   Width of the rounded box
 * @param   height  Height of the rounded box
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


/*!
 * @brief   Get position of item with linear animation
 *
 * @param   page    Struct of page
 * @param   item    Struct of item
 * @param   index   Current index
 * @param   timer   Fill this with interrupt trigger time
 * @return  void
 *
 * @note    Internal call
 */
void EasyUIGetItemPos(EasyUIPage_t *page, EasyUIItem_t *item, uint8_t index, uint8_t timer)
{
    static uint8_t itemHeightOffset = (ITEM_HEIGHT - FONT_HEIGHT) / 2;
    static uint16_t time = 0;
    static int16_t move = 0, target = 0;
    static uint8_t lastIndex = 0, moveFlag = 0;
    uint8_t speed = ITEM_MOVE_TIME / timer;

    // Item need to move or not
    if (moveFlag == 0)
    {
        for (EasyUIItem_t *itemTmp = page->itemHead; itemTmp != NULL; itemTmp = itemTmp->next)
        {
            if (index == itemTmp->id && itemTmp->lineId < 0)
            {
                move = itemTmp->lineId;
                moveFlag = 1;
                break;
            } else if (index == itemTmp->id && itemTmp->lineId > ITEM_LINES - 1)
            {
                move = itemTmp->lineId - ITEM_LINES + 1;
                moveFlag = 1;
                break;
            }
        }
    }

    // Change the item lineId and get target position
    for (EasyUIItem_t *itemTmp = page->itemHead; itemTmp != NULL; itemTmp = itemTmp->next)
    {
        itemTmp->lineId -= move;
    }
    move = 0;
    moveFlag = 0;
    target = itemHeightOffset + item->lineId * ITEM_HEIGHT;

    // Calculate current position
    if (time == 0 || index != lastIndex)
    {
        item->step = ((float) target - (float) item->position) / (float) speed;
    }
    if (time >= ITEM_MOVE_TIME)
    {
        item->posForCal = target;
    } else
        item->posForCal += item->step;

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


/*!
 * @brief   Get position of indicator with linear animation
 *
 * @param   page    Struct of page
 * @param   index   Current index
 * @param   timer   Fill this with interrupt trigger time
 * @return  void
 *
 * @note    Internal call
 */
void EasyUIDrawIndicator(EasyUIPage_t *page, uint8_t index, uint8_t timer)
{
    static float stepLength = 0, stepY = 0, length = 0, y = 0;
    static uint16_t time = 0;
    static uint8_t lastIndex = 0;
    static uint16_t lengthTarget = 0, yTarget = 0;
    uint8_t speed = INDICATOR_MOVE_TIME / timer;

    // Get Initial length
    if ((int) length == 0)
    {
        if (page->itemHead->funcType == PAGE_DESCRIPTION)
            length = (float) (strlen(page->itemHead->title)) * FONT_WIDTH + 5;
        else
            length = (float) (strlen(page->itemHead->title) + 2) * FONT_WIDTH + 5;
    }

    // Get target length and y
    for (EasyUIItem_t *itemTmp = page->itemHead; itemTmp != NULL; itemTmp = itemTmp->next)
    {
        if (index == itemTmp->id)
        {
            if (itemTmp->funcType == PAGE_DESCRIPTION)
                lengthTarget = (strlen(itemTmp->title)) * FONT_WIDTH + 5;
            else
                lengthTarget = (strlen(itemTmp->title) + 2) * FONT_WIDTH + 5;
            yTarget = itemTmp->lineId * ITEM_HEIGHT;
            break;
        }
    }

    // Calculate current position
    if (time == 0 || index != lastIndex)
    {
        stepLength = ((float) lengthTarget - (float) length) / (float) speed;
        stepY = ((float) yTarget - (float) y) / (float) speed;
    }
    if (time >= ITEM_MOVE_TIME)
    {
        length = lengthTarget;
        y = yTarget;
    } else
    {
        length += stepLength;
        y += stepY;
    }

    // Draw rounded box
    EasyUISetDrawColor(XOR);
    EasyUIDrawRBox(0, (int16_t) y, (int16_t) length, ITEM_HEIGHT, IPS114_penColor);
    EasyUISetDrawColor(NORMAL);
    lastIndex = index;

    // Time counter
    if ((int) length == lengthTarget && (int) y == yTarget)
        time = 0;
    else
        time += timer;
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


/*!
 * @brief   Main function of EasyUI
 *
 * @param   timer   Fill this with interrupt trigger time
 * @return  void
 */
void EasyUI(uint8_t timer)
{
    static uint8_t pageIndex[10] = {0};     // Page id (stack)
    static uint8_t itemIndex[10] = {0};     // Item id (stack)
    static uint8_t layer = 0;               // pageIndex[layer] / itemIndex[layer]
    static uint8_t index = 0, indexBackup = 0, itemSum = 0;

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
                EasyUIDisplayStr(2 + 2 * FONT_WIDTH, item->position, item->title);
                break;
            case JUMP_PAGE:
                EasyUIDisplayStr(2, item->position, "+ ");
                EasyUIDisplayStr(2 + 2 * FONT_WIDTH, item->position, item->title);
                break;
            case PAGE_DESCRIPTION:
                EasyUIDisplayStr(2, item->position, item->title);
            default:
                break;
        }
    }
    // Draw indicator
    EasyUIDrawIndicator(page, index, timer);

    // Display navigation
    if (page->itemHead->funcType == PAGE_DESCRIPTION)
    {
        indexBackup = index;
        itemSum = page->itemTail->id;
    } else
    {
        indexBackup = index + 1;
        itemSum = page->itemTail->id + 1;
    }
    if (itemSum > 9)
    {
        EasyUIDisplayUint(SCREEN_WIDTH - 1 - 2 * FONT_WIDTH, SCREEN_HEIGHT - 1 - FONT_HEIGHT, itemSum, 2);
        EasyUIDisplayStr(SCREEN_WIDTH - 1 - 3 * FONT_WIDTH / 2, SCREEN_HEIGHT - 1 - 2 * FONT_HEIGHT, "/");
        if (indexBackup > 9)
            EasyUIDisplayUint(SCREEN_WIDTH - 1 - 2 * FONT_WIDTH, SCREEN_HEIGHT - 1 - 3 * FONT_HEIGHT, indexBackup, 2);
        else
            EasyUIDisplayUint(SCREEN_WIDTH - 1 - 3 * FONT_WIDTH / 2, SCREEN_HEIGHT - 1 - 3 * FONT_HEIGHT, indexBackup,
                              1);
    } else
    {
        EasyUIDisplayUint(SCREEN_WIDTH - 1 - 3 * FONT_WIDTH / 2, SCREEN_HEIGHT - 1 - FONT_HEIGHT, itemSum, 1);
        EasyUIDisplayStr(SCREEN_WIDTH - 1 - 3 * FONT_WIDTH / 2, SCREEN_HEIGHT - 1 - 2 * FONT_HEIGHT, "/");
        EasyUIDisplayUint(SCREEN_WIDTH - 1 - 3 * FONT_WIDTH / 2, SCREEN_HEIGHT - 1 - 3 * FONT_HEIGHT, indexBackup, 1);
    }

    // Key move reaction
    itemSum = page->itemTail->id;
    if (keyForward.isPressed)
    {
        if (index < itemSum)
            index++;
        else
            index = 0;
    }
    if (keyBackward.isPressed)
    {
        if (index > 0)
            index--;
        else
            index = itemSum;
    }
    if (keyConfirm.isPressed)
    {
        for (EasyUIItem_t *item = page->itemHead; item != NULL; item = item->next)
        {
            if (item->id == index)
            {
                if (item->funcType == JUMP_PAGE)
                {
                    if (layer < 9)
                    {
                        pageIndex[layer] = page->id;
                        itemIndex[layer] = index;
                        layer++;
                        pageIndex[layer] = item->pageId;
                        index = 0;
                        for (EasyUIItem_t *itemTmp = page->itemHead; itemTmp != NULL; itemTmp = itemTmp->next)
                        {
                            itemTmp->position = 0;
                            itemTmp->posForCal = 0;
                        }
                        EasyUITransitionAnim();
                        break;
                    } else
                        break;
                }
            }
        }
    }
    if (keyConfirm.isHold)
    {
        if (layer > 0)
        {
            pageIndex[layer] = 0;
            itemIndex[layer] = 0;
            layer--;
            index = itemIndex[layer];
            for (EasyUIItem_t *item = page->itemHead; item != NULL; item = item->next)
            {
                item->position = 0;
                item->posForCal = 0;
            }
            EasyUITransitionAnim();
        }
    }

    EasyUISendBuffer();
}