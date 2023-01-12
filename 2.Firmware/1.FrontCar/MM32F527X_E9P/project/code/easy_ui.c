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
 *
 * @note    Do not modify, the first page should always be the fist one to be added.
 */
void EasyUIAddPage(EasyUIPage_t *page)
{
    page->itemHead = NULL;
    page->itemTail = NULL;

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
 */
void EasyUIAddItem(EasyUIPage_t *page, EasyUIItem_t *item, char *_title, EasyUIFunc_e func, ...)
{
    va_list variableArg;
    va_start(variableArg, func);
    item->funcType = func;
    switch (item->funcType)
    {
        case CALL_FUNCTION:
            item->Function = va_arg(variableArg, void (* )(uint8_t, ...));
            break;
        case JUMP_PAGE:
            item->pageId = va_arg(variableArg, int);
            break;
        default:
            break;
    }

    item->title = _title;

    if (page->itemHead == NULL)
    {
        item->id = 0;
        page->itemHead = item;
        page->itemTail = item;
    } else
    {
        item->id = page->itemTail->id;
        page->itemTail->next = item;
        page->itemTail = page->itemTail->next;
    }
    item->position = item->id;
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
            EasyUIDrawDot(i - 1, j - 1, IPS114_backgroundColor);
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
    EasyUISetDrawColor(NORMAL);
    EasyUIDrawRFrame(x, y, width, height, IPS114_penColor);
    EasyUIDrawBox(x + 1, y + 1, width - 2, height - 2, IPS114_backgroundColor);
    EasyUISendBuffer();
}

void EasyUIIndicatorMoveAnim(int16_t dest, int16_t src, uint8_t time)
{

}

void EasyUIItemMoveAnim(int16_t dest, int16_t src, uint8_t time)
{

}

/*!
 * @brief   Welcome Page with two size of photo
 *
 * @param   mode    choose the size of photo.(0 for smaller one and 1 for bigger one)
 * @return  void
 */
void EasyUIInit(uint8_t mode)
{
    EasyUIScreenInit();
    if (mode)
        EasyUIDisplayBMP((SCREEN_WIDTH - 58) / 2, (SCREEN_HEIGHT - 56) / 2, 58, 56, ErBW_s_5856);
    else
        EasyUIDisplayBMP((SCREEN_WIDTH - 29) / 2, (SCREEN_HEIGHT - 28) / 2, 29, 28, ErBW_s_2928);
    if (SCREEN_WIDTH > (25 * FONT_WIDTH + 1))
        EasyUIDisplayStr(SCREEN_WIDTH - 1 - 25 * FONT_WIDTH, SCREEN_HEIGHT - 1 - FONT_HEIGHT, "Powered by EasyUI(ErBW_s)");
    else if (SCREEN_WIDTH > (14 * FONT_WIDTH + 1))
        EasyUIDisplayStr(SCREEN_WIDTH - 1 - 25 * FONT_WIDTH, SCREEN_HEIGHT - 1 - FONT_HEIGHT, "EasyUI(ErBW_s)");
    EasyUISendBuffer();
}


void EasyUI(uint8_t time)
{
    static uint8_t pageIndex[20] = {0};     // Page id (stack)
    static uint8_t itemIndex[20] = {0};     // Item id (stack)
    static uint8_t layer = 0;               // pageIndex[layer] / itemIndex[layer]
    static uint8_t index = 0;
    static uint8_t itemHeightOffset = (ITEM_HEIGHT - FONT_HEIGHT) / 2;

    EasyUIClearBuffer();

    EasyUIPage_t *page = pageHead;
    while (page->id != pageIndex[layer])
    {
        page = page->next;
    }
    EasyUISetDrawColor(XOR);
//    IPS114_DrawRBox(0, (int16_t) y, (int16_t) w, 16, IPS114_penColor);
    EasyUISetDrawColor(NORMAL);
    for (EasyUIItem_t *item = page->itemHead; item != NULL; item = item->next)
    {
        switch (item->funcType)
        {
            case CALL_FUNCTION:
                EasyUIDisplayStr(2, itemHeightOffset + item->id * ITEM_HEIGHT, "- ");
                break;
            case JUMP_PAGE:
                EasyUIDisplayStr(2, itemHeightOffset + item->id * ITEM_HEIGHT, "+ ");
                break;
            default:
                break;
        }
        EasyUIDisplayStr(2 + 2 * FONT_WIDTH, itemHeightOffset + item->id * ITEM_HEIGHT, item->title);
    }
}