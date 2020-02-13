#ifndef UART_H
#define UART_H

#include<msp430.h>

typedef unsigned char _tByte;

void UART_Init();
void UART_SendByte(tByte c);

#endif // UART_H
