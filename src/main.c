#include <stdio.h>
#include <stdlib.h>

#include "cube.h"


int main(int argc, char *argv[]) {

    cube *cube = new_cube();

    on(4, 4, 4, cube);

    display("/dev/ttyACM0", cube);

    free(cube);
    
    return 0;
}
