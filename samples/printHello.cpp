#include "Controller.h"

int main(int argc, char** argv)
{
    std::string hello = "hello";
    
    Controller c;

    if (c.connectDevice(1)){
        std::cout << "Connection to device successful" << std::endl;

        if (!c.printMsgScreen(hello, 60)) {
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
    c.display();

    std::cout << "Unable to connect" << std::endl;

    return EXIT_FAILURE;

}
