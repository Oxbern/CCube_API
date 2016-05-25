#ifndef DEVICESHAPE_H
#define DEVICESHAPE_H

#include <cstdint>
#include <iostream>

#include "Debug.h"

//TODO : DOC
class DeviceShape {
private :
    void clearLed();
    int sizeX;
    int sizeY;
    int sizeZ;
    bool ***ledStatus;

public :
    DeviceShape(int sizeX, int sizeY, int sizeZ);
    ~DeviceShape();

    bool on(int x, int y, int z);
    bool off();
    bool off(int x, int y, int z);
    bool toggle(int x, int y, int z);
    uint8_t *  toArray();
    friend std::ostream& operator<<(std::ostream& os, const DeviceShape& d);
};
#endif //DEVICESHAPE_H
