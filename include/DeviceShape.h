#ifndef DEVICESHAPE_H
#define DEVICESHAPE_H

#include <cstdint>
#include <iostream>

#include "Debug.h"
#include "ShapeToDisplay.h"

/**
 * @class DeviceShape
 */
class DeviceShape
{
 protected :
    void clearLed();
    int sizeX;
    int sizeY;
    int sizeZ;
    bool ***ledStatus;

 public :
    DeviceShape(int sizeX = 9, int sizeY = 9, int sizeZ = 9);
    ~DeviceShape();

    bool on(int x, int y, int z);
    bool off();
    bool off(int x, int y, int z);
    bool toggle(int x, int y, int z);
    int getSizeInBytes();
    uint8_t *  toArray();
    friend std::ostream& operator<<(std::ostream& os, const DeviceShape& d);

    void print(std::ostream &str) const;
    
    DeviceShape& operator=(const DeviceShape &ds);

    int getSizeX() const;
    int getSizeY() const;
    int getSizeZ() const;
    
    bool*** getLedStatus() const;
    
    
    // TODO : test this function
    bool copyLedStatus(ShapeToDisplay &s);
};

#endif //DEVICESHAPE_H
