#include <mutex>
#include <unistd.h>
#include <fcntl.h>
#include <ErrorException.h>

#include "Controller.h"

/*!
 * \brief Constructor
 *
 * Creates a controller, 
 * lists all USB connected devices and adds them to the Device list
 *
 */
Controller::Controller() :
    ParentController()
{
    LOG(1, "Controller()");
}

/*!
 * \brief Destructor
 *
 */
Controller::~Controller()
{
    LOG(1,"~Controller()");
}

/*! 
 * \brief Switches on a led on the current connected device
 * \param x
 * \param y
 * \param z
 * \return bool
 */
bool Controller::on(int x, int y, int z)
{
    return connectedDevice->on(x,y,z);
}

/*! 
 * \brief Switches off a led on the current connected device
 * \param x
 * \param y
 * \param z
 * \return bool
 */
bool Controller::off(int x, int y, int z)
{
    return connectedDevice->off(x,y,z);
}

/*! 
 * \brief Switches off the entire device
 * \return bool
 */
bool Controller::off()
{
    return connectedDevice->off();
}

/*! 
 * \brief Sets the state of a led to its opposite on the current connected device
 * \param x
 * \param y
 * \param z
 * \return bool
 */
bool Controller::toggle(int x, int y, int z)
{
    return connectedDevice->toggle(x,y,z);
}
