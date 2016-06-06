#ifndef PARENTCONTROLLER_H
#define PARENTCONTROLLER_H

/*!
 * \file ParentController.h
 * \brief TODO
 * \version 0.1
 */

#include <list>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

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

/*!
 * \struct Dictionnary
 * \brief TODO
 * 
 */
struct Dictionnary{
    int bus; /*!< TODO */
    int Device; /*!< TODO */
} typedef Dictionnary;

/*!
 * \class ParentController
 * \brief Parent class of controller
 */
class ParentController
{
 protected:
    std::list<Listener> listeners; /*!< TODO */
    std::list<Device*> devices; /*!< TODO */
    Device *connectedDevice; /*!< TODO */
    std::queue<Message> messages; /*!< FIFO of the last message */
    std::queue <uint8_t*> buffReceived; /*!< TODO */
    std::thread ack_thread; /*!< TODO */
    std::mutex lock_ack; /*!< TODO */
    std::condition_variable cond_var;  /*!< TODO */

    /*!
     * \fn void *waitForACK() 
     * \brief Reads an ACK message from USB
     */
    void *waitForACK();

 public:
    /*!
     * \brief Constructor
     *
     * Creates a controller, 
     * lists all USB connected devices and adds them to the Device list
     *
     */
    ParentController();
    
    /*!
     * \brief Destructor
     *
     */
    ~ParentController();

    /*!
     * \fn bool addListener(Listener &l)
     * \brief Adds a listener to the controller's list of listeners
     * \param l listener to add
     * \return TODO
     */
    virtual bool addListener(Listener &l);

    /*!
     * \fn bool removeListener(Listener &l)
     * \brief Removes a listener to the controller's list of listeners
     * \param l listener to remove
     * \return TODO
     */
    virtual bool removeListener(Listener &l);

    /*!
     * \fn bool listAllDevices()
     * \brief Lists all devices which are connected via USB
     * \return TODO
     */
    virtual bool listAllDevices();

    /*!
     * \fn void listAndGetUSBConnectedDevices()
     * \brief Displays the list of all USB connected devices 
     * and pushes them in the device list
     */
    virtual void listAndGetUSBConnectedDevices();

    /*!
     * \fn std::string getPortFromID(int id)
     * \brief Gets the port of the connected device from its ID
     * \param id of the device to get the port from
     * \return string
     */
    virtual std::string getPortFromID(int id);

    /*!
     * \fn bool connectDevice(int id)
     * \brief Connects the controller to a device with its ID
     * \param id ID of the device to connect
     * \return 
     */
    virtual bool connectDevice(int id);

    /*!
     * \fn bool connectDevice(Device *d)
     * \brief Connects the controller to the Device specified in argument
     * \param d device to connect
     * \return bool
     */
    virtual bool connectDevice(Device *d);

    /*!
     * \fn bool connectDevice()
     * \brief Connects the controller to a device chosen from the list
     * \return
     */
    virtual bool connectDevice();

    /*!
     * \fn bool disconnectDevice()
     * \brief Disconnects the controller from the device
     * \return 
     */
    virtual bool disconnectDevice();

    /*!
     * \fn Device* getConnectedDevice()
     * \brief Accessor to the current connected device
     * \return the current connected device
     */
    virtual Device* getConnectedDevice();

    /*!
     * \fn bool send(Message* mess)
     * \brief
     * \param mess Message
     * \return 
     */
    virtual bool send(Message* mess);

    /*! 
     * \fn bool handleNewMessage(Message *mess, int currentBuff, int *nbTry, 
     * int *nbWait, bool *isAcknowledged)
     * \brief
     * \param mess
     * \param currentBuff
     * \param nbTry
     * \param nbWait
     * \param isAcknowledged
     * \return bool
     */
    virtual bool handleNewMessage(Message *mess, int currentBuff, int *nbTry,
                                  int *nbWait, bool *isAcknowledged);

    /*!
     * \fn std::list<Device*> getListDevices()
     * \brief Accessor to the list of USB connected devices
     * \return the list of USB connected devices
     */
    virtual std::list<Device*> getListDevices();

};

/*!
 * \fn void getNextWord(char *path, int *j, char * wordreturn)
 * \brief Gets the next word in a char
 * \param path the line to parse
 * \param j the beginning of the future parsing
 * \param wordreturn
 */
void getNextWord(char *path, int *j, char * wordreturn);

/*!
 * \fn Dictionnary *getDictSTM(int *nbSTM)
 * \brief Gets the result of a "lsusb | grep STM" system call in a Dictionnary(Bus:Device) structure
 * \param nbSTM the number of STM devices connected to return
 * \return
 */
Dictionnary *getDictSTM(int *nbSTM);

/*!
 * \fn bool isInDico(std::string echo, Dictionnary *dic, int sizeOfDic)
 * \brief Tests if the ttyPort corresponds to a STM device
 * \param echo the ttyPort
 * \param dic the Dictionnary to look into
 * \param sizeOfDic the Dictionnary's size
 * \return true if the ttyPort corresponds to a STM device
 */
bool isInDico(std::string echo, Dictionnary *dic, int sizeOfDic);

#endif //PARENTCONTROLLER_H