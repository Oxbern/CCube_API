#include <stdio.h>
#include <stdlib.h>

#include "cube.h"


int main(int argc, char *argv[]) {

    cube *cube = new_cube();

    display("/dev/ttyAMC0", cube);

    free(cube);
    
    return 0;
}
