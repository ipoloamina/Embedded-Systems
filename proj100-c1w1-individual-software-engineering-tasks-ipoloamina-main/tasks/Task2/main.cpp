/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <chrono>
#include <cstdlib>
#include <stdio.h>
#include "uop_msb.h"
#include "LEDMatrix.hpp"
#include "vt100-utils.hpp"

using namespace uop_msb;

//On board LEDs
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

//Traffic Light Set 1 (PUSH PULL - Set PIN MIGH to light the LED)
DigitalOut ledTraffic1Red(TRAF_RED1_PIN,0);
DigitalOut ledTraffic1Yellow(TRAF_YEL1_PIN,0);
DigitalOut ledTraffic1Green(TRAF_GRN1_PIN,0);

//Traffic Light Set 2 (Open Drain - so set PIN LOW to light the LED)
DigitalInOut ledTraffic2Red(TRAF_RED2_PIN, PinDirection::PIN_OUTPUT, PinMode::OpenDrainNoPull, 0);
DigitalInOut ledTraffic2Yellow(TRAF_YEL2_PIN, PinDirection::PIN_OUTPUT, PinMode::OpenDrainNoPull, 0);
DigitalInOut ledTraffic2Green(TRAF_GRN2_PIN, PinDirection::PIN_OUTPUT, PinMode::OpenDrainNoPull, 0);

//Switch Inputs
DigitalIn switchA(BTN1_PIN);        //Push to pull HIGH
DigitalIn switchB(BTN2_PIN);        //Push to pull HIGH
DigitalInOut switchC(BTN3_PIN, PinDirection::PIN_INPUT, PinMode::PullDown,0);        //Push to pull HIGH
DigitalInOut switchD(BTN4_PIN, PinDirection::PIN_INPUT, PinMode::PullDown,0);        //Push to pull HIGH
DigitalIn blueButton(USER_BUTTON);  //Push to pull HIGH


LCD_16X2_DISPLAY display;
DigitalOut backLight(LCD_BKL_PIN,1);

int main()
{
    //Write to terminal
    clearTerminal();
    puts("TASK 2");

    //Write to LCD screen
    display.cls();          //Clear
    display.locate(0, 0);   //Set cursor to the top left
    
    //Generate a crude random number between 5 and 30
    int counter = 5 + rand() % 25;
    display.cls();
    display.puts("Press Blue Btn.");
    display.locate(1, 0);
    display.puts("Randomising....");
    while (blueButton == 0) {
        counter = 5 + rand() % 25;
        ledTraffic1Red    = counter & 1;
        ledTraffic1Yellow = counter & 2;
        ledTraffic1Green  = counter & 4;
        wait_us(10000);
    }

    //Turn off all traffic lights
    ledTraffic1Red    = 0;
    ledTraffic1Yellow = 0;
    ledTraffic1Green  = 0;
    
    //Display count
    display.cls();
    display.printf("TASK 2");
    display.locate(1,0);
    display.printf("Counter=%d", counter);

    // At this point, the BLUE button has been pressed.....

    // (a) Wait for blue button to be released.
    while (blueButton == 0);
    //wait for 0.2seconds
    wait_us(200000); 

    // (b) Start the count down as soon as the blue button is released 
    //     - Flash led1 on and off each second
    //     - Show the count decrement once a second on the lCD (starting with the value in the variable `counter`). 
    //     - Only update the LCD when the count changes

    if (blueButton == 0) 
    {
        int cdown = counter;
        while (cdown > 0) 
        {
            cdown--;
            display.cls();
            display.printf("TASK 2");
            display.locate(1,0);
            display.printf("Counter = %d", cdown);

            wait_us(200000);
        }
    }
    // (c) If the blue button is pressed during the countdown: stop the countdown, wait for the button to be released and restart the program.

    if (blueButton == 1) 
    {
        int cdown = counter;
        while (cdown == 0)
        {
            //Wait for the blueButton to be released
            wait_us(200000);
            if (blueButton == 0) 
            {
                while(blueButton == 0);
                break;;
            }  
        }
    }
    // (d) When the counter reaches zero, read all four switches switchA, switchB, switchC and switchD
    
    int cdown = counter;
    while (cdown == 0) 
    {
        //Read all four switches
        bool switchAState = switchA; //Read the digital value of switchA
        bool switchBState = switchB; //Read the digital value of switchB
        bool switchCState = switchC; //Read the digital value of switchC
        bool switchDState = switchD; //Read the digital value of switchD
    }

    // (e) If only 'A' is pressed, turn on the Red LED on for 5 seconds
    //     If only 'B' is pressed, turn on the Green LED on for 5 seconds
    //     If only 'C' is pressed, turn on the Yellow LED on for 10 seconds 
    //     If only 'D' is pressed, flash all three LEDs for 15 seconds 
    //     If two or more buttons are pressed, turn on the RED LED for 1 second, then the Yellow for 1 second, then the Green for 1 second.



    // END
    puts("DONE");
    while(1);
}
