#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Cube.h"

int main(int argc, char *argv[]) {
    
    Cube cube;
    cube.on(3,2,1);
    cube.off();

    return 0;
}


