#include "Cube.h"
#include "Controller.h"
#include "LinuxUtils.h"

int main(int argc, char** argv)
{
    Controller c;

    if (!c.connectDevice(1)) {
        std::cerr << "Connection established" << std::endl;
        return EXIT_FAILURE;
    }
    int size = 5;
    Point p(0, 0, 0);
    bool full = true;
    int sizeX = 9;
    int sizeY = 9;
    int sizeZ = 9;
    
    Cube cube(size, p, full, sizeX, sizeY, sizeZ);

    c.display();
    
    std::cout << "DeviceShape displayed" << std::endl;

    c.disconnectDevice();
    
    return 0;
}

