/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "user_flash.h"

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
void DoubleToInt(const double val, uint32_t *arr)
{
    memcpy(arr, &val, 2 * sizeof(uint32_t));
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