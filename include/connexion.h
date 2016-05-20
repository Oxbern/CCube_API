#ifndef CONNEXION_H
#define CONNEXION_H

/**
 * File descriptor to communicate with the device
 */
extern int fd;


/**
 * @brief Opens a connection with the device
 * @param dev : path of the device
 * @return file descriptor for communicate with the device
 */
int open_connection(char* dev);

#endif
