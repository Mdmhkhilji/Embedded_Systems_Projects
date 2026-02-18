/*
 * door_control.c
 *
 *  Created on: Feb 18, 2026
 *      Author: MDMHK
 */

#include "stm32f4xx_hal.h"

void Door_Open(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

void Door_Close(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

