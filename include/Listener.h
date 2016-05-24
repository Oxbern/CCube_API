#ifndef LISTENER_H
#define LISTENER_H

class Controller; //Needed to avoid recursive includes

/**
 * @brief : TODO
 */
class Listener {
public:
    virtual void onInit(Controller & c);
    virtual void onConnect(Controller &c);
    virtual void onDisconnect(Controller &c);
    virtual void onData(Controller &c);
    virtual void onDeviceChange(Controller &c);
    virtual void onExit(Controller &c);
};

#endif //LISTENER_H
