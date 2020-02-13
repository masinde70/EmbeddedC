#include "project.h"
#include "trafic.h"
#include "ports.h"
#include "switch.h"
#include  "uart.h"
#include "led.h"

typedef enum {RED, RED_AMBER, GREEN, AMBER} eLightState;

eLightState TRAFFIC_state_G;
tWord TRAFFIC_time_in_state_G = 0;
tByte gotoGreen = 0;

#define TIME_RED (5 * 1000 / TIMER_INTERVAL)
#define TIME_RED_AMBER (0.5 * 1000 / TIMER_INTERVAL)
#define TIME_GREEN (5 * 1000 / TIMER_INTERVAL)
#define TIME_AMBER (0.5 * 1000 / TIMER_INTERVAL)

void Traffic_Init() {
	TRAFFIC_state_G = RED;
}

void Traffic_Update() {
	if (Switch_GetStat() == PRESSED) {
		gotoGreen = 1;
    }
TRAFFIC_time_in_state_G++;

switch (TRAFFIC_state_G) {
	case RED:
		Led_Set(RED_LED, LED_ON);
		Led_Set(GREEN_LED, LED_OFF);
		if (TRAFFIC_time_in_state_G > TIME_RED || gotoGreen) {
			TRAFFIC_time_in_state_G = 0;
			TRAFFIC_state_G = RED_AMBER;
			UART_Write("Going to RED_AMBER");
			gotoGreen = 0;
		}
		break;
	case RED_AMBER:
		Led_Set(RED_LED, LED_ON);
		Led_Set(GREEN_LED, LED_ON);
		if (TRAFFIC_time_in_state_G > TIME_RED_AMBER) {
			TRAFFIC_time_in_state_G = 0;
			TRAFFIC_state_G = GREEN;
			UART_Write("Going to GREEN");
		}
		break;
	case GREEN:
		Led_Set(RED_LED, LED_OFF);
		Led_Set(GREEN_LED, LED_ON);
		if(TRAFFIC_time_in_state_G > TIME_AMBER) {
			TRAFFIC_time_in_state_G = 0;
            TRAFFIC_state_G = AMBER;
		}
		break;
	case AMBER:
	    Led_Set(RED_LED, LED_ON);
	    Led_Set(GREEN_LED, LED_ON);
	    if (TRAFFIC_time_in_state_G > TIME_AMBER){
	    	TRAFFIC_time_in_state_G = 0;
	    	TRAFFIC_state_G = RED;
	    	UART_Write("Going to RED");
	    }
	    break;

}

}

