#include "project.h"

#include "led.h"
#include "switch.h"
#include "timer.h"


void main(){
	WDTCTL = WDTPW | WDTHOLD;  //stop watchdog timer

	Led_Init(500);
	Switch_Init();
	Timer_Init();
	_enable_interrupts();

	while(1){
		LPM1;
		if(Switch_GetStat() == PRESSED){
			Led_Setstat(LEDSTAT_ON);
		}
		Led_Setstat(LEDSTAT_BLINK);
	}

}