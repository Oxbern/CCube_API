#ifndef CONTROLLER_H
#define CONTROLLER_H

/*!
 * \file Controller.h
 * \brief In this class are listed all the functionalities of the API
 * \version 1.0
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
 * \class Controller
 * \brief Creates a controller
 */
namespace apicube{
class Controller
{
 protected:
    Device *connectedDevice; /*!< the connected device*/

 public:
    bool secure;                /*!< Flag to set ACK security */
    std::list<Device*> devices; /*!< list of all plugged in devices*/
    bool pilot(); /*!< method for demo */

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
     * \param x the first coordinate
     * \param y the second coordinate
     * \param z the third coordinate
     * \return true if the change went well
     */
    bool on(int x, int y, int z);

    /*!
     * \fn bool off(int x, int y, int z)
     * \brief Switches off a led on the current connected device
     * \param x the first coordinate
     * \param y the second coordinate
     * \param z the third coordinate
     * \return true if the change went well
     */
    bool off(int x, int y, int z);

    /*!
     * \fn bool off()
     * \brief Switches off the entire device
     * \return true if the change went well
     */
    bool off();

    /*!
     * \fn bool toggle(int x, int y, int z)
     * \brief Sets the state of a led to its opposite on the current connected device
     * \param x the first coordinate
     * \param y the second coordinate
     * \param z the third coordinate
     * \return true if the change went well
     */
    bool toggle(int x, int y, int z);

    /*!
     * \fn bool display()
     * \brief Displays the status of the LEDs on the device
     * \return true if the functionality went well
     */
    bool display();

    /*!
     * \fn bool setLuminosity()
     * \brief Sets the device's luminosity
     * \param value to set the luminosity to
     * \return true if the functionality went well
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
     * \brief Returns the info (Size) of the cube
     * \return Array of integer: | SizeX | SizeY | SizeZ |
     */
    uint8_t *getDeviceInfo();

    /*!
     * \fn uint8_t getDeviceID()
     * \brief Returns the connected device's ID
     * \return the ID
     */
    uint8_t getDeviceID();
    
    /*!
     * \fn uint8_t getVersionFirmware()
     * \brief Returns the version of the firmware
     * \return the version
     */
    uint8_t getVersionFirmware();

    /*!
     * \fn bool updateFirmware()
     * \brief Sends the firmware update
     * \return true if the functionality went well
     */
    bool updateFirmware(const std::string& file);

    /*!
     * \fn bool printMsgScreen()
     * \brief Prints a message on the device's screen
     * \param message the message to print
     * \param sizeMessage the message's size
     * \return true if the functionality went well
     */
    bool printMsgScreen(char *message, uint8_t sizeMessage) ;

    /*!
     * \fn bool reset()
     * \brief Resets the connection
     * \return true if the functionality went well
     */
    bool reset();
    
    /*!
     * \fn bool connectDevice(int id)
     * \brief Connects the controller to a device with its ID
     * \param id ID of the device to connect
     * \return true if the connection went well
     */
    bool connectDevice(int id);

    /*!
     * \fn bool connectDevice(int id, bool secure)
     * \brief Connects the controller to a device with its ID
     * \param id ID of the device to connect
     * \param secure flag to set ACK security
     * \return true if the connection went well
     */
    bool connectDevice(int id, bool secure);

    /*!
     * \fn bool connectDevice(char *port, bool secure = false)
     * \brief Connects the controller to a device with its ID
     * \param port the port of the device to connect
     * \param secure default value to false
     * \return true if the connection went well
     */    
    bool connectDevice(char *port, bool secure = false);

    /*!
     * \fn bool disconnectDevice()
     * \brief Disconnects the controller from the device
     * \return true if the disconnection went well
     */
    bool disconnectDevice();

    /*!
     * \fn Device* getConnectedDevice()
     * \brief Accessor to the current connected device
     * \return the current connected device
     */
    Device* getConnectedDevice();

    /*!
     * \fn std::list<Device*> getListDevices()
     * \brief Accessor to the list of USB connected devices
     * \return the list of USB connected devices
     */
    std::list<Device*> getListDevices();

};
}
#endif //CONTROLLER_H
