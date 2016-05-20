#ifndef POINT_H
#define POINT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include "cube.h"

struct Point {
    uint8_t x;
    uint8_t y;
    uint8_t z;
} typedef Point;

Point *new_point(uint8_t x,uint8_t y, uint8_t z);
bool handle_out_of_bounds(uint8_t x,uint8_t y, uint8_t z);
#endif
