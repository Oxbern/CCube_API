#include "cubeShape.h"

cube *test_cube(Point origine,uint8_t r,bool full){
    cube *cube = new_cube();
    uint16_t x, y, z;
    if (!full)
	//quadrilatere(p1,p2,p3,p4);
	x = 0;
    else {
	for (uint8_t i = 0; i<=r;i++){
	    for (uint8_t j = 0; j<=r;j++){
		for (uint8_t k = 0; k<=r;k++){
		    x = origine.x+i;
		    y = origine.y+j;
		    z = origine.z+k;
		    if (handle_out_of_bounds(x,y,z))
			perror("Out of bounds us");
		    
		    on(x,y,z,cube);
		}
	    }
	}
    }
	return cube;
}
