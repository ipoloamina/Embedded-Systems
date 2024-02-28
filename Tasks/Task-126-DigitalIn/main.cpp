#include "mbed.h"

DigitalIn ButtonA(PG_0); //Button A
DigitalIn ButtonB(PG_1); //BUTTON B
DigitalIn ButtonC(PG_2, PinMode::PullDown); //Button C
DigitalIn ButtonD(PG_3, PinMode::PullDown); //Button D
DigitalOut redLED(PC_2); //Red Traffic 1
DigitalOut greenLED(PC_6); //Green Traffic

// main() runs in its own thread in the OS
int main()
{
    int btnA;
    int btnB;
    // Turn OFF the red LED
    redLED = 0;
    greenLED = 0;

    while (true) {
    
        // Wait for the button to be pressed
        do {
            btnA = ButtonA; //Read button A
        } while (btnA == 0);
        
        //Toggle the red LED
        redLED = !redLED;
        
        do {
            btnB = ButtonB; //Read button B
        } while (btnB == 0);

        //Toggle the green LED
        greenLED = !greenLED;

        //Wait for noise to settle
        wait_us(10000);

        // Wait for the button to be released
        do {
            btnA = ButtonA; //Read button A
        } while (btnA == 1);
        
        do {
            btnB = ButtonB; //Read button B
        } while (btnA == 1);

        //Wait for noise to settle
        wait_us(10000);
    }
}

