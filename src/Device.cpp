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

/*! 
 * \brief Constructor
 * Constructor of the class Device
 * 
 * \param port  link to the file open by the file descriptor
 * \param id  ID of the device
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

    /* Set timeout */
    this->timeout.tv_sec = 0;
    this->timeout.tv_usec = 1000000L;

    /* Clear set */
    //FD_ZERO(&set);
    pfds[0].events = POLLIN;

    pfds[1].events = POLLOUT;


    //File descriptor (reading/writing)
    this->fd = -1;
}

/*!
 * \brief Destructor
 * Destructor of the class Device
 */
Device::~Device() 
{
    if (this->currentConfig != NULL) {
        delete this->currentConfig;
    }
    this->currentConfig = NULL;
    LOG(1, "~Device()");
}

/*! 
 * \fn bool connect()
 * 
 * \brief Connects the computer to the device
 * 
 * \return true if the device connected well
 * false otherwise
 */
bool Device::connect() 
{
    LOG(1, "Trying to connect the device");
    if (fd < 0) {
	    fd = open(port.c_str(), O_RDWR | O_NOCTTY);
	    if (fd == -1)
            std::cerr << "Error while opening the file descriptor : "
                << std::string(std::strerror(errno));
	    else {
            pfds[0].fd = fd;
            pfds[1].fd = fd;
	        fcntl(fd, F_SETFL, 0);
	        FD_SET(fd, &set);
	    }	    
    }

    LOG(2, "Device " + std::to_string(id) + std::string((fd >= 0 ? " " : " not ")) + "connected");
    return (fd >= 0);
}

/*! 
 * \fn bool disconnect()
 * 
 * \brief Disconnects the computer and the device
 * 
 * \return true if the device disconnected well
 * false otherwise
 */
bool Device::disconnect() 
{
    LOG(1, "Trying to disconnect the device");
    if (fd >= 0) {
        if (close(fd) == -1)
            std::cerr << "Error while closing the file descriptor : "
                << std::string(std::strerror(errno));
        else
            fd = -1;
    }

    LOG(2, "Device " + std::to_string(id) + std::string((fd == -1 ? " " : " not ")) + "disconnected");
    return (fd == -1);
}

/*! 
 * \fn bool updateFirmware()
 * 
 * \brief not implemented yet
 * 
 * \return true if
 * false otherwise
 */
bool Device::updateFirmware() 
{
    return false;
}

/*! 
 * \fn bool getFirmwareVersion()
 * 
 * \brief not implemented yet
 * 
 * \return 
 */
std::string Device::getFirmwareVersion() 
{
    return 0;
}

/*! 
 * \fn bool askForDisplaySize()
 * 
 * \brief not implemented yet
 * 
 * \return 
 */
bool Device::askForDisplaySize() 
{
    return false;
}

/*! 
 * \fn bool writeToFileDescriptor(uint8_t* data, int dataSize)
 * 
 * \brief write the data in the file descriptor 
 * 
 * \param data  data that needs to be written 
 * \param dataSize  size of data
 *
 * \return true if the writing went well
 * false otherwise
 */
bool Device::writeToFileDescriptor(uint8_t *data, int dataSize) {
    if (fd && dataSize > 0) {
        LOG(2, "[WRITE] Trying to write Buffer (SIZE = "
               + std::to_string(dataSize)
               + " Bytes) : DATA TO WRITE = "
               + uint8ArrayToString(data, dataSize));

        int ret = poll(pfds, 2, 1000);
        if (ret > 0) {
            if (pfds[1].revents & POLLOUT) {
                fsync(fd);
                if (write(fd, &data[0], dataSize)) {
                    LOG(2, "[WRITE] Data written to file");
                    return true;
                } else {
                    LOG(2, "[WRITE] Error while writing data to file : " + std::string(std::strerror(errno)));
                }
            }
        } else if (ret == 0)
            LOG(1, "[WRITE] Timeout");
        else
            LOG(2, "[WRITE] Error ");

    }
    return false;
}

/*!
 * \fn void readFromFileDescriptor(uint8_t ack_buffer[10])
 * 
 * \brief store the data received in a buffer 
 * to process them in the controler
 * 
 * \param ack_buffer  array where the data are stored
 */
bool Device::readFromFileDescriptor(uint8_t ack_buffer[10])
{
	/* Simple read from file descriptor */
    //int ret = select(this->getFile() + 1, &set, NULL, NULL, &timeout);
    int ret = poll(pfds, 2, 3000);
    if (ret > 0) {
        if (pfds[0].revents & POLLIN) {
            fsync(fd);
            ssize_t sizeRead = read(this->getFile(), ack_buffer, SIZE_ACK);
            LOG(2, "[READ] Reading from Device "
                   + std::to_string(id) + " | DATA READ = "
                   + uint8ArrayToString(ack_buffer, sizeRead));
            return true;
        }
    } else if (ret == 0)
        LOG(1, "[READ] Timeout");
    else
        LOG(1, "[READ] Error");
    return false;
}

/*! 
 * \fn bool handleResponse(uint8_t ack[10])
 * 
 * \brief not implemented yet
 * 
 * \return 
 */
