#include "Cube.h"
#include "Controller.h"

int main(int argc, char** argv) {

    Controller c;
    Device *chosen;

    if (c.listAllDevices()) {

        int choice = 0;

        std::cout << "Enter the device's ID you want to connect : " << std::endl;
        std::cin >> choice;


        std::list<Device*>::iterator iter;
        std::list<Device*> listDevice = c.getListDevices();
        for (iter = listDevice.begin(); (iter != listDevice.end()); iter++) {
            if (choice == (*iter)->getID())
                chosen = *iter;
        }

        std::cout << "You choose Device " << (int) chosen->getID() << std::endl;

        if (c.connectDevice(chosen)) {

            std::cout << "You are connected to " << c.getConnectedDevice()->getPort() << std::endl;
        }
    }
    Device *dc = c.getConnectedDevice();

    Point p(0, 0, 0);

    Cube cube(5, 9, 9, 9, dc, p, true);

    dc->display();
    
    std::cout << "DeviceShape displayed" << std::endl;

    c.disconnectDevice();
    
    return 0;
}

