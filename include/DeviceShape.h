#ifndef DEVICESHAPE_H
#define DEVICESHAPE_H

#include <cstdint>
#include <iostream>

#include "Debug.h"

//TODO : DOC
class DeviceShape {
protected :
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
    int getSizeInBytes();
    uint8_t *  toArray();
    friend std::ostream& operator<<(std::ostream& os, const DeviceShape& d);

    void print(std::ostream &str) const;
};
#endif //DEVICESHAPE_H
