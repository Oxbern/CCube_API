#include "Ball.h"
#include "Controller.h"
// #include <iostream>

#define TIME ((const struct timespec[]){{0, 500000000L}})

int main(int argc, char** argv) {
    
    Controller c;
    c.connectDevice(1);
    
    Ball b;
    
    c.getConnectedDevice()->setLedStatus(b);

    for (int i = 0; i < 100; i++) {
        b.action();
        c.getConnectedDevice()->setLedStatus(b);
        
        c.display();
        //nanosleep(TIME, NULL);
        sleep(2);
    }
    c.disconnectDevice();
    return 0;
}

