#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cerrno>

#define DATA_MAX_SIZE 58

/**
 * @class Buffer
 * @brief TODO
 */

class Buffer {
 private :
    uint8_t header;
    uint8_t codop;
    uint16_t sizeLeft;
    uint8_t data[DATA_MAX_SIZE];
    uint16_t crc;

 public :
    Buffer();

    ~Buffer();

};

#endif
