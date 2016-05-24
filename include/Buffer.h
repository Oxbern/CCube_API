#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>

/**
 * @class Buffer
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
    void setData(int index, uint8_t dataIndex);

    uint8_t getHeader();
    uint8_t getOpCode();
    uint16_t getSizeLeft();
    uint8_t *getData();
    uint16_t getCrc();
};

#endif
