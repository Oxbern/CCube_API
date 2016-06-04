#include "Ball.h"
#include "DeviceShape.h"


int main(int argc, char** argv) {
    Ball b;
    
    Point p(1,2,3);
    b.setOrigin(p);
    
    //for (int i = 0; i < 100; i++)
        //b.action();
    
    DeviceShape ds;
    ds.copyLedStatus(b);
        
    return 0;
}

