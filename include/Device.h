#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <fstream>

#include "DeviceShape.h"
#include "DataMessage.h"
#include "Debug.h"

class Device {
private :
    std::string id;
    std::fstream file;
    std::string port;
    std::string firmwareVersion;
    float luminosity;
    int sizeX;
    int sizeY;
    int sizeZ;
    bool isAvailable;
    DeviceShape *currentConfig;
public :
    Device(std::string port, std::string id, int sizeX, int sizeY, int sizeZ);
    ~Device();

    bool available();
    bool connect();
    bool disconnect();
    bool display();
    bool updateFirmware(); //TODO Set binary file as arg
    float getLuminosity();
    std::string getFirmwareVersion();
    bool askForDisplaySize();
    bool send(Message mess);
    void write(std::string data);

    //TODO Rajouter les setters et getters
    std::string getId();

};
#endif //CUBEAPI_DEVICE_H
