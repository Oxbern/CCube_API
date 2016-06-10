#include "Controller.h"

int main(int argc, char** argv)
{
    Controller c;
    
    // Read the parameter
    if (argc < 2) {
        std::cout << "Usage : "<< argv[0] << " absolute path to CCube_Firmware.bin \n";
        return EXIT_FAILURE;
    }

    if (c.connectDevice(1)){
        std::cout << "Connection to device successful" << std::endl;

        if (!c.updateFirmware(argv[1])) {
            std::cout << "Unable to update firmware" << std::endl;
            return EXIT_FAILURE;
        }
        else {
            std::cout << "[TEST PASSED]" << std::endl;
            return EXIT_SUCCESS;
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
