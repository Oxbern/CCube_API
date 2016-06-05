#include "Ball.h"
#include "Controller.h"
// #include <iostream>

#define TIME ((const struct timespec[]){{0, 100000000L}})

int main(int argc, char** argv) {
    
    Controller c;
    c.connectDevice(1);
    
    Ball b;
    
    c.getConnectedDevice()->setLedStatus(b);

    for (int i = 0; i < 1000; i++) {
        b.action();
        c.getConnectedDevice()->setLedStatus(b);
        
        c.getConnectedDevice()->getcurrentConfig()->print(std::cout);
        c.display();
        nanosleep(TIME, NULL);

    }
        
    c.disconnectDevice();
    return 0;
}

