#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <fstream>
#include <cstdio>

#include "DeviceShape.h"
#include "DataMessage.h"
#include "Debug.h"
#include "AckMessage.h"

/**
 * @class Device
 */
class Device
{
 private :
    int id;
    int fd;
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
    bool send(Message* mess);
    bool writeToFileDescriptor(uint8_t* data, int dataSize); //TODO set as private later
    bool on(int x, int y, int z);
    bool off();
    bool off(int x, int y, int z);
    bool toggle(int x, int y, int z);
    
    //TODO Rajouter les setters et getters
    int getID() const;
    std::string getPort() const;
    DeviceShape *getcurrentConfig() const;
    int getFile();

    bool handleAck(Message mess, AckMessage ack);
};

#endif //CUBEAPI_DEVICE_H
