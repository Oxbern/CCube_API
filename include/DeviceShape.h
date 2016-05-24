#ifndef DEVICESHAPE_H
#define DEVICESHAPE_H

#include <cstdbool>
#include <cstdint>


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
    void printAllLeds();
};
#endif //DEVICESHAPE_H
