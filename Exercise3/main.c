#include "project.h"
#include "led.h"
#include "switch.h"
#include "timer.h"
#include "uart.h"
#include "trafic.h"


void main(){
	WDTCTL = WDTPW | WDTHOLD;  //stop watchdog timer
	    
    Timer_Init();
	Led_Init(500);
	Switch_Init();
	Traffic_Init();
    UART_Init();

	_enable_interrupts();

	UART_Write("Starting system");

	while(1){
		LPM1;
	}
		
}


char buf[100];
void timer_run(){
	static unsigned int count;
	if (UART_Read(buf, 100)>0){
		UART_Write(buf);
		Traffic_Update();
	}
}