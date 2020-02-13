#include "project.h"
#include "led.h"

#include "timer.h"

#define DIVIDER 8
#define TMRC (DCO_FREQ / DIVIDER / 1000 * TIMER_INTERVAL)

static tWord tickCount=0;

void Timer_Init() {

        BCSCTL1 = CALBC1_16MHZ;
        DCOCTL = CALDCO_16MHZ;
        BCSCTL2 = 0x0 ; // MCLK clock source DCOCLK, MCLK divider 1, SMCLK source DCOCLK, SMCLK divider 1

        // Set up interrupts and timer 0

        // Enable interrupts on timer
        CCTL0 = CCIE;

        // Use clock SMCLK, UP counting, divided of 8
        TACTL = TASSEL_2 + MC_1 + ID_3;
       
        // Set compare value
        CCR0 = TMRC;
}

__attribute__((interrupt(TIMER0_A0_VECTOR))) void Timer_A(void) { 
tickCount++;
timer_run(); 
} 

tWord getTick() {return tickCount;}
