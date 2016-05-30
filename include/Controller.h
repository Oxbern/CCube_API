#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include <queue>
#include <thread>

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


/**
 * @class Controller
 */
class Controller
{
 private:
    std::list<Listener> listeners;
    std::list<Device*> devices;
    Device *connectedDevice;
    std::queue<Message> messages; //FIFO of last messages
    std::thread t;
 public:
    Controller();
    ~Controller();

    bool addListener(Listener &l);
    bool removeListener(Listener &l);
    bool listAllDevices();
    void listAndGetUSBConnectedDevices();
    bool connectDevice(Device *d);
    bool disconnectDevice();
    Device* getConnectedDevice();
    std::list<Device*> getListDevices();

    void readingTask();


};

char ** getTtyList(int *size);
void getNextWord(char *path, int *j, char * wordreturn);
Dictionnary *getDictSTM( int *nbSTM);
bool isInDico(std::string echo, Dictionnary *dic, int sizeOfDic);
#endif //CONTROLLER_H
