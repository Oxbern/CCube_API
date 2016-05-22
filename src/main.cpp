#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Cube.h"
#include "Shape.h"

int main(int argc, char *argv[]) {
    
    Cube cube;
    cube.on(3,2,1);
    cube.off();

     // Shape s(cube);
     // s.on();
     // s.addPoint(Point(3,3,3));
     // s.describe();
     // s.clearShape();
     // s.describe();
     // s.loadOkShape();
     // s.describe();

    return 0;
}


