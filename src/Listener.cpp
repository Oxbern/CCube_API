#include <iostream>

#include "Listener.h"
#include "Controller.h"

/*!
 * \fn virtual void onInit(Controller & c)
 * \brief TODO
 * \param c controller
 */
void Listener::onInit(Controller & c)
{
    std::cout << "Initialization of Listener" << std::endl;
}

/*!
 * \fn virtual void onConnect(Controller &c)
 * \brief TODO
 * \param c controller
 */
void Listener::onConnect(Controller & c)
{
    std::cout << "Device " << c.getConnectedDevice()->getID() << " connected" << std::endl;
}


/*!
 * \fn virtual void onDisconnect(Controller &c)
 * \brief TODO
 * \param c controller
 */
void Listener::onDisconnect(Controller &)
{
    std::cout << "Disconnected" << std::endl;
}

/*!
 * \fn virtual void onData(Controller &c)
 * \brief TODO
 * \param c controller
 */
void Listener::onData(Controller &)
{
    std::cout << "Data received" << std::endl;
}

/*!
 * \fn virtual void onDeviceChange(Controller &c)
 * \brief TODO
 * \param c controller
 */
void Listener::onDeviceChange(Controller &)
{
    std::cout << "Device changed" << std::endl;
}

/*!
 * \fn virtual void onExit(Controller &c)
 * \brief TODO
 * \param c controller
 */
void Listener::onExit(Controller &)
{
    std::cout << "Listener removed from the controller" << std::endl;
}
