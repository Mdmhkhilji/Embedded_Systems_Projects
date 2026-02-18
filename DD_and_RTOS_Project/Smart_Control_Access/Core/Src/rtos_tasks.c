/*
 * rtos_tasks.c
 *
 *  Created on: Feb 18, 2026
 *      Author: MDMHK
 */

#include "cmsis_os.h"
#include "mfrc522.h"
#include "auth.h"
#include "door_control.h"
#include "lcd.h"

osMessageQueueId_t rfidQueue;
osMessageQueueId_t authQueue;
osMutexId_t lcdMutex;

void RFID_Task(void *argument)
{
    uint8_t uid[4];

    for(;;)
    {
        if(MFRC522_Check(uid))
            osMessageQueuePut(rfidQueue, uid, 0, 0);
    }
}

void AUTH_Task(void *argument)
{
    uint8_t uid[4];
    uint8_t result;

    for(;;)
    {
        osMessageQueueGet(rfidQueue, uid, NULL, osWaitForever);
        result = Authenticate(uid);
        osMessageQueuePut(authQueue, &result, 0, 0);
    }
}

void DOOR_Task(void *argument)
{
    uint8_t result;

    for(;;)
    {
        osMessageQueueGet(authQueue, &result, NULL, osWaitForever);

        if(result)
        {
            Door_Open();
            LCD_Print("Access Granted");
            osDelay(3000);
            Door_Close();
        }
        else
        {
            LCD_Print("Access Denied");
        }
    }
}

void LCD_Task(void *argument)
{
    for(;;)
    {
        osDelay(1000);
    }
}

