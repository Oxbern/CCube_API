#include "Controller.h"


int main(int argc, char* argv[]) 
{

    // Keep this process running until Enter is pressed
    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();
    
    // Create an instance of Controller, main interface for the API
    Controller c;

    // Connect the controller to a device which is physically connected via USB
    // with its ID (Here 1).
    c.connectDevice(1);

    // Switch on a led on the current connected device
    int x = 0, y = 0, z = 0;
    c.on(x,y,z);

    // Update the display, and physically switch on the light
    c.displayDevice();
    
    //Don't forget to disconnect
    c.disconnectDevice();
    return 0;
}
