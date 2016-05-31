#include <cstring>
#include <fstream>
#include <errno.h>

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
Device::Device(std::string port, int id)
{
    LOG(1, "Device(port, id)");
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

    this->fd = -1;
}

/**
 * @brief TODO
 */
Device::~Device()
{
    LOG(1, "~Device()");
    if (this->currentConfig != NULL) {
        delete this->currentConfig;
    }
    this->currentConfig = NULL;
}

/**
 * @brief TODO
 */
bool Device::available()
{
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
bool Device::connect()
{
    LOG(1, "Trying to connect the device");
    if (fd < 0) {
	    fd = open(port.c_str(), O_RDWR | O_NOCTTY);
	    	fcntl(fd, F_SETFL, 0);
    }

    LOG(1, "Device " + std::string((fd >= 0 ? "" :  "not ")) + "connected");
    return (fd >= 0);
}

/**
 * @brief TODO
 */
bool Device::disconnect()
{
    LOG(1, "Trying to disconnect the device");
    if (fd < 0) {
	    close(fd);
        fd = -1;
    }

    LOG(1, "Device " + std::string((fd == -1 ? "" :  "not ")) + "disconnected");
    return (fd == -1);
}

/**
 * @brief TODO
 */
bool Device::display()
{
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
bool Device::updateFirmware()
{
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
bool Device::writeToFileDescriptor(uint8_t* data, int dataSize)
{
    if (fd) {
        LOG(2, "Trying to write Buffer (size = " + std::to_string(dataSize)
            + " Bytes) : " + uint8ArrayToString(data, dataSize));

        if (write(fd, (char *) data, dataSize)) {
            LOG(2, "Data written to file");

            return true;
        } else {
            LOG(2, "Error while writing data to file : " + std::string(std::strerror(errno)));
        }

    } else {
        LOG(2, "Unable to write data to file : wrong file descriptor");
    }
    return false;
}

/**
 * @brief TODO
 */
bool Device::send(Message* mess)
{
    LOG(1, "Trying to send a message");
    if (mess != NULL) {
        if (!fd) {
            while (!connect()) {
                //TODO Timeout
                continue;
            }
        }
        int n = mess->NbBuffers();
        for (int i = 0; i < n; i++) {
            int sizeBuffer = mess->getBuffer()[i].getSizeBuffer();
            uint8_t *buffString = new uint8_t[sizeBuffer];
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

                while (!writeToFileDescriptor(buffString, sizeBuffer)) {
                    continue;
                }


            }
            delete[]buffString;
        }
        LOG(1, "Message sended");

        return true;
    }
    LOG(1, "Unable to send a message to the device");
    return false;
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
DeviceShape *Device::getcurrentConfig() const
{
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
bool Device::off() {
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
int Device::getFile()
{
    return this->fd;
}

/**
 * @brief TODO
 */
bool Device::handleAck(Message mess, AckMessage ack)
{
    //Check the AckMessage
    if (ack.getOpCode() != ACK_OK) {
        LOG(3, "Handle an ACK_NOK or ACK_ERR");
        uint8_t ackDataOpcode = ack.getBuffer()[0].getData()[0];
        uint16_t ackDataSize = convertTwo8to16(ack.getBuffer()[0].getData()[1], ack.getBuffer()[0].getData()[2]);
        uint8_t buff[mess.getSizeBuffer()];

        mess.getBuffer(ackDataOpcode, ackDataSize).toArray(buff);
        writeToFileDescriptor(buff, mess.getSizeBuffer());

        return false;
    } else {
        LOG(3, "ACK_OK received");
        return true;
    }
}