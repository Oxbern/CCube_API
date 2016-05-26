#ifndef MESSAGE_H
#define MESSAGE_H

#include "Buffer.h"
#include <vector>

/**
 * @class Message 
 */

class Message {
 protected :
    int sizeBuffer;
    uint16_t sizeData;
    uint8_t opCode;
    Buffer *listBuffer;
    uint16_t crc;
    
 public :     
    Message();
    Message(int sizeBuff, uint16_t size, uint8_t code);
    Message(const Message &M);
    ~Message();
    int NbBuffers() const;


    void encode(uint8_t *dataToEncode);
    Buffer *getBuffer(int index) const;
    Buffer getBuffer(uint8_t opCode, uint16_t sizeLeft);
    int getSizeBuffer() const;
    uint16_t getSizeData() const;
    uint8_t getOpCode() const;
    uint16_t getCrc() const;
};


#endif
