#include "Point.h"


Point *new_point(uint8_t x,uint8_t y, uint8_t z){
    Point *p = malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    p->z = z;
    return p;
}


bool handle_out_of_bounds(uint8_t x,uint8_t y, uint8_t z){
    if (x < 0 || x > 8)
	return true;
    if (y < 0 || y > 8)
	return true;
    if (z < 0 || z > 8)
	return true;
    return false;
}



