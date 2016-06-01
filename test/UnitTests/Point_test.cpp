#include <Point.h>

int main(int argc, char** argv) {

    /* Initialization */
    Point p1(0, 0, 0);
    Point p2(1, 2, 3);
    Point p3;


    if (p1.getX() != 0 || p1.getY() != 0 || p1.getZ() != 0
            || p2.getX() != 1 || p2.getY() != 2 || p2.getZ() != 3
            || p3.getX() != 0 || p3.getY() != 0 || p3.getZ() != 0)
        perror("Test 1 point FAILED");


    /* operator == */
    if (p1 == p2)
        perror("Test 2 point FAILED");

    /* operator = */
    p1 = p2;
    if (!(p1 == p2))
        perror("Test 3 point FAILED");

    /* operator + */
    p3 = p1 + p2;
    if (p3.getX() != 2 || p3.getY() != 4 || p3.getZ() != 6)
        perror("Test 4 point FAILED");

    /* incr / decr */
    p3.setX(0);
    p3.setY(0);
    p3.setZ(0);
    if (p3.getX() != 0 || p3.getY() != 0 || p3.getZ() != 0)
        perror("Test 5 point FAILED");

    p3.incrX();
    if (p3.getX() != 1)
        perror("Test 6 point FAILED");
    
    p3.decrX();
    if (p3.getX() != 0)
        perror("Test 7 point FAILED");
    
    p3.incrY();
    if (p3.getY() != 1)
        perror("Test 6 point FAILED");
    
    p3.decrY();
    if (p3.getY() != 0)
        perror("Test 7 point FAILED");

    p3.incrZ();
    if (p3.getZ() != 1)
        perror("Test 8 point FAILED");
    
    p3.decrZ();
    if (p3.getZ() != 0)
        perror("Test 9 point FAILED");
    
    std::cout << "Test point : PASSED " << std::endl;

    return 0;
}

