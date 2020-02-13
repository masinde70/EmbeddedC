#ifndef _SWITCH_H
#define _SWITCH_H

#include <msp430.h>

tByte NOT_PRESSED = 0;
tByte PRESSED = 1;


void Switch_Init();

tByte Switch_GetStat();

#endif
