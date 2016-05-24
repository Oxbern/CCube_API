#include <iostream>

#include "Listener.h"
#include "Controller.h"

void Listener::onInit(Controller & c)
{
    std::cout << "Initialization of Listener" << std::endl;
}

void Listener::onConnect(Controller & c)
{
    std::cout << "Device " << c.getConnectedDevice()->getId() << " connected" << std::endl;
}


void Listener::onDisconnect(Controller &)
{
    std::cout << "Disconnected" << std::endl;
}


void Listener::onData(Controller &)
{
    std::cout << "Data received" << std::endl;
}


void Listener::onDeviceChange(Controller &)
{
    std::cout << "Device changed" << std::endl;
}


void Listener::onExit(Controller &)
{
    std::cout << "Listener removed from the controller" << std::endl;
}