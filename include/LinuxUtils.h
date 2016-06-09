#ifndef LINUXUTILS_H
#define LINUXUTILS_H

/*!
 * \file LinuxUtils.h
 * \brief Regroups all the functions used to see which devices are connected
 * \version 0.5
 */

#include <list>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Controller.h"

#include <stdbool.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
/*!
 * \struct Dictionnary
 * \brief used in the parsing
 *
 */
struct Dictionnary {
    int bus; /*!< bus */
    int Device; /*!< device */
} typedef Dictionnary;

/*!
 * \fn bool listAllDevices(Controller& c)
 * \brief Lists all devices which are connected via USB
 * \return true when the method exited successfully
 */
bool listAllDevices(Controller &c);

/*!
 * \fn void listAndGetUSBConnectedDevices(Controller& c)
 * \brief Displays the list of all USB connected devices 
 * and pushes them in the device list
 */
void listAndGetUSBConnectedDevices(Controller &c);

/*!
 * \fn void getNextWord(char *path, int *j, char * wordreturn)
 * \brief Gets the next word in a char
 * \param path the line to parse
 * \param j the beginning of the future parsing
 * \param wordreturn the word to return
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

/*!
 * \fn std::string getPortFromID(int id)
 * \brief Gets the port of the connected device from its ID
 * \param c controller
 * \param id of the device to get the port from
 * \return string
 */
std::string getPortFromID(Controller &c, int id);

#endif
