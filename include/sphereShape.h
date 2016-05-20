#ifndef SPHERESHAPE_H
#define SPHERESHAPE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include "cube.h"
#include "Point.h"
#include "test_display.h"

cube *test_sphere(Point origine, uint8_t r,bool full);
void sphere(Point origine,uint8_t r,uint8_t n, cube *cube);

#endif
