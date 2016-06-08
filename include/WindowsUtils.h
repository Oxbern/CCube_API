#ifndef WINDOWSUTILS_H
#define WINDOWSUTILS_H

/*!
 * \file WindowsUtils.h
 * \brief Some cooking to get usb connected devices
 * \version 0.1
 */


#include "Controller.h"

#include <stdbool.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

/*!
 * \fn bool listAllDevices(Controller& c)
 * \brief Lists all devices which are connected via USB
 * \return TODO
 */
//bool listAllDevices(Controller &c);

/*!
 * \fn void listAndGetUSBConnectedDevices(Controller& c)
 * \brief Displays the list of all USB connected devices 
 * and pushes them in the device list
 */
//void listAndGetUSBConnectedDevices(Controller &c);

/*!
 * \fn void getNextWord(char *path, int *j, char * wordreturn)
 * \brief Gets the next word in a char
 * \param path the line to parse
 * \param j the beginning of the future parsing
 * \param wordreturn
 */
//void getNextWord(char *path, int *j, char * wordreturn);


#endif
