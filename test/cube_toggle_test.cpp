#include <cstdint>
#include <stdio.h>
#include <cstdlib>

#include "Cube.h"

/**
    File to test the behaviour of the off(..) function 
 */

int main(int argc, char *argv[]) {

    uint8_t led;

/*******************************************************************
                    TEST 1 : one led in two switched on
********************************************************************/
    uint16_t res_expected[10][10];
    for (int z = 0; z < 10; z++) {
        for (int y = 0; y < 10; y++) {
            if (z == 9) {
                    res_expected[z][y] = (uint16_t)0x0;
            } else {
                if (y==9)     
                    res_expected[z][y] = (uint16_t)(1 << z);
                else
                    res_expected[z][y] = 0b101010101;
            }
        }
    }

    Cube cube1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                if (k % 2 == 1)
                    cube1.on(k, j, i);
            }
        }
    }

    //Test toggle function
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                    cube1.toggle(k, j, i);
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                led = (uint8_t)((res_expected[i][j] >> k) & 0x1);

                if (!(led == cube1.getLedBuffer(k, j, i))) {
                    perror("Test 1 : FAILED");
                    return EXIT_FAILURE;
                }
            }
        }
    }
    printf("Test 1 : PASSED\n");

/*******************************************************************
                    TEST 2 : one led in two switched on
********************************************************************/
    for (int z = 0; z < 10; z++) {
        for (int y = 0; y < 10; y++) {
            if (z == 9) {
                    res_expected[z][y] = (uint16_t)0x0;
            } else {
                if (y==9)     
                    res_expected[z][y] = (uint16_t)(1 << z);
                else
                    res_expected[z][y] = 0b111111111;
            }
        }
    }

    Cube cube2;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                cube2.toggle(k, j, i);
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                led = (uint8_t)((res_expected[i][j] >> k) & 0x1);

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