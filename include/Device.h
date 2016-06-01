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

    bool connect();
    bool disconnect();
    bool updateFirmware(); //TODO Set binary file as arg
    std::string getFirmwareVersion();
    bool askForDisplaySize();
    bool writeToFileDescriptor(uint8_t* data, int dataSize); //TODO set as private later
    void readFromFileDescriptor(uint8_t ack_buffer[10]);
    bool on(int x, int y, int z);
    bool off();
    bool off(int x, int y, int z);
    bool toggle(int x, int y, int z);
    
    //TODO Rajouter les setters et getters
    int getID() const;
    std::string getPort() const;
    DeviceShape *getcurrentConfig() const;
    int getFile();
    void handleResponse(uint8_t ack[10]);

    bool handleAck(Message *mess, AckMessage ack);
    
    bool setLedStatus(ShapeToDisplay s);
};

#endif //CUBEAPI_DEVICE_H
