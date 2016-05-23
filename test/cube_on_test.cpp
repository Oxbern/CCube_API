#include <cstdint>
#include <stdio.h>
#include <cstdlib>

#include "Cube.h"

/**
    File to test the behaviour of the on(..) function 
 */

int main(int argc, char *argv[]) {

    uint8_t led;

/*******************************************************************
                    TEST 1 : all leds switched off
********************************************************************/    
    //LedBuffer 1 : all led switched off
    uint16_t ledBuffer1[10][10];
    for (int z = 0; z < 10; z++) {
        for (int y = 0; y < 10; y++) {
            if (z == 9) {
                    ledBuffer1[z][y] = (uint16_t)0x0;
            } else {
                if (y==9)     
                    ledBuffer1[z][y] = (uint16_t)(1 << z);
                else
                    ledBuffer1[z][y] = (uint16_t)0;
            }
        }
    }

    Cube cube1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                led = (uint8_t)((ledBuffer1[i][j] >> k) & 0x1);

                if (!(led == cube1.getLedBuffer(k, j, i))) {
                    perror("Test 1 : FAILED");
                    return EXIT_FAILURE;
                }
            }
        }
    }
    printf("Test 1 : PASSED\n");


/*******************************************************************
                    TEST 2 : all leds switched on
********************************************************************/
    //LedBuffer 1 : all led switched on
    uint16_t ledBuffer2[10][10];
    for (int z = 0; z < 10; z++) {
        for (int y = 0; y < 10; y++) {
            if (z == 9) {
                    ledBuffer2[z][y] = (uint16_t)0x0;
            } else {
                if (y==9)     
                    ledBuffer2[z][y] = (uint16_t)(1 << z);
                else
                    ledBuffer2[z][y] = (uint16_t)0b0000000111111111;
            }
        }
    }


    Cube cube2;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++)
                cube2.on(k, j, i);
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                led = (uint8_t)((ledBuffer2[i][j] >> k) & 0x1);

                if (!(led == cube2.getLedBuffer(k, j, i))) {
                    perror("Test 2 : FAILED");
                    return EXIT_FAILURE;
                }
            }
        }
    }
    printf("Test 2 : PASSED\n");


    return EXIT_SUCCESS;
}