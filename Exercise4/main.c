#include "project.h"
#include "led.h"
#include "switch.h"
#include "timer.h"
#include "adc.h"
#include  "uart.h"
#include "eos.h"

void main(){
	WDTCTL = WDTPW | WDTHOLD;  //stop watchdog timer

	Led_Init(500);
	UART_Init();
	SCH_Init();
	ADC_Init();
	Switch_Init();
	Timer_Init();
	_enable_interrupts();

	SCH_AddTask(Led_Update, 0, 100);
	SCH_AddTask(ADC_Read, 10, 500);
	SCH_AddTask(ADC_Write, 20, 1000);

	UART_Write("Starting up\n\r");

	SCH_Start();

	while(1){
		SCH_Dispatch();
	}

	return 0;

}