bool Device::handleResponse(uint8_t ack[10]) 
{
    fprintf(stdout, "ACK : ");
    for (int i = 0; i < 10; ++i)
        fprintf(stdout, "%u |", ack[i]);
    fprintf(stdout, "\n");



    return true;
}

/*! 
 * \fn int getID() const
 * 
 * \brief Returns the id of the device
 *
 * \return int id : id of the device
 */
int Device::getID() const 
{
    return this->id;
}

/*! 
 * \fn std::string getPort() const
 * 
 * \brief Returns the port of the device
 * 
 * \return std::string : port of the device
 */
std::string Device::getPort() const 
{
    return this->port;
}

/*! 
 * \fn DeviceShape *getcurrentConfig() const
 * 
 * \brief Returns the currentConfig of the device
 * 
 * \return DeviceShape * : currentConfig of the device
 */
DeviceShape *Device::getcurrentConfig() const 
{
    return this->currentConfig;
}

/*! 
 * \fn bool on(int x, int y, int z)
 * 
 * \brief set the configuration of the LED of coordinates (x, y, z) to true
 * by calling the function of currentConfig (DeviceShape)
 * 
 * \param x  first coordinate of the LED
 * \param y  second coordinate of the LED
 * \param z  third coordinate of the LED
 * 
 * \return true if the configuration of the LED is now true 
 * false otherwise
 */
bool Device::on(int x, int y, int z) 
{
	return currentConfig->on(x, y, z);
}

/*! 
 * \fn bool off()
 * 
 * \brief Set the configuration of all LEDs to false
 * by calling the function of currentConfig (DeviceShape)
 * 
 * \return always return true
 */
bool Device::off() 
{
    return currentConfig->off();
}

/*! 
 * \fn bool off(int x, int y, int z)
 * 
 * \brief set the configuration of the LED of coordinates (x, y, z) to false
 * by calling the function of currentConfig (DeviceShape)
 * 
 * \param x  first coordinate of the LED
 * \param y  second coordinate of the LED
 * \param z  third coordinate of the LED
 *  
 * \return true if the configuration of the LED is now false 
 * false otherwise
 */
bool Device::off(int x, int y, int z) 
{
    return currentConfig->off(x, y, z);
}

/*! 
 * \fn bool toggle(int x, int y, int z)
 * 
 * \brief set the configuration of the LED of coordinates (x, y, z) to its 
 * opposite (true if it was false and false if it was true)
 * by calling the function of currentConfig (DeviceShape)
 * 
 * \param x  first coordinate of the LED
 * \param y  second coordinate of the LED
 * \param z  third coordinate of the LED
 * 
 * \return true if the whole shape stays in the 3D array
 * false otherwise
 */
bool Device::toggle(int x, int y, int z) 
{
    return currentConfig->toggle(x, y, z);
}

/*! 
 * \fn int getFile()
 * 
 * \brief Returns the file descriptor of the device
 * 
 * \return int : fd of the device
 */
int Device::getFile() 
{
    return this->fd;
}

/*! 
 * \fn bool handleAck(Message *mess, AckMessage ack)
 *
 * \brief Handles the acknowledge of the message
 * 
 * \param mess  needed to know which message has to be send back
 * \param ack  to verify if the message was received well 
 * 
 * \return true if the ack is an ACK_OK
 * false otherwise
 */
bool Device::handleAck(Message *mess, AckMessage &ack, int i)
{
    //Check the AckMessage
    if (ack.getOpCode() != ACK_OK) {
        LOG(3, "[HANDLER] ACK_NOK or ACK_ERR for Buffer N° " + std::to_string(i));

        //Extract pack data from the ackMessage
        uint8_t ackDataOpcode = ack.getListBuffer()[0].getData()[0];

        uint16_t ackDataSize = convertTwo8to16(ack.getListBuffer()[0].getData()[1],
                ack.getListBuffer()[0].getData()[2]);

        //Search the buffer to retransmit from the message
        Buffer *bufferToRetransmit = mess->getBuffer(ackDataOpcode, ackDataSize);
        if (bufferToRetransmit == NULL) {
            throw ErrorException("Error in an ack message "
                    ": buffer to retransmit not found in the message");
        }

        //Convert array to retransmit to an array of uint8_t
        uint8_t bufferArray[mess->getSizeBuffer()];
        bufferToRetransmit->toArray(bufferArray);

        //Try to retransmit the wrong buffer
        writeToFileDescriptor(bufferArray, mess->getSizeBuffer()); //TODO add timeout

        return false;
    } else {
        LOG(3, "[HANDLER] ACK_OK received for Buffer N° : " + std::to_string(i));
        return true;
    }
}

/*! 
 * \fn bool setLedStatus(ShapeToDisplay s)
 * 
 * \brief Sets the 3D array of the currentDevice to the 3D array
 *  of the ShapeToDisplay
 * 
 * \return true if copy went well
 * false otherwise (for example dimensions did not match)
 */
bool Device::setLedStatus(ShapeToDisplay s) 
{
    return currentConfig->copyLedStatus(s);
}
