#ifndef _PORTS_H
#define _PORTS_H

#include <msp430.h>


#define LED1 BIT0
#define LED2 BIT6
#define LED1_PORT P1OUT
#define LED1_DIR  P1DIR
#define LED1BIT   BIT0 //P1.0

#define LED2_PORT P1OUT
#define LED2_DIR  P1DIR
#define LED2BIT   BIT6 //p1.6

#define SWITCH1_PORT P1OUT
#define SWITCH1_DIR P1DIR
#define SWITCH1_READ  P1IN
#define SWITCH1_REN P1REN
#define SWITCH1_BIT (1<<3) //P1.3

#endif