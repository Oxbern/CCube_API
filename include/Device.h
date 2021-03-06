#ifndef DEVICE_H
#define DEVICE_H

/*!
 * \file Device.h
 * \brief Represents a device
 * \version 1.0
 */

#include <iostream>
#include <fstream>
#include <cstdio>

#ifdef _WIN32
#include <winsock2.h>

#ifndef O_NOCTTY
#define O_NOCTTY 0
#endif

#ifndef O_NDELAY
#define O_NDELAY 0
#endif

#else //LINUX
#include <sys/poll.h>

#endif

#include "DeviceShape.h"
#include "Utils.h"

/*!
 * \class Device
 * \brief Parameters of a device we can connect to
 */
class Device
{
 private :
    int id; /*!< identifier of the device */
    int fd; /*!< file descriptor of the device */
    std::string port; /*!< link to the file open by the file descriptor  */
    uint8_t firmwareVersion; /*!< not implemented yet */
    uint8_t luminosity; /*!< luminosity of the LEDs */
    int sizeX; /*!< First dimension of the device */
    int sizeY; /*!< Second dimension of the device */
    int sizeZ; /*!< Third dimension of the device */
    bool isAvailable; /*!< if the device is available */
    DeviceShape *currentConfig; /*!< state of the LEDs of the device */

 public :

    // Port is found by Controller's constructor and id is defined there.

    /*!
     * \brief Constructor
     * Constructor of the class Device
     *
     * \param port  link to the file open by the file descriptor
     * \param id  ID of the device
     */
    Device(std::string port, int id);

    /*!
     * \brief Destructor
     * Destructor of the class Device
     */
    ~Device();

    /*!
     * \fn bool connect()
     *
     * \brief Connects the computer to the device
     *
     * \return true if the device connected well
     * false otherwise
     */
    bool connect();

    /*!
     * \fn bool disconnect()
     *
     * \brief Disconnects the computer and the device
     *
     * \return true if the device disconnected well
     * false otherwise
     */
    bool disconnect();

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
    bool writeToFileDescriptor(uint8_t* data, int dataSize);

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
    bool on(int x, int y, int z);

    /*!
     * \fn bool off()
     *
     * \brief Set the configuration of all LEDs to false
     * by calling the function of currentConfig (DeviceShape)
     *
     * \return always return true
     */
    bool off();

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
    bool off(int x, int y, int z);

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
    bool toggle(int x, int y, int z);

    /*!
     * \fn int getID() const
     *
     * \brief Returns the id of the device
     *
     * \return id of the device
     */
    int getID() const;

    /*!
     * \fn std::string getPort() const
     *
     * \brief Returns the port of the device
     *
     * \return port of the device
     */
    std::string getPort() const;

    /*!
     * \fn DeviceShape *getCurrentConfig() const
     *
     * \brief Returns the currentConfig of the device
     *
     * \return currentConfig of the device
     */
    DeviceShape *getCurrentConfig() const;

    /*!
     * \fn int getFile()
     *
     * \brief Returns the file descriptor of the device
     *
     * \return fd of the device
     */
    int getFile();

    /*!
     * \fn bool setLedStatus(ShapeToDisplay s)
     *
     * \brief Sets the 3D array of the currentDevice to the 3D array
     *  of the ShapeToDisplay
     *
     * \return true if copy went well
     * false otherwise (for example dimensions did not match)
     */
    bool setLedStatus(ShapeToDisplay &s);

    /*!
     * \fn void setLuminosity(uint8_t l)
     * \brief sets the luminosity
     * \param l the value of the luminosity
     */
    void setLuminosity(uint8_t l);

    /*!
     * \fn void setDimension(uint8_t* dim)
     * \brief sets the dimensions
     * \param dim an array of sizex, sizey, sizez
     */
    void setDimension(uint8_t *dim);

    /*!
     * \fn void setVersionFirmware(uint8_t v)
     * \brief sets the firmware's version
     * \param v the new version
     */
    void setVersionFirmware(uint8_t v);

    /*!
     * \fn void setID(uint8_t id);
     * \brief sets the ID
     * \param id the device's ID
     */
    void setID(uint8_t id);


};

#endif //CUBEAPI_DEVICE_H
