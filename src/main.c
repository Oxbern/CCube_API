#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cube.h"
#include "test_display.h"

int main(int argc, char *argv[]) {

    cube *cube = new_cube();

    //test_ok(cube);
    test_sphere(cube);
    
    display("/dev/ttyACM0", cube);
    sleep(20);
    
    display("/dev/ttyACM0", new_cube());
    
    free(cube);
    
    return 0;
}
