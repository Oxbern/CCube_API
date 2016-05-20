#include "connexion.h"
#include <fcntl.h>

int fd = -1;

/**
 * @brief Opens a connection with the device
 * @param dev : path of the device
 * @return file descriptor for communicate with the device
 */
int open_connection(char* dev) {
    if (fd == -1)  {
        fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
    }
    return fd;
}
