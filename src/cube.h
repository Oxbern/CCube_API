
#ifndef CUBE_H
#define CUBE_H

#include <stdint.h>

#define BUFFER_MAX_INDEX 64

typedef struct _cube {
    uint16_t led_buffer[10][10];
} cube;


cube *new_cube();

void on(int x, int y, int z, cube *cube);
void off(int x, int y, int z, cube *cube);
void toggle(int x, int y, int z, cube *cube);
void display(char * dev, cube *cube);

#endif 
