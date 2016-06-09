#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

#include "Controller.h"

/**
 * Simple test to get the device's ID
 */
int main(int argc, char *argv[])
{
    Controller c;

    if (c.connectDevice(1)){
        std::cout << "Connection to device successful" << std::endl;

        uint8_t id = c.getDeviceID();

        std::cout << "ID : " << (int)id << std::endl;        
        
        
        if (c.disconnectDevice()) {
            std::cout << "Disconnection from device successful" << std::endl;
            std::cout << "TEST PASSED " << std::endl;
            return EXIT_SUCCESS;
        } else {
            std::cout << "Unable to disconnect " << std::endl;
        }

    }

    std::cout << "Unable to connect" << std::endl;

    return EXIT_FAILURE;
}
