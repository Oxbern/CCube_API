#include "Ball.h"
#include "Controller.h"
// #include <iostream>

#define TIME ((const struct timespec[]){{0, 100000000L}})

int main(int argc, char** argv) {
    Controller c;
    Device *chosen;

    if (c.listAllDevices()){
        
        int choice = 0;
        
        std::cout << "Enter the device's ID you want to connect : " << std::endl;
        std::cin >> choice;
        
        
        std::list<Device*>::iterator iter ;
        std::list<Device*> listDevice = c.getListDevices();
        for(iter = listDevice.begin() ; (iter != listDevice.end()) ;iter++){
            if (choice == (*iter)->getID())
                chosen = *iter;
        }
        
        std::cout << "You choose Device " << (int) chosen->getID() << std::endl;
        
        if (c.connectDevice(chosen)){
            
            std::cout << "You are connected to " << c.getConnectedDevice()->getPort()  << std::endl;
        }
    }
    Device *dc = c.getConnectedDevice();
   
    Ball b;
    
    dc->setLedStatus(b);

    for (int i = 0; i < 1000; i++) {
        b.action();
        dc->setLedStatus(b);
        c.displayDevice();
        nanosleep(TIME, NULL);

    }
        
        
    // std::cout << "DeviceShape on (4,4,4)" << std::endl;
    c.displayDevice();
    // std::cout << "DeviceShape displayed" << std::endl;

    c.disconnectDevice();
    return 0;
}

