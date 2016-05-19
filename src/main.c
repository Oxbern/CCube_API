#include <stdio.h>
#include <stdlib.h>

#include "cube.h"


int main(int argc, char *argv[]) {

    cube *cube = new_cube();

    display("nothing", cube);

    free(cube);
    
    return 0;
}
