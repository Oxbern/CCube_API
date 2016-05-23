#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <ncurses.h>
#include <cstring>

#include "Point.h"
#include "Vec3.h"
#include "Cube.h"
#include "Shape.h"

int main(int argc, char *argv[]) {
    
    Cube cube;

    // for (uint8_t i = 0 ;i<9;i++)
    // 	cube.on(i,3,3);
    //cube.on(1,1,1);
    char const *dev = "/dev/ttyACM0";
    char const *loc = "local";
    //cube.display(dev );

    Shape sphere(cube);
    int r = 3;
    Point p(3,3,3);
    sphere.loadSphereShape(r,p,true);
    sphere.on();
    sphere.display("/dev/ttyACM0");
}
