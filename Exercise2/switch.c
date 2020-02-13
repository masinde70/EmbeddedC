#include "project.h"
#include "ports.h"
#include "switch.h"

void Switch_Init(){
	SWITCH1_DIR &= ~(SWITCH1_BIT);
	P1OUT |= (SWITCH1_BIT);
	P1REN |= (SWITCH1_BIT);
}


void Switch_GetStat(){
	if (SWITCH1_IN & (SWITCH1_BIT))
	{
		return NOT_PRESSED;
	}
	else
		return PRESSED;
}