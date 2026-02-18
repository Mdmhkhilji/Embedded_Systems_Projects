/*
 * rtos_tasks.h
 *
 *  Created on: Feb 18, 2026
 *      Author: MDMHK
 */

#ifndef RTOS_TASKS_H
#define RTOS_TASKS_H

void RFID_Task(void *argument);
void AUTH_Task(void *argument);
void DOOR_Task(void *argument);
void LCD_Task(void *argument);

#endif
