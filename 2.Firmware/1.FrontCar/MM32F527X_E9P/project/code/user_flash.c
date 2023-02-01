/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "user_flash.h"

static uint16_t bufIndex = 0;       // Flash buffer array index(0-255)
static uint8_t secIndex = 63;       // Flash section index(63-)
static uint8_t pageIndex = 3;       // Flash page index(3-0)

/*!
 * @brief       Convert double data(8 Byte) into unsigned int data(4 Byte)
 *
 * @param       val     The object to be converted
 * @param       arr    Target uint32 array
 * @return      void
 *
 * @note        Use a "double" pointer to point to this array,
 *              or use memcpy function
 *              can convert int data back to double
 */
void DoubleToInt(const double *val, uint32_t *arr)
{
    memcpy(arr, val, 2 * sizeof(uint32_t));
}


/*!
 * @brief       Convert double data(8 Byte) into unsigned int data(4 Byte)
 *
 * @param       val     The object to be converted
 * @param       arr    Target uint32 array
 * @return      void
 */
void IntToDouble(double *val, const uint32_t *arr)
{
    memcpy(val, arr, 2 * sizeof(uint32_t));
}


void SaveToFlash(const int32_t *value)
{
    if (secIndex == 0)
        return;

    if (bufIndex >= 256)
    {
        flash_write_page_from_buffer(secIndex, pageIndex);
        flash_buffer_clear();
        if (pageIndex > 0)
        {
            // Change page automatically
            pageIndex--;
            bufIndex = 0;
        } else
        {
            // Change section automatically
            pageIndex = 3;
            bufIndex = 0;
            secIndex--;
        }
    }

    flash_union_buffer[bufIndex].uint32_type = *value;
    bufIndex++;
}
void SaveToFlashWithConversion(const double *value)
{
    if (secIndex == 0)
        return;

    uint32_t arr[2];

    if (bufIndex + 1 >= 256)
    {
        flash_write_page_from_buffer(secIndex, pageIndex);
        flash_buffer_clear();
        if (pageIndex > 0)
        {
            // Change page automatically
            pageIndex--;
            bufIndex = 0;
        } else
        {
            // Change section automatically
            pageIndex = 3;
            bufIndex = 0;
            secIndex--;
        }
    }

    DoubleToInt(value, arr);
    flash_union_buffer[bufIndex].uint32_type = arr[0];
    flash_union_buffer[++bufIndex].uint32_type = arr[1];
    bufIndex++;
}


void ReadFlash(int32_t *value)
{
    if (secIndex == 0)
        return;

    if (bufIndex >= 256)
    {
        flash_buffer_clear();
        if (pageIndex > 0)
        {
            // Change page automatically
            pageIndex--;
            bufIndex = 0;
        } else
        {
            // Change section automatically
            pageIndex = 3;
            bufIndex = 0;
            secIndex--;
        }
    }

    flash_read_page_to_buffer(secIndex, pageIndex);

    *value = flash_union_buffer[bufIndex].int32_type;
    bufIndex++;
}
void ReadFlashWithConversion(double *value)
{
    if (secIndex == 0)
        return;

    uint32_t arr[2];

    if (bufIndex + 1 >= 256)
    {
        flash_write_page_from_buffer(secIndex, pageIndex);
        flash_buffer_clear();
        if (pageIndex > 0)
        {
            // Change page automatically
            pageIndex--;
            bufIndex = 0;
        } else
        {
            // Change section automatically
            pageIndex = 3;
            bufIndex = 0;
            secIndex--;
        }
    }

    flash_read_page_to_buffer(secIndex, pageIndex);

    arr[0] = flash_union_buffer[bufIndex].uint32_type;
    arr[1] = flash_union_buffer[++bufIndex].uint32_type;
    IntToDouble(value, arr);
    bufIndex++;
}


void FlashOperationEnd()
{
    flash_write_page_from_buffer(secIndex, pageIndex);
    flash_buffer_clear();
    bufIndex = 0;
    secIndex = 63;
    pageIndex = 3;
}