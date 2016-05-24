#ifndef LISTENER_H
#define LISTENER_H


class Listener {
public:
    virtual void onInit();
    virtual void onConnect();
    virtual void onDisconnect();
    virtual void onData();
    virtual void onDeviceChange();
    virtual void onExit();
};

#endif //CUBEAPI_LISTENER_H
