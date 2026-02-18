/*
 * mfrc522.h
 *
 *  Created on: Feb 18, 2026
 *      Author: MDMHK
 */

#ifndef MFRC522_H
#define MFRC522_H

#include "stm32f4xx_hal.h"

void MFRC522_Init(SPI_HandleTypeDef *hspi);
uint8_t MFRC522_Check(uint8_t *uid);

#endif
