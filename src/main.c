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

    volatile uint16_t count = 0;
    register unsigned src asm("r5") = 0x1234;
    register unsigned dst asm("r6") = 0x0000;
    const uint16_t runs = 1000; //Number of iterations for averaging
    volatile uint16_t avg_cycles = 0;

    uartInitialize();                       // Initialize UART

    TA0CTL |= TASSEL__SMCLK | MC__CONTINOUS | TACLR; //Set up timer A with SMCKL as the clock source, continous mode and reset timer

    unsigned current_ts = TA0R; //Get the current value of the timer
    for(unsigned i = 0; i < runs; i++){
           __asm__ __volatile__ (
            "MOV %[s], %[d] \n" //Move the value from src to dst
            : [d] "=r" (dst)        //Output operand
            : [s] "r" (src)         //Input operand
            );
    };

    count = TA0R - current_ts; //Substract to get the difference in time aka the cycle count of the instruction
    avg_cycles = count/runs; //Calculate average cycles
    send_uint(dst);   //Send the value of dst over UART to verify the MOV instruction worked
    send_uint(avg_cycles); //Send the cycle count over UART
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