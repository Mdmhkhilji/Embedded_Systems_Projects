/*
 * auth.c
 *
 *  Created on: Feb 18, 2026
 *      Author: MDMHK
 */


#include "auth.h"

uint16_t valid_uid[4] = {0xDE,0xAD,0xBE,0xEF};

uint16_t Authenticate(uint8_t *uid)
{
    for(int i=0;i<4;i++)
        if(uid[i] != valid_uid[i]) return 0;
    return 1;
}
