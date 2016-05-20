#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cube.h"


int main(int argc, char *argv[]) {

    cube *cube = new_cube();

    on(4, 3, 6, cube);
    on(4, 4, 5, cube);
    on(4, 2, 5, cube);
    on(4, 1, 4, cube);
    on(4, 5, 4, cube);
    on(4, 4, 3, cube);
    on(4, 2, 3, cube);
    on(4, 3, 2, cube);
            
    // The K
    on(4, 6, 6, cube);
    on(4, 6, 5, cube);
    on(4, 6, 4, cube);
    on(4, 6, 3, cube);
    on(4, 6, 2, cube);
    on(4, 8, 6, cube);
    on(4, 7, 5, cube);
    on(4, 7, 3, cube);
    on(4, 8, 2, cube);

    display("/dev/ttyACM0", cube);
    sleep(2);
    
    display("/dev/ttyACM0", new_cube());
    
    free(cube);
    
    return 0;
}
