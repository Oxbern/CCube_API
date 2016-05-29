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
    if (c.listAllDevices()) {

	    int choice = 0;
    
	    std::cout << "Enter the device's ID you want to connect : " << std::endl;
	    std::cin >> choice;

	    Device *chosen;

	    std::list<Device*>::iterator iter ;
	    std::list<Device*> listDevice = c.getListDevices();
	    for(iter = listDevice.begin() ; (iter != listDevice.end()) ;iter++){
		    if (choice == (*iter)->getID())
			    chosen = *iter;
	    }

	    std::cout << "You choose Device " << (int) chosen->getID() << std::endl;

	    if (c.connectDevice(chosen))
		    std::cout << "You are connected" << std::endl;

	    DeviceShape *ds = c.getConnectedDevice()->getcurrentConfig();
	    (*ds).on(4,4,4);
	    std::cout << "DeviceShape on (4,4,4)" << std::endl;

	    c.getConnectedDevice()->display();
	    std::cout << "DeviceShape displayed" << std::endl;
    }
    return 0;
}

/*

echo /dev/bus/usb/`udevadm info --name=/dev/ttyUSB0 --attribute-walk | sed -n 's/\s*ATTRS{\(\(devnum\)\|\(busnum\)\)}==\"\([^\"]\+\)\"/\4/p' | head -n 2 | awk '{$1 = sprintf("%03d", $1); print}'` | tr " " "/"

 */
