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
    int r = 2;
    Point p(3,3,3);
    sphere.loadSphereShape(r,p,false);
    sphere.display("/dev/ttyACM0");
    sleep(2);

    sphere.loadSphereShape(r,p,true);
    sphere.display(dev);
    sleep(2);

    Vec3 v(0,3,0);
    sphere.translateShape(v);
    sphere.display(dev);
    sleep(2);

    Point ori(0,0,1);
    sphere.loadCircleShape(r,p,ori,false);
    sphere.display(dev);
    sleep(2);

    sphere.loadCircleShape(r,p,ori,true);
    sphere.display(dev);
    sleep(2);

    sphere.loadCubeShape(r,p,true);
    sphere.display(dev);
    sleep(2);

    sphere.loadCubeShape(r,p,false);
    sphere.display(dev);
    sleep(2);

    sphere.loadOkShape();
    sphere.display(dev);
    sleep(2);
}
