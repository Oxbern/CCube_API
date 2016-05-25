#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include <queue>

#include "Device.h"
#include "Message.h"
#include "Listener.h"
//class Listener; //Needed to avoid recursive includes

#include <stdbool.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

struct Dictionnary{
    int bus;
    int Device;
} typedef Dictionnary;



class Controller {
private:
    std::list<Listener> listeners;
    std::list<Device> devices;
    Device *connectedDevice;
    std::queue<Message> messages; //FIFO of last messages
public:
    Controller();
    ~Controller();

    bool addListener(Listener &l);
    bool removeListener(Listener &l);
    void listAllDevices();
    bool connectDevice(Device d);
    Device* getConnectedDevice();

};

char ** getTtyList(int *size);
char * getNextWord(char *path, int *j);
Dictionnary *getDictSTM( int *nbSTM);
bool isInDico(std::string echo, Dictionnary *dic, int sizeOfDic);
#endif //CONTROLLER_H
