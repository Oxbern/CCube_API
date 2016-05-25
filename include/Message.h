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
    std::vector<Buffer*> listBuffer;
    uint16_t crc;
    
 public :     
    Message();
    Message(int sizeBuff, uint16_t size, uint8_t code);
    ~Message();
    int NbBuffers();


    void encode(uint8_t *dataToEncode);

    Buffer* getBuffer(uint8_t opCode, uint16_t sizeLeft);
};


#endif
