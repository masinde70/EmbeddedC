#include "project.h"
#include "ports.h"
#include "timer.h"

#include "led.h"

tWord blinkInterval;
tByte gLedStat = LEDSTAT_BLINK;

void Led_Init(tWord interval){
	LED1_DIR |=LED1BIT;
    LED1_PORT |= LED1BIT;

    LED2_DIR |= LED2BIT;
    LED2_PORT &= ~LED2BIT;

    blinkInterval = interval / TIMER_INTERVAL;
}

void Led_Setstat(tByte a){
	gLedStat = a;
}

void Led_Update(){
	static tWord lastUpdate=0;

	switch (gLedStat)  {
		case LEDSTAT_OFF:
			 LED1_PORT &= ~(LED1BIT);
			 LED2_PORT &= ~(LED2BIT);
			 break;

		case LEDSTAT_ON:
		     LED1_PORT |= (LED1BIT);
		     LED2_PORT |= (LED2BIT);
		     break;
		      
		case LEDSTAT_BLINK:
		    if(getTick() - lastUpdate >=blinkInterval){
		 		LED1_PORT ^= (LED1BIT);
		 		LED2_PORT ^=(LED2BIT);
		 		lastUpdate = getTick(); 
		 	}
		 	 break;

	}
}
