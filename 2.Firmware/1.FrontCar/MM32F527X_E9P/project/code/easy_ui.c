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
 * @param   _pageId     If CALL_FUNCTION, just fill this with 0
 * @param   _callback   If JUMP_PAGE, just fill this with
 */
void EasyUIAddItem(EasyUIPage_t *page, EasyUIItem_t *item, char *_title, EasyUIFunc_e func, uint8_t _pageId,
                   void (*_callback)())
{
    item->funcType = func;
    switch (item->funcType)
    {
        case CALL_FUNCTION:
            item->callback = _callback;
            break;
        case JUMP_PAGE:
            item->pageId = _pageId;
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
}

/*!
 * @brief   Blur transition animation
 */
void EasyUITransitionAnim()
{
    for (int j = 1; j < SCREEN_HEIGHT + 1; j += 2)
    {
        for (int i = 0; i < SCREEN_WIDTH + 1; i += 2)
        {
            EasyUI_DrawDot(i, j, IPS114_backgroundColor);
        }
    }
    IPS114_SendBuffer();
    for (int j = 1; j < SCREEN_HEIGHT + 1; j += 2)
    {
        for (int i = 1; i < SCREEN_WIDTH + 1; i += 2)
        {
            EasyUI_DrawDot(i, j, IPS114_backgroundColor);
        }
    }
    IPS114_SendBuffer();
    for (int j = 1; j < SCREEN_HEIGHT + 1; j += 2)
    {
        for (int i = 1; i < SCREEN_WIDTH + 1; i += 2)
        {
            EasyUI_DrawDot(i - 1, j - 1, IPS114_backgroundColor);
        }
    }
    IPS114_SendBuffer();
    for (int j = 0; j < SCREEN_HEIGHT + 1; j += 2)
    {
        for (int i = 1; i < SCREEN_WIDTH + 1; i += 2)
        {
            EasyUI_DrawDot(i, j, IPS114_backgroundColor);
        }
    }
    IPS114_SendBuffer();
}

/*!
 * @brief   Blur the background for rounded box
 */
void EasyUIDrawRBoxWithBlur()
{
    for (int j = 1; j < SCREEN_HEIGHT + 1; j += 2)
    {
        for (int i = 1; i < SCREEN_WIDTH + 1; i += 2)
        {
            EasyUI_DrawDot(i, j, IPS114_backgroundColor);
        }
    }
    IPS114_SendBuffer();
    for (int j = 1; j < SCREEN_HEIGHT + 1; j += 2)
    {
        for (int i = 1; i < SCREEN_WIDTH + 1; i += 2)
        {
            EasyUI_DrawDot(i - 1, j - 1, IPS114_backgroundColor);
        }
    }
    IPS114_SendBuffer();
    EasyUI_DrawRBox(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, IPS114_penColor);
    EasyUI_FillWithColor(SCREEN_WIDTH / 4 + 1, SCREEN_HEIGHT / 4 + 1, SCREEN_WIDTH / 2 - 2, SCREEN_HEIGHT / 2 - 2, IPS114_backgroundColor);
    IPS114_SendBuffer();
}

void EasyUI(uint16_t time)
{
    static uint8_t pageIndex[20] = {0};     // Page id (stack)
    static uint8_t itemIndex[20] = {0};     // Item id (stack)
    static uint8_t layer = 0;               // pageIndex[layer] / itemIndex[layer]

    EasyUIPage_t *page = pageHead;
    while (page->id != pageIndex[layer])
        page = page->next;
    for (EasyUIItem_t *item = page->itemHead; item != NULL; item = item->next)
    {
        switch (item->funcType)
        {
            case CALL_FUNCTION:
                EasyUI_DisplayStr(2, ((ITEM_HEIGHT - FONT_HEIGHT) / 2) + item->id * ITEM_HEIGHT, "- ");
                break;
            case JUMP_PAGE:
                EasyUI_DisplayStr(2, ((ITEM_HEIGHT - FONT_HEIGHT) / 2) + item->id * ITEM_HEIGHT, "+ ");
                break;
            default:
                break;
        }
        EasyUI_DisplayStr(2 + 2 * FONT_WIDTH, ((ITEM_HEIGHT - FONT_HEIGHT) / 2) + item->id * ITEM_HEIGHT, item->title);
    }
}