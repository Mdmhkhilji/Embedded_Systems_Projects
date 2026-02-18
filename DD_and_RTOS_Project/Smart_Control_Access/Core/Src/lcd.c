/*
 * lcd.c
 *
 *  Created on: Feb 18, 2026
 *      Author: MDMHK
 */


#include "lcd.h"
#include "cmsis_os.h"

extern osMutexId_t lcdMutex;

void LCD_Init(void)
{
}

void LCD_Print(char *msg)
{
    osMutexAcquire(lcdMutex, osWaitForever);
    // send string to LCD
    osMutexRelease(lcdMutex);
}
