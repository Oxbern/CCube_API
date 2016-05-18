#ifndef CONNEXION
#define CONNEXION

/**
 * File descriptor to communicate with the device
 */
int fd = -1;


/**
 * @brief Open a connection with the device
 * @param dev : path of the device
 * @return file descriptor for communicate with the device
 */
int open_connection(char* dev);

#endif