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

        //Switches on some LEDs
        if (!c.on(0, 0, 0)
            || !c.on(4, 3, 3)
            || !c.on(8, 5, 6)) {
            std::cout << "Unable to turn on the LEDs" << std::endl;
            return EXIT_FAILURE;
        }

        if (!c.display()) {
             std::cout << "Unable to display" << std::endl;
             return EXIT_FAILURE;
        }

        //Switches off one LED
        if (!c.off(0, 0, 0)) {
            std::cout << "Unable to turn off the LED" << std::endl;
            return EXIT_FAILURE;
        }

        if (!c.display()) {
             std::cout << "Unable to display" << std::endl;
             return EXIT_FAILURE;
        }
        
        //Switches off the cube
        if (!c.off()) {
            std::cout << "Unable to turn off the cube" << std::endl;
            return EXIT_FAILURE;            
        }

        if (!c.display()) {
             std::cout << "Unable to display" << std::endl;
             return EXIT_FAILURE;
        }

        if (c.disconnectDevice()) {
            std::cout << "Disconnection to device successful" << std::endl;
            std::cout << "TEST PASSED " << std::endl;
            return EXIT_SUCCESS;
        } else {
            std::cout << "Unable to disconnect " << std::endl;
        }
    }

    std::cout << "Unable to connect" << std::endl;

    return EXIT_FAILURE;
}
