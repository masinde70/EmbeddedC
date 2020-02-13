#include <stdio.h>
#include "project.h"
#include "ports.h"
#include "timer.h"
#include "adc.h"
#include  "uart.h"


tWord gADCLastVal=0;
char buf[25];


void ADC_Init() {
	ADC10CTL0 &= ~ENC;
	ADC10CTL0 = ADC10ON + ADC10SHT_3;

	ADC10CTL1 = INCH_10 + ADC10SSEL_3 + ADC10DIV_4;
}


void ADC_Read(){
	tWord count = 32000;
	ADC10CTL0 |= ENC + ADC10SC;

	while ((ADC10CTL1 & ADC10BUSY) && --count);
	if (!count) UAR_Write("ADC Timeout error");

	gADCLastVal = ADC10MEM;
	ADC10CTL0 &= ~ENC;
}

void ADC_Write() {
	tWord i;
	tWord val = ADC_GetValue();
	tByte q, c = 0;

	snprintf(buf, 25, "val:  %i\n", val);
	UAR_Write(buf);
}

inline tWord ADC_GetValue(){return gADCLastVal;}