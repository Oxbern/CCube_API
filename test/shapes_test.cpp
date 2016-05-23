#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <ncurses.h>

#include "Point.h"
#include "Vec3.h"
#include "Cube.h"
#include "Shape.h"

int main(int argc, char *argv[]) {
    
    Cube cube;

    Shape sphere(cube);
    int r = 3;
    Point p(3,3,3);
    sphere.loadSphereShape(r,p,true);
    sphere.on();
}
