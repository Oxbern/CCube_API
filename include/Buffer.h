#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>

#define DATA_MAX_SIZE 58
#define SIZE_BUFFER 64

/**
 * @class Buffer
 * @brief TODO
 */

class Buffer {
 private :
    uint8_t header;
    uint16_t crc;

 public :
    uint8_t *data;
    uint8_t opCode;
    uint16_t sizeLeft;
    
    Buffer();

    Buffer(uint8_t head, uint8_t code, uint16_t size, uint16_t crcCheck);

    ~Buffer();

    void setHeader(uint8_t head);
    void setOpCode(uint8_t code);
    void setSizeLeft(uint16_t size);
    void setCrc(uint16_t crcCheck);
    void setData(uint8_t *data);

    void send(int fd);

    void describe();
};

#endif
