#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "Controller.h"


int main(int argc, char* argv[]) {
    
    Controller c;
    c.listAllDevices();

    int choice = 0;
    
    std::cout << "Enter the device's ID you want to connect : " << std::endl;
    std::cin >> choice;

    std::list<Device*>::iterator iter ;
    Device *chosen;
    std::list<Device*> listDevice = c.getListDevices();
    for(iter = listDevice.begin() ; (iter != listDevice.end()) ;iter++){
        std::cout << "Hello\n";
        if (choice == (*iter)->getId())
            chosen = *iter;
    }

    std::cout << "You choose Device " << (int) chosen->getId() << std::endl;
    if (c.connectDevice(chosen))
        std::cout << "You are connected" << std::endl;
    
    return 0;
}

/*

echo /dev/bus/usb/`udevadm info --name=/dev/ttyUSB0 --attribute-walk | sed -n 's/\s*ATTRS{\(\(devnum\)\|\(busnum\)\)}==\"\([^\"]\+\)\"/\4/p' | head -n 2 | awk '{$1 = sprintf("%03d", $1); print}'` | tr " " "/"

 */
