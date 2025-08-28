#include <msp430.h>
#include <stdio.h>
#include "UART.h"

void send_uint(unsigned int number);

int main(void) {

    //Code that makes UART work for some unknown (to me) reason
    WDTCTL = WDTPW | WDTHOLD;  // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO power-on default high-impedance mode
                               // to activate previously configured port settings

    P1DIR |= BIT0;   // set P1.0 as output
    P1OUT &= ~BIT0;  // clear P1.0

    P4DIR |= BIT7;   // set P4.7 as output
    P4OUT &= ~BIT7;  // clear P4.7

    P5DIR |= BIT1;   // set P5.1 as output
    P5OUT &= ~BIT1;  // clear P5.1

    P5DIR |= BIT0;   // set P5.0 as output
    P5OUT &= ~BIT0;  // clear P5.0

    volatile unsigned count = 0;
    volatile int x = 0;
    volatile registerCheck = 0;

    uartInitialize();                       // Initialize UART

    TA0CTL |= TASSEL__SMCLK | MC__CONTINOUS | TACLR; //Set up timer A with SMCKL as the clock source, continous mode and reset timer

    unsigned current_ts = TA0R; //Get the current value of the timer
    __asm__("NOP"); //Instruction to measure
    count = TA0R - current_ts; //Substract to get the difference in time aka the cycle count of the instruction

    send_uint(count); //Send the cycle count over UART
}

// Function to send an unsigned integer over UART
// It converts the number to a string and sends each character
void send_uint(unsigned int number) {
    char s[11] = {0};
    s[10] = 0;
    sprintf(s, "%u", number);
    for (int i = 0; i < 10; i++) {
        send(s[i]);
    }
    send('\n');
}