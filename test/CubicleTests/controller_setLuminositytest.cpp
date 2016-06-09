#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

#include "Controller.h"

/**
 * Simple test to set the luminosity
 */
int main(int argc, char *argv[])
{
    Controller c;

    if (c.connectDevice(1)){
        std::cout << "Connection to device successful" << std::endl;

        // Sets the luminosity
        if (!c.setLuminosity(1)) {
             std::cout << "Unable to set the luminosity" << std::endl;
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
