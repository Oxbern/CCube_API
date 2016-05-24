#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>

#define DATA_MAX_SIZE 58
#define SIZE_BUFFER 64
#define HEADER_INDEX 0
#define OPCODE_INDEX 1
#define SIZE_INDEX 2
#define DATA_INDEX 4
#define CRC_INDEX 62

/**
 * @class Buffer
 * @brief TODO
 */

class Buffer {
 private :
    uint8_t header;
    uint8_t opCode;
    uint16_t sizeLeft;
    uint8_t *data;
    uint16_t crc;
public :

    Buffer();
    Buffer(uint8_t header, uint8_t opCode, uint16_t size, uint16_t crcCheck);
    ~Buffer();

    void toArray(uint8_t* buffLinear);

    void setHeader(uint8_t head);
    void setOpCode(uint8_t code);
    void setSizeLeft(uint16_t size);
    void setCrc(uint16_t crcCheck);
    void setData(uint8_t *data);
};

#endif
