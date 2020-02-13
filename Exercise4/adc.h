#ifndef ADC_H
#define ADC_H

#include<msp430.h>

typedef unsigned int tWord;
typedef unsigned int tByte;

void ADC_Init();
void ADC_Read();
void ADC_Write();
inline tWord ADC_GetValue();

#endif