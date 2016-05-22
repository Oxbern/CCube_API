#ifndef TEST_DISPLAY_H
#define TEST_DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include "cube.h"
#define M_PI 3.14159265359


void printcmd();

bool handle_out_of_bounds(uint8_t x,uint8_t y, uint8_t z);

#endif 