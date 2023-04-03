/*!
 * Copyright (c) 2022, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan
 */

#include "easy_key.h"

EasyKey_t keyL, keyC, keyR;
bool multiClickSwitch = true;
EasyKey_t *head = NULL, *tail = NULL;


void DebounceFilter(uint8_t timeUs)
{
    for (EasyKey_t *key = head; key != NULL; key = key->next)
    {
        key->cacheValue = gpio_get_level(key->pin);
    }

    system_delay_us(timeUs);

    uint8_t mask;
    for (EasyKey_t *key = head; key != NULL; key = key->next)
    {
        key->value = gpio_get_level(key->pin);
        mask = key->value ^ key->cacheValue;
        key->value |= mask;
    }
}


void PressCallback(EasyKey_t *key)
{
    key->isPressed = true;
}


void HoldCallback(EasyKey_t *key)
{
    key->isHold = true;
}


void MultiClickCallback(EasyKey_t *key)
{
    key->isMultiClick = true;
}


void ReleaseCallback(EasyKey_t *key)
{
    key->isMultiClick = false;
    key->isPressed = false;
    key->isHold = false;
}


/*!
 * @brief       Key linked list init
 * @param       key         Linked list's node
 * @param       pin         Gpio pin
 * @param       num         Gpio num
 * @param       period      Scanner period(ms), should be the same as the Timer period
 * @return      void
 * @sample      key_init(&key1, 'G', 1, 10)     Init G1 as key input, 10ms scanner period
 */
void EasyKeyInit(EasyKey_t *key, gpio_pin_enum _pin)
{
    key->state = released;
    key->next = NULL;
    key->holdTime = 0;
    key->intervalTime = 0;
    key->pin = _pin;
    key->preValue = 1;

    // GPIO init
    gpio_init(_pin, GPI, 0,GPI_PULL_UP);

    if(head == NULL)
    {
        head = key;
        tail = key;
    } else
    {
        tail->next = key;
        tail = tail->next;
    }
}


/*!
 * @brief       Key interrupt handler
 * @param       void
 * @return      void
 * @note        Don't modify
 */
void EasyKeyScanKeyState()
{
    DebounceFilter(FILTER_TIME_US);

    for (EasyKey_t *key = head; key != NULL; key = key->next)
    {
        // Update key state
        if (key->preValue > key->value)
            key->state = down;
        else if (key->preValue < key->value)
            key->state = up;
        else if (key->value == 0)
            key->state = pressed;
        else
            key->state = released;

        // Time counter
        switch (key->state)
        {
        case down:
            key->holdTime = 0;
            break;
        case up:
            key->intervalTime = 0;
            break;
        case pressed:
            key->holdTime += UPDATE_KEY_STATE_MS;
            break;
        default:
            if (key->intervalTime >= 3000)
                key->intervalTime = 3000;
            else
                key->intervalTime += UPDATE_KEY_STATE_MS;
            break;
        }

        // Store key value
        key->preValue = key->value;
    }
}


void EasyKeyUserApp()
{
    for (EasyKey_t *key = head; key != NULL; key = key->next)
    {
        ReleaseCallback(key);

        // Press and Hold callback
        if (key->state == up && key->holdTime > HOLD_THRESHOLD_MS)
            HoldCallback(key);
        if (key->state == up && key->holdTime < HOLD_THRESHOLD_MS)
            PressCallback(key);

        // Multiple clicks callback
        if (multiClickSwitch == false)
            continue;
        if (key->state == down && key->intervalTime < INTERVAL_THRESHOLD_MS)
            MultiClickCallback(key);
    }
//        // Key is pressed
//        if (key->value == 0)
//        {
//            // Press time counter
//            key->holdTime++;
//            continue;
//        }
//
//        // Key is released
//        // Trigger hold or release callback according to hold time
//        if (key->holdTime >= HOLD_THRESHOLD_MS)
//        {
//            HoldCallback(key);
//            continue;
//        }
//        else if (key->holdTime > 0 && multiClickSwitch == false)
//        {
//            PressCallback(key);
//            continue;
//        }
//
//        if (multiClickSwitch)
//        {
//            // Time counter for multiple clicks
//            key->intervalTime++;
//        }
//
//        //
//        if (key->intervalTime > 0 && key->intervalTime < INTERVAL_THRESHOLD_MS)
//            key->clickCnt++;
//        if (key->clickCnt > 0)
//            MultiClickCallback(key);
//
//        // Interval time is too long, trigger press callback
//        if (key->intervalTime >= INTERVAL_THRESHOLD_MS)
//            PressCallback(key);
//
}