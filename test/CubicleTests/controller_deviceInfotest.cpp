#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

#include "Controller.h"

/**
 * Simple test to switch on some LEDs using methods of the API
 */
int main(int argc, char *argv[])
{
    Controller c;

    if (c.connectDevice(1)){
        std::cout << "Connection to device successful" << std::endl;

        //Switch on some LEDs
        // if (!c.on(0, 0, 0)
        //     || !c.on(4, 4, 4)
        //     || !c.on(8, 8, 8)) {
        //     std::cout << "Unable to turn on the LEDs" << std::endl;
        //     return EXIT_FAILURE;
        // }


        // if (!c.display()) {
        //      std::cout << "Unable to display" << std::endl;
        //      return EXIT_FAILURE;
        // }

        uint8_t *info = c.getDeviceInfo();

        std::cout << "size x : " << (int)info[0] << std::endl;
        std::cout << "size y : " << (int)info[1] << std::endl;
        std::cout << "size z : " << (int)info[2] << std::endl;        
        
        
        if (c.disconnectDevice()) {
            std::cout << "Disconnection from device successful" << std::endl;
            std::cout << "TEST PASSED " << std::endl;
            return EXIT_SUCCESS;
        } else {
            std::cout << "Unable to disconnect " << std::endl;
        }

        delete [] info;
    }

    std::cout << "Unable to connect" << std::endl;

    return EXIT_FAILURE;
}
