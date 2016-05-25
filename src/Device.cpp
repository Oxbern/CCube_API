#include <cstring>
#include <fstream>

#include "Device.h"
#include "ErrorException.h"
#include "Utils.h"
#include "VirtualCube.h"

Device::Device(std::string port, std::string id, int sizeX, int sizeY, int sizeZ)
{
    LOG(1, "DeviceShape constructor called");
    //Copy device's port
    if (port.length() > 0) {
        this->port = std::string(port);
    } else {
        throw ErrorException("Wrong port");
    }

    //Copy device's id
    if (id.length() > 0) {
        this->id = std::string(id);
    } else {
        throw ErrorException("Wrong id");
    }

    //Size initialization
    if (sizeX < 0 || sizeY < 0 || sizeZ < 0) {
        throw ErrorException("Invalid size of display");
    } else{
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        this->sizeZ = sizeZ;
    }

    //Luminosity initialization
    this->luminosity = -1.0;

    //Not available by default
    this->isAvailable = false;
}

Device::~Device()
{
    LOG(1, "DeviceShape destructor called");
}

bool Device::available()
{
    DataMessage m(0, OPCODE(AVAILABLE));
    while (!this->send(m)) {
        //TODO Timeout
        continue;
    }

    return this->isAvailable;
}

bool Device::connect(){
    LOG(1, "Trying to connect the device");
    if (!file.is_open()) {
        file.open(port, std::ios::in | std::ios::out);
    }

    LOG(1, "Device connected");
    return (file.is_open());
}

bool Device::disconnect()
{
    LOG(1, "Trying to disconnect the device");
    if (file.is_open()) {
        file.close();
    }
    LOG(1, "Device disconnected");
    return (!file.is_open());
}

bool Device::display()
{
    return false;
}

bool Device::updateFirmware()
{
    return false;
}

float Device::getLuminosity()
{
    return 0.0;
}

std::string Device::getFirmwareVersion()
{
    return 0;
}

bool Device::askForDisplaySize()
{
    return false;
}

bool Device::send(Message mess)
{
    LOG(1, "Sending message");
    if (!file.is_open()) {
        while (!connect()) {
            continue;
        }
    }
    for (int i = 0; i < mess.NbBuffers(); i++) {
        std::string buff= mess.getBuffer(i)->toString();
        if (this->port.compare("/dev/stdout") == 0) {
            //VirtualCube
            uint8_t * bufferArray = new uint8_t[mess.getBuffer(i)->getSizeBuffer()];
            mess.getBuffer(i)->toArray(bufferArray);
            CDC_Receive_FS(bufferArray);
            delete [] bufferArray;
        } else {
            while (!write(buff)) {
                continue;
            }
        }
    }

    LOG(1, "Message sended");
    return true;
}

std::string Device::getId() const
{
    return this->id;
}

bool Device::write(std::string data)
{
    if(this->file.is_open()) {
        this->file << data << std::endl;
        LOG(1, "Data written to file");
        return true;
    }else {
        LOG(1, "Unable to write data to file");
        return false;
    }
}
