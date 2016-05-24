#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include <queue>

#include "Listener.h"
#include "Device.h"
#include "Message.h"

class Controller {
private:
    std::list<Listener> listeners;
    std::list<Device> devices;
    Device connectedDevice;
    std::queue<Message> messages; //FIFO of last messages
public:
    Controller();
    ~Controller();

    bool addListener(Listener l);
    bool removeListener(Listener l);
    void listAllDevices();
    bool connectDevice(Device d);
    Device getConnectedDevice();

};

#endif //CUBEAPI_CONTROLLER_H
