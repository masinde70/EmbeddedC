
#include<msp430.h>
#include "blink.h"
#include "uart.h"



tByte gState=0x7a;
extern const tByte gMode;


void main(){
	WDTCTL = WDTPW | WDTHOLD;  //stop watchdog timer

	SetupBlink();
	UART_Init();

	SCH_Init();
	SCH_AddTask(BlinkLed, 0, 200);

	SCH_Start();

	while(1){
		SCH_Dispatch();
	}

	return 0;
}