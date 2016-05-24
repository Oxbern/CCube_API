#ifndef DEVICESHAPE_H
#define DEVICESHAPE_H

class DeviceShape {
protected :
    int sizeX;
    int sizeY;
    int sizeZ;
    bool ***ledBuffer;

public :
    DeviceShape();
    ~DeviceShape();
};
#endif //CUBEAPI_DEVICESHAPE_H
