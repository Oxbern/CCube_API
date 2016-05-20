#ifndef TEST_DISPLAY_C
#define TEST_DISPLAY_C

#include "test_display.h"
#define M_PI 3.14159265359

void test_ok(cube *cube){

    on(4, 3, 6, cube);
    on(4, 4, 5, cube);
    on(4, 2, 5, cube);
    on(4, 1, 4, cube);
    on(4, 5, 4, cube);
    on(4, 4, 3, cube);
    on(4, 2, 3, cube);
    on(4, 3, 2, cube);
            
    // The K
    on(4, 6, 6, cube);
    on(4, 6, 5, cube);
    on(4, 6, 4, cube);
    on(4, 6, 3, cube);
    on(4, 6, 2, cube);
    on(4, 8, 6, cube);
    on(4, 7, 5, cube);
    on(4, 7, 3, cube);
    on(4, 8, 2, cube);
}

void test_sphere(cube *cube) {
    uint16_t r,theta,phi;
    for (r = 0; r < 4; r++) 
        for (theta = 0; theta < 8; theta++)
            for (phi = 0; phi < 4; phi++) {
                uint16_t x, y, z;
                x = floor(r * sin(2*theta*M_PI/8) * cos(2*phi*M_PI/8)) + 4;
                y = floor(r * sin(2*theta*M_PI/8) * sin(2*phi*M_PI/8)) + 4;
                z = floor(r * cos(2*theta*M_PI/8)) + 4;

                on(x, y, z, cube);
            }
}

#endif
