#include "sphereShape.h"


void sphere(Point origine, uint8_t r,uint8_t n,cube *cube){
    for (uint8_t theta = 0; theta < n; theta++)
	for (uint8_t phi = 0; phi < n; phi++) {
	    uint16_t x, y, z;
                x = round(r * sin(2*theta*M_PI/n) * cos(2*phi*M_PI/n) + origine.x);
                y = round(r * sin(2*theta*M_PI/n) * sin(2*phi*M_PI/n) + origine.y);
		z = round(r * cos(2*theta*M_PI/n) + origine.z);
		if (handle_out_of_bounds(x,y,z))
		    perror("Out of bounds us");
                on(x, y, z, cube);
	}
}

cube *test_sphere(Point origine, uint8_t radius,bool full) {
    cube *cube = new_cube();
    uint8_t theta,phi;
    uint16_t n = 30;
    uint8_t r;
    if (!full){
	r = radius;
	sphere(origine,r,n,cube);
    }
    else{
	for (double r = 0; r <= radius; r+=0.5)
	    sphere(origine,r,n,cube);
    }
    return cube;
}


