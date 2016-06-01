#include "Ball.h"


int main(int argc, char** argv) {
    Ball b;
    
    Point p(1,2,3);
    b.setOrigin(p);
    
    for (int i = 0; i < 100; i++)
        b.action();
    
    return 0;
}

