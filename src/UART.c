#include "UART.h"

void uartInitialize() {
    P2SEL0 &= ~(BIT0 | BIT1);
    P2SEL1 |= BIT0 | BIT1;  // USCI_A0 UART operation

    // Startup clock system with max DCO setting ~8MHz
    CSCTL0_H = CSKEY_H;            // Unlock CS registers
    CSCTL1 = DCOFSEL_3 | DCORSEL;  // Set DCO to 8MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;  // Set all dividers
    CSCTL0_H = 0;                          // Lock CS registers

    // Configure USCI_A0 for UART mode
    UCA0CTLW0 = UCSWRST;         // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK;  // CLK = SMCLK
    // Baud Rate calculation
    // 8000000/(16*9600) = 52.083
    // Fractional portion = 0.083
    // User's Guide Table 21-4: UCBRSx = 0x04
    // UCBRFx = int ( (52.083-52)*16) = 1
    UCA0BRW = 52;  // 8000000/16/9600
    UCA0MCTLW |= UCOS16 | UCBRF_1 | 0x4900;
    UCA0CTLW0 &= ~UCSWRST;  // Initialize eUSCI
    UCA0IE |= UCRXIE;       // Enable USCI_A0 RX interrupt
}

void send(char c) {
    // Wait for previos action to be finished
    while (!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = c;
    __delay_cycles(3);
}
