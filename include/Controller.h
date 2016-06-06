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
     * \return bool
     */
    bool setLuminosity();
    
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
    
};

#endif //CONTROLLER_H
