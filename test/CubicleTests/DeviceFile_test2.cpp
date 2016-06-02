#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

#include "Device.h"
#include "Controller.h"

/**
 * Simple test to switch on some LEDs using methods of the API
 */
int main(int argc, char *argv[])
{
    std::string port = "/dev/ttyACM0";
    Device dev(port, 1);
    Controller c;
    c.connectDevice(&dev);


    if (dev.connect()){
        std::cout << "Connection to " << port << " device successful" << std::endl;

        //Switch on some LEDs
        if (!dev.on(0, 0, 0) || !dev.on(4, 4, 4) || !dev.on(8, 8, 8)) {
            std::cout << "Unable to turn on the LEDs" << std::endl;
            return EXIT_FAILURE;
        }


        if (!c.displayDevice()) {
             std::cout << "Unable to display" << std::endl;
             return EXIT_FAILURE;
        }

        if (c.disconnectDevice()) {
            std::cout << "Disconnection to " << port << " device successful" << std::endl;
            std::cout << "TEST PASSED " << std::endl;
            return EXIT_SUCCESS;
        } else {
            std::cout << "Unable to disconnect " << port << std::endl;
        }
    }

    std::cout << "Unable to connect" << std::endl;
    return EXIT_FAILURE;
}
