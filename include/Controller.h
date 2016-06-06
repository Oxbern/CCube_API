#ifndef CONTROLLER_H
#define CONTROLLER_H

/*!
 * \file Controller.h
 * \brief TODO
 * \version 0.1
 */

#include "ParentController.h"

/*!
 * \class Controller
 * \brief TODO
 */
class Controller : public ParentController
{
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
};

#endif //CONTROLLER_H
