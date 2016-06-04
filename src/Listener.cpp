#include <iostream>

#include "Listener.h"
#include "Controller.h"

/*!
 * \brief TODO
 * \param c controller
 */
void Listener::onInit(Controller & c)
{
    std::cout << "Initialization of Listener" << std::endl;
}

/*!
 * \brief TODO
 * \param c controller
 */
void Listener::onConnect(Controller & c)
{
    std::cout << "Device " << c.getConnectedDevice()->getID() << " connected" << std::endl;
}


/*!
 * \brief TODO
 * \param c controller
 */
void Listener::onDisconnect(Controller &)
{
    std::cout << "Disconnected" << std::endl;
}

/*!
 * \brief TODO
 * \param c controller
 */
void Listener::onData(Controller &)
{
    std::cout << "Data received" << std::endl;
}

/*!
 * \brief TODO
 * \param c controller
 */
void Listener::onDeviceChange(Controller &)
{
    std::cout << "Device changed" << std::endl;
}

/*!
 * \brief TODO
 * \param c controller
 */
void Listener::onExit(Controller &)
{
    std::cout << "Listener removed from the controller" << std::endl;
}
