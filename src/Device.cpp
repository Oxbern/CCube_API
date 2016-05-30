#include <cstring>
#include <fstream>

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <aio.h>


#include "Device.h"
#include "ErrorException.h"
#include "Utils.h"
#include "VirtualCube.h"
#include "Message.h"

/**
 * @brief TODO
 */
Device::Device(std::string port, int id) {
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

    this->currentConfig = new DeviceShape(sizeX, sizeY, sizeZ);

    this->fileR = -1;
}

/**
 * @brief TODO
 */
Device::~Device() {
    LOG(1, "Device destructor called");
    if (this->currentConfig != NULL) {
        delete this->currentConfig;
    }
    this->currentConfig = NULL;
}

/**
 * @brief TODO
 */
bool Device::available() {
    DataMessage dm(this->id, 0, OPCODE(AVAILABLE));

    if (!send(&dm)) {
        std::cerr << "Error while checking if the device availability" << std::endl;
        return false; //TODO See if unavailable or just error while sending buffer
    }
    return this->isAvailable;
}

/**
 * @brief TODO
 */
bool Device::connect() {
    LOG(1, "Trying to connect the device");
    if (!file.is_open()) {
        file.open(port, std::ios::in | std::ios::out | std::ios::app); //TODO app flag usefull ?
    }

    if (this->fileR == -1) {
        this->fileR = open(port.c_str(), O_RDONLY | O_RDONLY | O_APPEND);
        if (this->fileR == -1) {
            std::cerr << errno << std::endl;
        }else{
            LOG(2, "File open for reading");
        }
    }

    LOG(1, "Device " + std::string((file.is_open() ? "connected" : "not connected")));
    return (file.is_open());
}

/**
 * @brief TODO
 */
bool Device::disconnect() {
    LOG(1, "Trying to disconnect the device");
    if (file.is_open()) {
        file.close();
    }

    if (this->fileR != -1) {
        close(this->fileR);
    }

    LOG(1, "Device disconnected");
    return (!file.is_open());
}

/**
 * @brief TODO
 */
bool Device::display() {
    DataMessage dm(this->id, currentConfig->getSizeInBytes(), OPCODE(BUFF_SENDING));
    uint8_t *buffer = currentConfig->toArray();
    dm.encode(buffer);
    delete[](buffer);

    if (!send(&dm)) {
        std::cerr << "Error while sending ledBuffer" << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief TODO
 */
bool Device::updateFirmware() {
    return false;
}

/**
 * @brief TODO
 */
float Device::getLuminosity()
{
    DataMessage dm(this->id, 0, OPCODE(LIGHT_RECEPTION));

    if (!send(&dm)){
        std::cerr << "Error while asking the device brightness" << std::endl;
        return false; //TODO See if unavailable or just error while sending buffer
    }
    return this->luminosity;
}

/**
 * @brief TODO
 */
std::string Device::getFirmwareVersion() {
    return 0;
}

/**
 * @brief TODO
 */
bool Device::askForDisplaySize() {
    return false;
}

/**
 * @brief TODO
 */
bool Device::write(uint8_t* data, int dataSize) {
    if (this->file.is_open()) {
        LOG(2, "Buffer send (size = " + std::to_string(dataSize)
                + " Bytes) : " + uint8ArrayToString(data, dataSize));

        if (this->file.write((char *) data, dataSize)) {
            LOG(1, "Data written to file");
            return true;
        } else {
            LOG(1, "Error while writing data to file");
        }

    } else {
        LOG(1, "Unable to write data to file");
    }
    return false;
}

/**
 * @brief TODO
 */
bool Device::send(Message* mess) {

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

        LOG(3, mess->toStringDebug());

        if ((this->port.compare("/dev/stdin") == 0) || (this->port.compare("/dev/stdout") == 0)) {
            //VirtualCube
            LOG(2, "Buffer send (size = " + std::to_string(sizeBuffer)
                    + " Bytes) : " + uint8ArrayToString(buffString, sizeBuffer));

            LOG(1, "Virtual sending");
            //Virtual sending
            // uint8_t* buffer = CDC_Receive_FS(buffString);
            // delete []buffer;

        } else {
            
            while (!write(buffString, sizeBuffer)) {
	        continue;
            }
            
        }
        delete []buffString;
    }
    LOG(1, "Message sended");

    return true;
}

/**
 * @brief TODO
 */
int Device::getID() const {
    return this->id;
}

/**
 * @brief TODO
 */
std::string Device::getPort() const {
    return this->port;
}

/**
 * @brief TODO
 */
DeviceShape *Device::getcurrentConfig() const {
    return this->currentConfig;
}

/**
 * @brief TODO
 */
bool Device::on(int x, int y, int z) {
    return currentConfig->on(x, y, z);
}

/**
 * @brief TODO
 */
bool Device::off() {
    return currentConfig->off();
}

/**
 * @brief TODO
 */
bool Device::off(int x, int y, int z) {
    return currentConfig->off(x, y, z);
}

/**
 * @brief TODO
 */
bool Device::toggle(int x, int y, int z) {
    return currentConfig->toggle(x, y, z);
}

/**
 * @brief TODO
 */
std::fstream& Device::getFile() {
    return this->file;
}
