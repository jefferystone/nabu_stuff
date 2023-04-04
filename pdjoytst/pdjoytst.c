#define DISABLE_HCCA_RX_INT
#define DISABLE_CURSOR

#define DISABLE_VDP          // If you dssable VDP in NABU-LIB, the program crashes and CP/M warm boots.
// #define DISABLE_KEYBOARD_INT // The NABU-LIB functions for the joystick depend on the KBD interrupts.

#include <stdio.h>
#include "NABU-LIB.h"

uint8_t status0, lastStatus0, status1, lastStatus1 = 0; //Record the status of the joystick in these vars.

uint8_t main(void) {

    /*The NABU Keyboard Controller only reports changes to the joystick.
    * NABU-LIB tracks these in a global variable which allows us to poll the
    * Joystick.  It's possible that Marduk and Ishkur CP/M do not manage the
    * joystick input in the same way as DJ's CloudCP/M BIOS.
    * 
    * To do this without NABU-LIB, you will need to write code to handle the
    * Keyboard interrupt yourself.
    */

    ;initNABULib();
    
    // Here I am basically tracking the status of the joystick as reported by
    // NABU-LIB and printing a message to the screen if it changes.
    printf("Joystick Test Program:\n");
    printf("Move the Joystick and press the button.\n");
    printf("Hit Q to quit.\n\n");

    while(1) {
        status0 = getJoyStatus(0);           
        if (status0 != lastStatus0) {
            if(status0 & Joy_Left) {
                printf("J0 - LEFT\n");
            } else if (status0 & Joy_Right) {
                printf("J0 - RIGHT\n");
            } else if (status0 & Joy_Up) {
                printf("J0 - UP\n");
            } else if (status0 & Joy_Down) {
                printf("J0 - DOWN\n");
            } else if (status0 & Joy_Button) {
                printf("J0 - BUTTON\n");
            } else {
                printf("J0 - RESET\n");
            }

            lastStatus0 = status0;
        }
        
        status1 = getJoyStatus(1);
        if (status1 != lastStatus1) {
            if(status1 & Joy_Left) {
                printf("J1 - LEFT\n");
            } else if (status1 & Joy_Right) {
                printf("J1 - RIGHT\n");
            } else if (status1 & Joy_Up) {
                printf("J1 - UP\n");
            } else if (status1 & Joy_Down) {
                printf("J1 - DOWN\n");
            } else if (status1 & Joy_Button) {
                printf("J1 - BUTTON\n");
            } else {
                printf("J1 - RESET\n");
            }

            lastStatus1 = status1;
        }

        if (isKeyPressed()) {
            uint8_t key = getChar();
            if (key == 'q' || key == 'Q') {
                printf("Exiting...\n");
                break;
            }
        }

    }
    return 0;
}
