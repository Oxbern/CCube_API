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
    Controller c;
    
    if(argc == 1){
        if (!c.connectDevice(1)) {
            std::cerr << "Connection established" << std::endl;
            return EXIT_FAILURE;
        }
    }
    else{
        c.connectDevice(argv[1]);
    }
    
    if (c.getConnectedDevice() != NULL)
        std::cout << "Connection to device " << c.getConnectedDevice()->getPort() <<" successful" << std::endl;
    
    //Switch on some LEDs
    if (!c.getConnectedDevice()->on(0, 0, 0)
        || !c.getConnectedDevice()->on(4, 4, 4)
        || !c.getConnectedDevice()->on(8, 8, 8)) {
        std::cout << "Unable to turn on the LEDs" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Leds turned on" << std::endl;
    
    
    if (!c.display()) {
        std::cout << "Unable to display" << std::endl;
             return EXIT_FAILURE;
    }
    std::cout << "Leds displayed" << std::endl;
    
    
    if (c.disconnectDevice()) {
        std::cout << "Disconnection to device successful" << std::endl;
        std::cout << "TEST PASSED " << std::endl;
        return EXIT_SUCCESS;
    } else {
        std::cout << "Unable to disconnect " << std::endl;
    }
    
    
    std::cout << "Unable to connect" << std::endl;
    
    return EXIT_FAILURE;
}
