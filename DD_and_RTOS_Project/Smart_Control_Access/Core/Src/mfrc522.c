/*
 * mfrc522.c
 *
 *  Created on: Feb 18, 2026
 *      Author: MDMHK
 */

#include "mfrc522.h"

static SPI_HandleTypeDef *rfid_spi;

#define RFID_CS_LOW()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define RFID_CS_HIGH() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

void MFRC522_Init(SPI_HandleTypeDef *hspi)
{
    rfid_spi = hspi;
    RFID_CS_HIGH();
}

uint8_t MFRC522_Check(uint8_t *uid)
{
    // Simplified UID simulation for testing
    uid[0] = 0xDE;
    uid[1] = 0xAD;
    uid[2] = 0xBE;
    uid[3] = 0xEF;
    HAL_Delay(1000);
    return 1;
}

