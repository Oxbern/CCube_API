#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "Controller.h"

int main(int argc, char* argv[])
{    
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
    dc->on(4,4,4);
    dc->on(3,4,4);
    dc->on(4,3,4);
    dc->on(5,4,4);
    dc->on(4,5,4);
    dc->on(3,3,4);
    dc->on(5,5,4);

    std::cout << "DeviceShape on (4,4,4)" << std::endl;
    
    c.display();
    std::cout << "DeviceShape displayed" << std::endl;

    c.disconnectDevice();
    return 0;
}

/*

  echo /dev/bus/usb/`udevadm info --name=/dev/ttyUSB0 --attribute-walk | sed -n 's/\s*ATTRS{\(\(devnum\)\|\(busnum\)\)}==\"\([^\"]\+\)\"/\4/p' | head -n 2 | awk '{$1 = sprintf("%03d", $1); print}'` | tr " " "/"

*/
