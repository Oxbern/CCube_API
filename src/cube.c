#include <stdint.h>
#include <stdlib.h>

#include "cube.h"

cube *new_cube() {
    cube *newCube = malloc(sizeof(cube));

    for (int i = 0; i <= 10; ++i) {
	for (int j = 0; j < 10; ++j)
	    newCube->led_buffer[i][j] = 0b0000000000;
	newCube->led_buffer[i][10] = 1 << i;
    }
    newCube->led_buffer[10][10] = 0b0000000000;

    return newCube;
}

void display() {
    
}


