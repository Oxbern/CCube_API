#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "Controller.h"


int main(int argc, char* argv[])
{    
    // Create an instance of Controller, main interface for the API
    Controller c;

    // Connect the controller to a device which is physically connected via USB
    c.connectDevice();

    // Switch on a led on the current connected device;
    //c->on(4,4,4);
    return 0;
}
