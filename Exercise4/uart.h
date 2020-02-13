#ifndef UART_H
#define UART_H

typedef unsigned char _tByte;

void UART_Init();
void UART_SendByte(_tByte c);

void UART_Write(char *);
_tByte UART_Read(char *, _tByte max);

#endif // UART_H
