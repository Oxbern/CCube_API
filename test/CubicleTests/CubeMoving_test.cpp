#include "Controller.h"
// #include <iostream>

#define TIME ((const struct timespec[]){{0, 100000000L}})

int main(int argc, char** argv) {
    
    Controller c;
    c.connectDevice(1);
    
    //c.pilot();
    c.available();
    
    c.disconnectDevice();
    return 0;
}

