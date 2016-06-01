#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include <queue>
#include <thread>
#include <mutex>

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

#define MAX_NUMBER_ACK 10

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
    uint8_t ack_index;
    uint8_t ack[MAX_NUMBER_ACK][SIZE_ACK];
    std::thread ack_thread;
    std::mutex lock_ack;

    void *waitForACK();

 public:
    Controller();
    ~Controller();

    bool addListener(Listener &l);
    bool removeListener(Listener &l);
    bool listAllDevices();
    void listAndGetUSBConnectedDevices();
    bool connectDevice(Device *d);
    bool connectDevice();
    bool disconnectDevice();
    Device* getConnectedDevice();
    bool send(Message* mess);
    bool displayDevice();
    
    std::list<Device*> getListDevices();

};

char ** getTtyList(int *size);
void getNextWord(char *path, int *j, char * wordreturn);
Dictionnary *getDictSTM( int *nbSTM);
bool isInDico(std::string echo, Dictionnary *dic, int sizeOfDic);
#endif //CONTROLLER_H
