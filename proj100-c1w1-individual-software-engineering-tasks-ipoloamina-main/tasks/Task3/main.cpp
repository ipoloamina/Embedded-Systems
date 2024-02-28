/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <chrono>
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

// LCD Display
LCD_16X2_DISPLAY display;
DigitalOut lcdBack(LCD_BKL_PIN,1);

int main()
{
    // ******************************************************
    // STUDENTS NOTE - you must set the Baud rate to 115200 *
    // ******************************************************
    hideCursor();       //Turn off the cursor in the terminal to avoid flickering 
    clearTerminal();    //Clear the terminal

    //Update LCD display
    display.cls();
    display.printf("TASK 3");

    //Wat for user
    printf("TASK 3 - press the blue button\n");
    while (blueButton == 0);    //Wait for button press

    clearTerminal();    //Clear the terminal

    //Create a timer
    Timer printTimer;
    Timer plotterTimer;
    printTimer.start();
    plotterTimer.start();

    //Create LEDMatrix 
    LEDMatrix grid;
    uint8_t x=7, y=3;

    //Test - plot in each corner (x5)
    int xx[] = {0, 15, 15, 0};
    int yy[] = {0, 0,  7,  7};
    for (uint8_t c = 0; c<5; c++) {
        for (uint8_t n=0; n<4; n++) {
            grid.xyplot(xx[n], yy[n]);
            wait_us(125000);
        }
    }

    //Very fast polling loop
    while (true)
    {
        // Read all switches without blocking
        unsigned swA = switchA.read();
        unsigned swB = switchB.read();
        unsigned swC = switchC.read();
        unsigned swD = switchD.read();

        //Read timers without blocking
        microseconds tPrint   = printTimer.elapsed_time();      //Time in uS
        microseconds tPlotter = plotterTimer.elapsed_time();    //Time in uS

        // Update plotter fast enough to avoid flicker
        if (tPlotter >= 100ms) {
            //Reset timer to zero
            plotterTimer.reset();

            //Update the point on the grid
            grid.xyplot(x, y);  //16 cols, 8 rows       
        }
        
        // Update serial terminal periodically
        if (tPrint >= 250ms) {
            //Reset timer to zero
            printTimer.reset();

            // Toggle the LEDs
            led1 = !led1;
            led2 = !led2;
            led3 = !led3;       
            
            //Set terminal cursor to the top left
            homeCursor();   

            //Display button state (note: characters are sent at 11500 bits per second, so this is relatively slow)
            printf("(x,y)=(%u,%u)", x,y);
        }

        // TASK
        // (a) Use the buttons A,B,C and D to move the dot on the matrix 
        //     A - left
        //     C - right
        //     B - down
        //     D - up
        //     Each time one of the buttons is pressed, the dot shall move one position. 
        //     The button has to be released before it can be used again.
        //
        // (b) Switches should be debounced without noticeably affecting the responsiveness
        //
        // (c) It shall be possible to press more than one button at a time 
        //     (e.g. up and right to move diagonally)
        //
        // (d) It shall not be possible to move beyond the end of the matrix display
        //
        // (e) The LED on the matrix shall also work in one of 2 modes. Solid or flashing.
        //     Pressing and releasing the blue button should switch between solid and flashing.
        //     Again, take steps to prevent switch bounce.
        //
        // (f) The LCD matrix should display the coordinates each time it changes. 
        //     Only update the display when there is a change.
    }
}
