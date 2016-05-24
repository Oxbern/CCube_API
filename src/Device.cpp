#include <cstring>

#include "Device.h"
#include "ErrorException.h"

Device::Device(char* port, int portLength, char* id, int idLength, int sizeX, int sizeY, int sizeZ)
{
    //Copy device's port
    if (port != NULL && portLength > 0) {
        this->port = new char[portLength]; //Don't forget '/0' character
        strcpy(this->port, port);
    } else {
        throw ErrorException("Wrong port");
    }

    //Copy device's id
    if (port != NULL && portLength > 0) {
        this->id = new char[idLength]; //Don't forget '/0' caracter
        strcpy(this->id, id);
    } else {
        throw ErrorException("Wrong id");
    }

    //FD initialization
    this->fd = -1;

    //Size initialization
    if (sizeX < 0 || sizeY < 0 || sizeZ < 0) {
        throw ErrorException("Invalid size of display");
    } else{
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        this->sizeZ = sizeZ;
    }

    //Current led configuration
    this->currentConfig = NULL;

    //Firmware version initialization
    this->firmwareVersion = NULL;

    //Luminosity initialization
    this->luminosity = -1.0;
}

Device::~Device()
{
    if (id != NULL) {
        delete id;
        id = NULL;
    }
    if (port != NULL) {
        delete port;
        port = NULL;
    }
    if (firmwareVersion != NULL) {
        delete firmwareVersion;
        firmwareVersion = NULL;
    }

}

bool Device::available()
{
    return false;
}

bool Device::connect(){
    return false;
}

bool Device::disconnect()
{
    return false;
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

char* Device::getFirmwareVersion()
{
    return 0;
}

bool Device::askForDisplaySize()
{
    return false;
}

bool Device::send(Message m)
{
    return false;
}

char* Device::getId()
{
    return this->id;
}