#include "mbed.h"

#define WAIT_TIME_MS 2000

DigitalOut redLED(PC_2,1);
DigitalOut yellowLED(PC_3,1);
DigitalOut greenLED(PC_6,1);



int main()
{
    printf("Task 114\n");
    redLED = 1;
    yellowLED = 0;
    greenLED = 0;
    wait_us(WAIT_TIME_MS * 1000);

    redLED = 1;
    yellowLED = 1;
    greenLED = 0;
    wait_us(WAIT_TIME_MS * 1000);

    redLED = 0;
    yellowLED = 0;
    greenLED = 1;
    wait_us(WAIT_TIME_MS * 1000);

    redLED = 0;
    yellowLED = 0;
    greenLED = 0;

    int n;
    for (n = 4; n >= 0; n++)
    {
        wait_us(WAIT_TIME_MS * 1000);
        yellowLED = 1;
        yellowLED = 1;
        yellowLED = 1;
        yellowLED = 1;
        wait_us(WAIT_TIME_MS * 1000);
        yellowLED = 0;
        yellowLED = 0;
        yellowLED = 0;
        yellowLED = 0; 

        /*if (n <= 0){
            break;
        }*/    
    } 
    
    
    while (true) 
    {
        redLED = !redLED;
        yellowLED = !yellowLED;
        greenLED = !greenLED;
        wait_us(WAIT_TIME_MS * 1000);

    }
}

