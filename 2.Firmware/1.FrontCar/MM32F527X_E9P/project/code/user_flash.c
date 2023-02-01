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
#ifdef FPU
void DoubleToInt(const double val, uint32_t *arr)
#else
void DoubleToInt(const int64_t val, uint32_t *arr)
#endif
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
#ifdef FPU
void IntToDouble(double *val, const uint32_t *arr)
#else
void IntToDouble(int64_t *val, const uint32_t *arr)
#endif
{
    memcpy(val, arr, 2 * sizeof(uint32_t));
}