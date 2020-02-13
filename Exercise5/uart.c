#include "msp430.h"
#include "eos.h"
#include "uart.h"

#define TXD BIT2
#define RXD BIT1
 
unsigned int i;     //Counter

// Note these external global variables must be defined in another c-file
extern tByte gState;    // State of software
extern const tByte gMode; // Mode of software: Master / slave -- Please make sure that right is selected
extern tWord gTickCount;   // Global tick count
extern tWord gSlaveAckTick;  //Tick count of last ack from slave

void UART_Init(void)
{
  WDTCTL = WDTPW + WDTHOLD; // Stop WDT
  DCOCTL = 0; // Select lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_1MHZ; // Set DCO
  DCOCTL = CALDCO_1MHZ;
//  P2DIR |= 0xFF; // All P2.x outputs
//  P2OUT &= 0x00; // All P2.x reset
  P1SEL |= RXD + TXD ; // P1.1 = RXD, P1.2=TXD
  P1SEL2 |= RXD + TXD ; // P1.1 = RXD, P1.2=TXD
  P1OUT &= 0x00;
 

  UCA0CTL1 |= UCSWRST; // **Initialize USCI state machine**
  UCA0CTL1 |= UCSSEL_2; // SMCLK
  UCA0CTL0 |= UCMSB; // SMCLK

  UCA0BR0 = 0x68; // 1MHz 9600
  UCA0BR1 = 0x00; // 1MHz 9600
  UCA0MCTL = UCBRS1;// Modulation


  UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**

  UC0IE |= UCA0RXIE; // Enable USCI_A0 RX interrupt


  //  __bis_SR_register(CPUOFF + GIE); // Enter LPM0 w/ int until Byte RXed
}
 
void UART_SendByte(tByte c) {
    UCA0TXBUF = c;
}
  
__attribute__((interrupt(USCIAB0RX_VECTOR)))void USCI0RX_ISR(void)
{ 
  tByte Message;

  Message = UCA0RXBUF; // Read byte

  if (gMode == MASTER) {
    if (Message != ACK_SLAVE_OK) {
        gState = ERROR_SLAVE;
    }
    gSlaveAckTick = gTickCount;

} else  { // Code for SLAVE
  gState = Message;
  // Send ack-message
  UART_SendByte(ACK_SLAVE_OK);
  // Update scheduler
  SCH_Update();
}
}