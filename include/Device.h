#ifndef DEVICE_H
#define DEVICE_H

#include "DeviceShape.h"
#include "Message.h"

class Device {
private :
    char* id;
    int fd;
    char *port;
    float luminosity;
    int sizeX;
    int sizeY;
    int sizeZ;
    char* firmwareVersion;
    DeviceShape *currentConfig;
public :
    Device(char* port, int portLength, char* id, int idLength, int sizeX, int sizeY, int sizeZ);
    ~Device();

    bool available();
    bool connect();
    bool disconnect();
    bool display();
    bool updateFirmware(); //TODO Set binary file as arg
    float getLuminosity();
    char* getFirmwareVersion();
    bool askForDisplaySize();
    bool send(Message m);

    //TODO Rajouter les setters et getters
    char* getId();
};
#endif //CUBEAPI_DEVICE_H
