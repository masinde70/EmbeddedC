#ifndef EOS_H
#define EOS_H

#include<msp430.h>


typedef struct 
{
	void (*pTask)(void);
	tWord Delay;
	tWord Repeat;
	tByte RunMe;
}sTask;


#define MAX_TASK 5;

void SCH_AddTask(void *fptr, tWord Delay, tWord Repeat);
void SCH_Init();
void SCH_Dispatch(void);
void SCH_Update(void);
void SCH_Start(void);


#endif