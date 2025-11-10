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

    register unsigned start_timer asm("r4"); //Stores the starting time of the benchmark
    register unsigned end_timer asm("r5"); //Stores the ending time of the benchmark
    register unsigned count asm("r6"); //Stores the cycle count of the benchmarked instruction
    register unsigned r7 asm("r7");
    register unsigned r8 asm("r8");
    register unsigned r9 asm("r9"); 

    uartInitialize();                       // Initialize UART

    TA0CTL |= TASSEL__SMCLK | MC__CONTINOUS | TACLR; //Set up timer A with SMCKL as the clock source, continous mode and reset timer

    unsigned current_ts = TA0R; //Get the current value of the timer
    for(unsigned i = 0; i < 2; i++){
        __asm__ __volatile__ (
            //Clear timer and count registers
            "mov #0, r4\n"
            "mov #0, r5\n"
            "mov #0, r6\n"
            //Initialize registers for benchmarking
            "mov #42, r7\n"
            "mov #0, r8\n"
            "mov #0, r9\n"

            "mov &TA0R, r4\n" // Get start time
            //benchmark_instruction
            "mov &TA0R, r5\n" // Get end time
        );
    };

    count = end_timer - start_timer; //Substract to get the difference in time aka the cycle count of the instruction
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