#include "Controller.h"


int main(int argc, char* argv[])
{    
    // Create an instance of Controller, main interface for the API
    Controller c;

    // Connect the controller to a device which is physically connected via USB
    c.connectDevice(1);
    std::cout << "Device connected" << std::endl;
    //c.disconnectDevice();

    // Or connect directly to a known device with its port and give it and id
    // int myDeviceId = 0;
    // myDeviceId = c.getListDevices().size() + 1;
    // Device *d = new Device("/dev/ttyACM0",10);
    // if(c.connectDevice(d))
    //     std::cout << "Connected" << std::endl;
    
    // Switch on a led on the current connected device
    int x = 0,y = 0,z = 0;
    c.on(x,y,z);
    std::cout << "Led on" << std::endl;

    // Display led status on the current connected device.
    while(1){
        c.displayDevice();
        std::cout<<"DISPLAYED, move?"<<std::endl;
        int choice = 0;
        std::cin >> choice;
        switch(choice){
        case 1:
            x++;
            break;
        case 2:
            x--;
            break;
        case 3:
            y++;
            break;
        case 4:
            y--;
            break;
        case 5:
            z++;
            break;
        case 6:
            z--;
            break;
            
        }
        c.on(x,y,z);
    }
    //Don't forget to disconnect
    c.disconnectDevice();
    return 0;
}
