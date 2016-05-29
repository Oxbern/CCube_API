#include <iostream>
#include <fstream>

#include "Device.h"

/**
 * Simple test to switch on some LEDs using methods of the API
 */
int main(int argc, char *argv[]) {

    std::string port = "/dev/stdout";
    Device dev(port, 1);

    if (dev.connect()){
        std::cout << "Connection to " << port << " device successful" << std::endl;

        //Switch on some LEDs
        if (!dev.on(0, 0, 0) || !dev.on(4, 4, 4) || !dev.on(8, 8, 8)) {
            std::cout << "TEST FAILED " << std::endl;
            return EXIT_FAILURE;
        }

        if (!dev.display()) {
            std::cout << "TEST FAILED " << std::endl;
            return EXIT_FAILURE;
        }

        if (dev.disconnect()) {
            std::cout << "Disconnection to " << port << " device successful" << std::endl;
            std::cout << "TEST PASSED " << std::endl;
            return EXIT_SUCCESS;
        } else {
            std::cout << "Unable to disconnect " << port << std::endl;
        }
    }

    std::cout << "TEST FAILED " << std::endl;
    return EXIT_FAILURE;
}