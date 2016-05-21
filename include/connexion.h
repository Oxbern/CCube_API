#ifndef CONNEXION_H
#define CONNEXION_H

#include <stdint.h>
#include "cube.h"

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

int getNumberOfBuffer(uint16_t size);

buffer* data_encoding(uint8_t codop, uint16_t size, uint8_t *data);

uint8_t* data_decoding(uint8_t *data, int length);


#endif
