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
 * @note    Do not modify
 */
void EasyUIAddPage(EasyUIPage_t *page)
{
    page->itemHead = NULL;
    page->itemTail=  NULL;

    if(pageHead == NULL)
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
void EasyUIAddItem(EasyUIPage_t *page, EasyUIItem_t *item, char *_title, EasyUIFunc_e func, uint8_t _pageId, void (* _callback)())
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

    if(page->itemHead == NULL)
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


void EasyUI(uint16_t time)
{

}