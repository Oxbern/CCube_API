#include <cstring>
#include <fstream>

#include "Device.h"
#include "ErrorException.h"
#include "Utils.h"
#include "VirtualCube.h"
#include "Message.h"

/**
 * @brief TODO
 */
Device::Device(std::string port, int id)
{
    LOG(1, "Device constructor called");
    //Copy device's port
    if (port.length() > 0) {
        this->port = std::string(port);
    } else {
        throw ErrorException("Wrong port");
    }

    //Copy device's id
    if (id > 0) {
        this->id = id;
    } else {
        throw ErrorException("Wrong id");
    }

    //Size initialization
    //TODO Ask the size to the device
    this->sizeX = 9;
    this->sizeY = 9;
    this->sizeZ = 9;

    //Luminosity initialization
    this->luminosity = -1.0;

    //Not available by default
    this->isAvailable = false;

    this->currentConfig = new DeviceShape(sizeX,sizeY,sizeZ);
}

/**
 * @brief TODO
 */
Device::~Device()
{
    LOG(1, "DeviceShape destructor called");
    delete this->currentConfig;
}

/**
 * @brief TODO
 */
bool Device::available()
{
    DataMessage dm(this->id, 0, OPCODE(AVAILABLE));

    if (!send(&dm)){
        std::cerr << "Error while checking if the device availability" << std::endl;
        return false; //TODO See if unavailable or just error while sending buffer
    }
    return this->isAvailable;
}

/**
 * @brief TODO
 */
bool Device::connect(){
    LOG(1, "Trying to connect the device");
    if (!file.is_open()) {
        file.open(port, std::ios::in | std::ios::out); //TODO app flag usefull ?
    }

    LOG(1, "Device " + std::string((file.is_open() ? "connected" : "not connected")));
    return (file.is_open());
}

/**
 * @brief TODO
 */
bool Device::disconnect()
{
    LOG(1, "Trying to disconnect the device");
    if (file.is_open()) {
        file.close();
    }
    LOG(1, "Device disconnected");
    return (!file.is_open());
}

/**
 * @brief TODO
 */
bool Device::display()
{
    DataMessage dm (this->id, currentConfig->getSizeInBytes(), OPCODE(BUFF_SENDING));
    uint8_t *buffer = currentConfig->toArray();
    dm.encode(buffer);
    delete[](buffer);

    if (!send(&dm)){
        std::cerr << "Error while sending ledBuffer" << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief TODO
 */
bool Device::updateFirmware()
{
    return false;
}

/**
 * @brief TODO
 */
float Device::getLuminosity()
{
    return 0.0;
}

/**
 * @brief TODO
 */
std::string Device::getFirmwareVersion()
{
    return 0;
}

/**
 * @brief TODO
 */
bool Device::askForDisplaySize()
{
    return false;
}

/**
 * @brief TODO
 */
bool Device::write(uint8_t* data, int dataSize)
{
    if(this->file.is_open()) {
        if (this->file.write((char *)data, dataSize)){
            LOG(1, "Data written to file");
            return true;
        }else{
            LOG(1, "Error while writing data to file");
        }

    }else {
        LOG(1, "Unable to write data to file");
    }
    return false;
}

/**
 * @brief TODO
 */
bool Device::send(Message* mess)
{
    LOG(1, "Sending message");
    if (!file.is_open()) {
        while (!connect()) {
            //TODO Timeout
            continue;
        }
    }
    int n = mess->NbBuffers();
    for (int i = 0; i < n; i++) {
        int sizeBuffer = mess->getBuffer()[i].getSizeBuffer();
        uint8_t * buffString = new uint8_t[sizeBuffer];
        mess->getBuffer()[i].toArray(buffString);

        LOG(1, "DataSize : " + std::to_string(sizeBuffer));
        LOG(1, "Buffer send : " + uint8ArrayToString(buffString, sizeBuffer));

        if ((this->port.compare("/dev/stdin") == 0) || (this->port.compare("/dev/stdout") == 0)) {
            //VirtualCube

            //Virtual sending
            uint8_t* buffer = CDC_Receive_FS(buffString);
            delete []buffer;

        } else {
            while (!write(buffString, sizeBuffer)) {
                //TODO Timeout
                continue;
            }
        }
        delete []buffString;
    }
    LOG(1, "Message sended" );
    return true;
}

/**
 * @brief TODO
 */
int Device::getID() const
{
    return this->id;
}

/**
 * @brief TODO
 */
std::string Device::getPort() const
{
    return this->port;
}

/**
 * @brief TODO
 */
DeviceShape *Device::getcurrentConfig() const{
    return this->currentConfig;
}

/**
 * @brief TODO
 */
bool Device::on(int x, int y, int z)
{
    return currentConfig->on(x, y, z);
}

/**
 * @brief TODO
 */
bool Device::off()
{
    return currentConfig->off();
}

/**
 * @brief TODO
 */
bool Device::off(int x, int y, int z)
{
    return currentConfig->off(x, y, z);
}

/**
 * @brief TODO
 */
bool Device::toggle(int x, int y, int z)
{
    return currentConfig->toggle(x, y, z);
}

/**
 * @brief TODO
 */
std::fstream& Device::getFile()
{
    return this->file;
}
