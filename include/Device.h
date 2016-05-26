#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <fstream>

#include "DeviceShape.h"
#include "DataMessage.h"
#include "Debug.h"

class Device {
private :
    int id;
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
    // Port is found by Controller's constructor and id is defined there.
    Device();
    Device(std::string port, int id);
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
    bool write(std::string data);

    //TODO Rajouter les setters et getters
    int getId() const;
    std::string getPort() const;
    DeviceShape *getcurrentConfig() const;
    std::fstream & getFile();

};
#endif //CUBEAPI_DEVICE_H
