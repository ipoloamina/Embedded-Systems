#include "mbed.h"
#include <algorithm>

// DigitalOut redLED(PC_2,0);
// DigitalOut yellowLED(PC_3,0);
// DigitalOut greenLED(PC_6,0);
BusOut leds(PC_2, PC_3, PC_6);

// main() runs in its own thread in the OS
int main()
{
    /*int value, a, n;
    int(count(n=5; n<=20; n=++));

    do{
        scanf ("enter a value for a pattern");
        printf ("value=%d\n", value);

        scanf("enter a value for count");
        printf("n=%d\n", n);
    }*/
    while (true) {

        //For-Loop
        for (int n=7; n>=0; n = n-1) {
            printf("n=%d\n", n);
            leds = n;
            wait_us(250000);
        }

        //2s pause
        wait_us(2000000);
    }
}

