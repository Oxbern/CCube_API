#include <cstring>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

#include "Device.h"
#include "ErrorException.h"
#include "Utils.h"
#include "Debug.h"


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
    this->sizeX = 9;
    this->sizeY = 9;
    this->sizeZ = 9;

    //Luminosity initialization
    this->luminosity = 0;

    //Not available by default
    this->isAvailable = false;

    this->currentConfig = new DeviceShape(sizeX, sizeY, sizeZ);

    /* Set timeout */
    this->timeout.tv_sec = 0;
    this->timeout.tv_usec = 100000L;

    //File descriptor (reading/writing)
    this->fd = -1;

    /* Clear set */
    FD_ZERO(&set);
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
            throw ErrorException("Error while opening the file descriptor : "
                + std::string(std::strerror(errno)));
	    else {
#ifdef _WIN32
            //To make blocking:
            unsigned long off = 0;
            if (ioctlsocket(fd, FIONBIO, &off) != 0)
                {
                    /* Handle failure. */
                }
#else
            fcntl(fd, F_SETFL, 0);
#endif
	    }
    }

    LOG(2, "Device " + std::to_string(id) +
        std::string((fd >= 0 ? " " : " not ")) + "connected");

    return (fd >= 0);
}

/*!
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
            throw ErrorException("Error while closing the file descriptor : "
                                 + std::string(std::strerror(errno)));
        else
            fd = -1;
    }

    LOG(2, "Device " + std::to_string(id) +
        std::string((fd == -1 ? " " : " not ")) + "disconnected");
    return (fd == -1);
}


/*!
 * \brief write the data in the file descriptor
 *
 * \param data  data that needs to be written
 * \param dataSize  size of data
 *
 * \return true if the writing went well
 * false otherwise
 */
bool Device::writeToFileDescriptor(uint8_t *data, int dataSize)
{
    if (fd && dataSize > 0) {
        LOG(2, "[WRITE] Trying to write Buffer (SIZE = "
            + std::to_string(dataSize)
            + " Bytes) : DATA TO WRITE = "
            + uint8ArrayToString(data, dataSize));

        if (write(fd, &data[0], dataSize)) {
            LOG(2, "[WRITE] Data written to file");
            return true;
        } else
            LOG(2, "[WRITE] Error while writing data to file : "
                + std::string(std::strerror(errno)));
    }

    return false;
}

/*!
 * \brief store the data received in a buffer
 * to process them later
 *
 * \param buffer  array where the data are stored
 * \param sizeBuffer  size of the data to collect 
 * 
 * \return true if the reading went well
 * false otherwise
 */
bool Device::readFromFileDescriptor(uint8_t *buffer, uint16_t sizeBuffer)
{
    uint8_t localBuffer[sizeBuffer];

    int ret = select(fd, NULL, NULL, 0, &timeout);

    if (ret > 0) {
        ssize_t sizeRead = read(this->getFile(), &localBuffer[0], sizeBuffer);
        if (sizeRead >= 0) {

            LOG(5, "[READ] Reading from Device "
                + std::to_string(id) + " | DATA READ = "
                + uint8ArrayToString(localBuffer, sizeRead));

            /* Copy data received into buffer to fill */
            memcpy(&buffer[0], &localBuffer[0], sizeRead);
            return true;

        } else
            LOG(5, "[WRITE] Error while reading data to file : "
                + std::string(std::strerror(errno)));

    } else if (ret == 0)
        LOG(5, "[READ] Timeout");
    else
        LOG(5, "[READ] Error");

    return false;
}

/*!
 * \brief Returns the id of the device
 *
 * \return int id : id of the device
 */
int Device::getID() const
{
    return this->id;
}

/*!
 * \brief Returns the port of the device
 *
 * \return std::string : port of the device
 */
std::string Device::getPort() const
{
    return this->port;
}

/*!
 * \brief Returns the currentConfig of the device
 *
 * \return DeviceShape * : currentConfig of the device
 */
DeviceShape *Device::getCurrentConfig() const
{
    return this->currentConfig;
}

/*!
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
 * \brief Returns the file descriptor of the device
 *
 * \return int : fd of the device
 */
int Device::getFile()
{
    return this->fd;
}


/*!
 * \brief Sets the 3D array of the currentDevice to the 3D array
 *  of the ShapeToDisplay
 *
 * \return true if copy went well
 * false otherwise (for example dimensions did not match)
 */
bool Device::setLedStatus(ShapeToDisplay &s)
{
    return currentConfig->copyLedStatus(s);
}

/*!
 * \brief sets the luminosity
 * \param l the value of the luminosity
 */
void Device::setLuminosity(uint8_t l)
{
    this->luminosity = l;
}

/*!
 * \brief sets the dimensions
 * \param dim an array of sizex, sizey, sizez
 */
void Device::setDimension(uint8_t *dim)
{
    this->sizeX = (int)dim[0];
    this->sizeY = (int)dim[1];
    this->sizeZ = (int)dim[2];
}

/*!
 * \brief sets the firmware's version
 * \param v the new version
 */
void Device::setVersionFirmware(uint8_t v)
{
    this->firmwareVersion = v;
}

/*!
 * \brief sets the ID
 * \param id the device's ID
 */
void Device::setID(uint8_t id)
{
    this->id = id;
}
