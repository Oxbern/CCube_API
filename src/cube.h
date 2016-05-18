#ifndef CUBE_H
#define CUBE_H

#include <stdint.h>

#define BUFFER_MAX_INDEX 64

typedef struct _cube {
    uint16_t led_buffer[10][10];
} cube;


cube *new_cube();

void display(char * dev, cube *cube);

#endif 
