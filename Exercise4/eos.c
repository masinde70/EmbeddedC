#include "eos.h"
#include "uart.h"

#include <signal.h>
#include <stdio.h>

#define DCO_FREQ 16*1e6
#define TIMER_INTERVAL 10

#define DIVIDER 8
#define TMRC (DCO_FREQ / DIVIDER / 1000 * TIMER_INTERVAL)

static sTask gTaskList[MAX_TASKS]

tByte gErrorCode = 0;
tWord gTickCount = 0;

void SetupTimer () {
	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDC0_16MHZ;
	BCSCTL2 = 0x0;

	//Enable interrupts on timer
	CCTL0 = CCIE;

	TACTL = TASSEL_2 + MC_1 + ID_3;

	CCR0 = TMRC;
}

void SCH_Start(){
	__enable_interrupt();
}

void SCH_AddTask(void *fPtr, tWord Delay, tWord Repeat) {
	tByte i;
	for (i = 0; i < MAX_TASKS; i++){
		if(!gTaskList[i].pTask){
			gTaskList[i].pTask = fPtr;
			gTaskList[i].Delay = (Delay / TIMER_INTERVAL) + 1;
			gTaskList[i].Repeat = (Repeat / TIMER_INTERVAL);
			gTaskList[i].RunMe = 0;
			return;
		}
	}
	return;
}

void SCH_Update(void){
	tByte i;
	for (i=0; i<MAX_TASKS; i++) {
		if (gTaskList[i].pTask){
			if(--gTaskList[i].Delay==0){
				gTaskList[i].RunMe++;
				if(gTaskList[i].Repeat)
					gTaskList[i].Delay = gTaskList[i].Repeat;
			}
		}
	}
}

static char buf[50];

void SCH_Dispatch(void){
	tByte idx;

	for (idx = 0; idx < MAX_TASKS; idx++) {
		if(gTaskList[idx].RunMe>0){
			(*gTaskList[idx].pTask)();
			gTaskList[idx].RunMe--;
		}
		if(gTaskList[idx].Repeat == 0){

		}
	}
}

void SCH_Init(){
	tByte idx;

	for(idx=0; idx<MAX_TASKS; idx++){
		gTaskList[idx].pTask = (0);
		gTaskList[idx].RunMe = 0;
	}

	SetupTimer();
}

__attribute__((interrupt(TIMER_A0_VECTOR))) void TIMER_A(void){
	gTickCount++;
	LPM0_EXIT;
	SCH_Update();
}