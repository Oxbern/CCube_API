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
    uint8_t codeOp;
    uint16_t sizeLeft;
    uint8_t *data;
    uint16_t crc;

 public :
    Buffer();

    Buffer(uint8_t head, uint8_t code, uint16_t size, uint16_t crcCheck);

    ~Buffer();

};

#endif
