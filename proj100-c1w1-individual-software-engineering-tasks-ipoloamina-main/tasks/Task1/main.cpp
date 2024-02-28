/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include "PinNamesTypes.h"
#include "mbed.h"
#include "uop_msb.h"
#include "vt100-utils.hpp"

using namespace uop_msb;

//On board LEDs
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

//Traffic Light Set 1 (PUSH PULL - Set PIN MIGH to light the LED)
DigitalOut ledTraffic1Red(TRAF_RED1_PIN,1);
DigitalOut ledTraffic1Yellow(TRAF_YEL1_PIN,1);
DigitalOut ledTraffic1Green(TRAF_GRN1_PIN,1);

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


int main()
{
    // ******************************************************
    // STUDENTS NOTE - you must set the Baud rate to 115200 *
    // ******************************************************
    hideCursor();       //Turn off the cursor in the terminal to avoid flickering 
    clearTerminal();    //Clear the terminal

    //Wait for button A to be pressed and released
    printf("TASK 1 - press the blue button to start\n");
    while (blueButton == 0);    //Wait for button press

    clearTerminal();    //Clear the terminal
    printf("TASK 1\n"); //Display prompt

    //Create a Buzzer
    Buzzer buzz;
  
    //Very fast polling loop
    while (true)
    {
        // Read all switches
        unsigned swA = switchA.read();
        unsigned swB = switchB.read();
        unsigned swC = switchC.read();
        unsigned swD = switchD.read();

        // Set the LEDs to ON
        led1 = 1;
        led2 = 1;
        led3 = 1;

        //Sound the buzzer
        buzz.playTone("F"); //Play middle F

        // Wait 0.5 seconds
        wait_us(500000);        

        // Set the LEDs to OFF
        led1 = 0;
        led2 = 0;
        led3 = 0;

        //Stop the buzzer
        buzz.rest();        

        // (a) Wait for the following sequence of events:
        //       1 switch A and B are both held down
        //       2 switch A and B are both released
        //     Once complete, turn on LED1.
        //     Use debouncing to avoid the effects of switch noise.

        // Write your solution here 
        int BTN1_PIN, BTN2_PIN;
        //Turn OFF led1
        led1 = 0;

        //wait for BOTH switches to be pressed
        do
        {
            BTN1_PIN = swA; //Read switch A
            BTN2_PIN = swB; //Read switch B
        } while ((BTN1_PIN == 0) || (BTN2_PIN == 0));
        
        //Toggle the led1
        led1 = !led1;
        led1 = 0;

        //wait for noise to settle
        wait_us (100000);

        //wait for EITHER switches to be released
        do
        {
              
            BTN1_PIN = swA; //Read button A
            BTN2_PIN = swB; //Read button B
        } while ((BTN1_PIN == 1) || (BTN2_PIN == 1));

        //Toggle the led1
        led1 = 1;
            
        //wait for noise to settle
        wait_us (100000);
        // End of solution
        
        // (b) Wait for the following sequence of events:
        //       1. Switch C is pressed and released
        //       2. Switch D to be pressed and held down
        //       3. Switch C is pressed
        //     Once complete, turn on LED2  
        //     Use debouncing to avoid the effects of switch noise.

        // Write your solution here
        int BTN3_PIN, BTN4_PIN;
        for (BTN3_PIN = 0; BTN3_PIN < 5; BTN3_PIN++)
        {
           BTN3_PIN = swC;
           BTN4_PIN = swD;
           if ((BTN3_PIN % 2 == 0) && (BTN3_PIN % 2 == 1)) // Switch C is pressed and Switch C is released
            continue;
           else if (BTN4_PIN % 2 == 0) //Switch D is pressed and held down
           {
               led2 = 0;
               continue;
           }
           else if (BTN3_PIN % 2 == 0) //Switch C is pressed 
           {
               //wait for switch C to be pressed and released and switch D to be pressed and held down and switch C to be pressed
               led2 = 1;

               //wait for noise to settle
               wait_us(100000);
            }
           else {
               led2 = !led2; //Toggle the led2
               
               wait_us(100000);

              //wait for noise to settle
              
            }

        }
        // End of solution

        // (c) Wait for the following switch sequence: 
        //       1. Switch A is pressed and released
        //       2. Switch C is pressed and released 
        //       3. Switch A is pressed and released
        //       4. Switch D is pressed and released
        //       5. Switch B is pressed and released
        //     If the correct sequence is entered, turn on LED3. 
        //     If at ANY point the sequence is incorrect, sound the buzzer for 0.5s and go back to the start
        //     Use debouncing to avoid the effects of switch noise.

        // Write your solution here

        if (swA == 0) 
        {
            wait_us(100000); //Debounce delay
            if (swC == 0) 
            {
                wait_us(100000); //Debounce delay
                if (swA == 1) 
                {
                    wait_us(100000); //Debounce delay
                    if (swD == 0) 
                    {
                        wait_us(100000); //Debounce delay
                        if (swB == 0) 
                        {
                            //Correct sequence
                            led3 = 1; //Turn on led3
                        }
                    }
                }
            }
        } else 
        {
            //Sound the buzzer
            buzz.playTone("F"); //Play middle F

            // Wait 0.5 seconds
            wait_us(500000);
        }
        // End of solution


        //Pause
        while(1);
    }
}
