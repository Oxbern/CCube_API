#ifndef CONTROLLER_H
#define CONTROLLER_H

/*!
 * \file Controller.h
 * \brief TODO
 * \version 0.1
 */
#include <cstdint>
#include <list>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <iostream>
#include <algorithm>


#include "Device.h"
#include "OutgoingMessage.h"

#ifdef _WIN32
#include "mingw.thread.h"
#include "mingw.mutex.h"
#include "mingw.condition_variable.h"
#endif
/*!
 * \struct Dictionnary
 * \brief TODO
 *
 */
struct Dictionnary {
    int bus; /*!< TODO */
    int Device; /*!< TODO */
} typedef Dictionnary;

/*!
 * \class Controller
 * \brief TODO
 */
class Controller
{
 protected:
    std::list<Device*> devices; /*!< TODO */
    Device *connectedDevice; /*!< TODO */
    //    std::queue<OutgoingMessage> messages; /*!< FIFO of the last message */
    std::queue <uint8_t*> buffReceived; /*!< TODO */
    std::thread ack_thread; /*!< TODO */
    std::mutex lock_ack; /*!< TODO */
    std::condition_variable cond_var;  /*!< TODO */

    /*!
     * \fn void *waitForACK() 
     * \brief Reads an ACK message from USB
     */
    void *waitForACK();

 public:
    /*!
     * \brief Constructor
     *
     * Creates a controller, 
     * lists all USB connected devices and adds them to the Device list
     *
     */
    Controller();
    
    /*!
     * \brief Destructor
     *
     */
    ~Controller();

    /*! 
     * \fn bool on(int x, int y, int z)
     * \brief Switches on a led on the current connected device
     * \param x
     * \param y
     * \param z
     * \return bool
     */
    bool on(int x, int y, int z);

    /*! 
     * \fn bool off(int x, int y, int z)
     * \brief Switches off a led on the current connected device
     * \param x
     * \param y
     * \param z
     * \return bool
     */
    bool off(int x, int y, int z);

    /*! 
     * \fn bool off()
     * \brief Switches off the entire device
     * \return bool
     */
    bool off();

    /*! 
     * \fn bool toggle(int x, int y, int z)
     * \brief Sets the state of a led to its opposite on the current connected device
     * \param x
     * \param y
     * \param z
     * \return bool
     */
    bool toggle(int x, int y, int z);

    /*!
     * \fn bool display()
     * \brief TODO
     * \return bool
     */
    bool display();

    /*!
     * \fn bool setLuminosity() 
     * \brief Sets the device's luminosity
     * \param value to set the luminosity to
     * \return bool
     */
    bool setLuminosity(uint8_t value);
    
    /*!
     * \fn bool available()
     * \brief TODO
     * \return bool
     */
    bool available();

    /*!
     * \fn uint8_t getLuminosity()
     * \brief Returns the luminosity of the LEDs on the Device
     * \return the value of the luminosity
     */
    uint8_t getLuminosity();

    /*!
     * \fn uint8_t getVersionFirmware()
     * \brief Returns the version of the firmware
     * \return the version
     */
    uint8_t getVersionFirmware();

    /*!
     * \fn bool updateFirmware()
     * \brief Sends the firmware update
     * \return bool
     */
    bool updateFirmware(const std::string& file);


    /*!
     * \fn bool connectDevice(int id)
     * \brief Connects the controller to a device with its ID
     * \param id ID of the device to connect
     * \return 
     */
    bool connectDevice(int id);

    /*!
     * \fn bool disconnectDevice()
     * \brief Disconnects the controller from the device
     * \return 
     */
    bool disconnectDevice();

    /*!
     * \fn Device* getConnectedDevice()
     * \brief Accessor to the current connected device
     * \return the current connected device
     */
    Device* getConnectedDevice();

    /*!
     * \todo think about where to put it : Utils.h ?
     * \fn bool send(Message* mess)
     * \brief
     * \param mess Message
     * \return 
     */
    bool send(OutgoingMessage* mess);

    /*! 
     * \todo think about where to put it : Utils.h ?
     * \fn bool handleNewMessage(Message *mess, int currentBuff, int *nbTry, 
     * int *nbWait, bool *isAcknowledged)
     * \brief TODO
     * \param mess
     * \param currentBuff
     * \param nbTry
     * \param nbWait
     * \param isAcknowledged
     * \return bool
     */
    bool handleNewMessage(OutgoingMessage *mess, int currentBuff, int *nbTry,
                          int *nbWait, bool *isAcknowledged);

    /*!
     * \fn std::list<Device*> getListDevices()
     * \brief Accessor to the list of USB connected devices
     * \return the list of USB connected devices
     */
    std::list<Device*> getListDevices();
    
};

#endif //CONTROLLER_H
