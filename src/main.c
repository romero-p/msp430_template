#include "msp430-gcc/include/msp430.h"
#include "msp430-gcc/include/msp430fr5994.h"

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    volatile unsigned count = 0;
    volatile int x = 0;

    TA0CTL |= TASSEL__SMCLK | MC__CONTINOUS | TACLR; //Set up timer A with SMCKL as the clock source, continous mode and reset timer

    unsigned current_ts = TA0R; //Get the current value of the timer
    x = x + 1; //some instruction
    count = TA0R - current_ts; //Substract to get the difference in time aka the cycle count of the instruction

    while(1); //debugging purposes
}
