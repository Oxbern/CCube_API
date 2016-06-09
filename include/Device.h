#ifndef DEVICE_H
#define DEVICE_H

/*!
 * \file Device.h
 * \brief TODO
 * \version 0.1
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
    struct timeval timeout; /*!< time waited before exiting read function */
    fd_set set; /*!<  needed for the timeout */
    std::string port; /*!< link to the file open by the file descriptor  */
    std::string firmwareVersion; /*!< not implemented yet */
    float luminosity; /*!< luminosity of the LEDs (not implemented yet) */
    int sizeX; /*!< First dimension of the device */
    int sizeY; /*!< Second dimension of the device */
    int sizeZ; /*!< Third dimension of the device */
    bool isAvailable; /*!< if the device is available (not implemented yet) */
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
     * \todo not yet implemented, is it usefull ?
     * \fn bool getFirmwareVersion()
     *
     * \brief not implemented yet
     *
     * \return
     */
    std::string getFirmwareVersion();

    /*!
     * \todo not yet implemented, is it usefull ?
     * \fn bool askForDisplaySize()
     *
     * \brief not implemented yet
     *
     * \return
     */
    bool askForDisplaySize();

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
    bool writeToFileDescriptor(uint8_t* data, int dataSize); //TODO set as private later

    /*!
     * \brief store the data received in a buffer
     * to process them later
     *
     * \param buffer  array where the data are stored
     * \param sizeBuffer  size of the data to collect
     */
    bool readFromFileDescriptor(uint8_t *buffer, uint16_t sizeBuffer);

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

    //TODO : Add setters and getters

    /*!
     * \fn int getID() const
     *
     * \brief Returns the id of the device
     *
     * \return int id : id of the device
     */
    int getID() const;

    /*!
     * \fn std::string getPort() const
     *
     * \brief Returns the port of the device
     *
     * \return std::string : port of the device
     */
    std::string getPort() const;

    /*!
     * \fn DeviceShape *getcurrentConfig() const
     *
     * \brief Returns the currentConfig of the device
     *
     * \return DeviceShape * : currentConfig of the device
     */
    DeviceShape *getcurrentConfig() const;

    /*!
     * \fn int getFile()
     *
     * \brief Returns the file descriptor of the device
     *
     * \return int : fd of the device
     */
    int getFile();

    /*!
     * \fn bool handleAck(OutgoingMessage *mess, Ack ack, int i)
     *
     * \brief Handles the acknowledge of the message
     *
     * \param mess  needed to know which message has to be send back
     * \param ack  to verify if the message was received well
     * \param i TODO
     *
     * \return true if the ack is an ACK_OK
     * false otherwise
     */
    //    bool handleAck(OutgoingMessage *mess, Ack &ack, int i);

    /*!
     * \fn bool setLedStatus(ShapeToDisplay s)
     *
     * \brief Sets the 3D array of the currentDevice to the 3D array
     *  of the ShapeToDisplay
     *
     * \return true if copy went well
     * false otherwise (for example dimensions did not match)
     */
    bool setLedStatus(ShapeToDisplay s);
};

#endif //CUBEAPI_DEVICE_H
