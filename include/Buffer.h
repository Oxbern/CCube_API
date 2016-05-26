#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>
#include <iostream>
#include "Debug.h"

/**
 * @class Buffer
 */

class Buffer {
 private :
    uint8_t header;
    int sizeBuffer;
    uint8_t opCode;
    uint16_t sizeLeft;
    uint8_t *data;
    uint16_t crc;
public :
    Buffer();
    Buffer(int sizeBuff);
    ~Buffer();

    void toArray(uint8_t* buffLinear);
    std::string toString();

    void setHeader(uint8_t head);
    void setOpCode(uint8_t code);
    void setSizeLeft(uint16_t size);
    void setCrc(uint16_t crcCheck);
    void setData(int index, uint8_t dataIndex);

    uint8_t getHeader() const;
    uint8_t getOpCode() const;
    uint16_t getSizeLeft() const;
    uint8_t *getData() const;
    uint16_t getCrc() const;
    int getSizeBuffer() const;

    bool operator==(Buffer b);
};

#endif
