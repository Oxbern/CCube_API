#include "Device.h"

Device::Device()
{

}

Device::~Device()
{

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