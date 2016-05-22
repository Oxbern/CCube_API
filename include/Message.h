#ifndef MESSAGE_H
#define MESSAGE_H

#include "Buffer.h"

/**
 * @class Message
 * @brief TODO
 */

class Message {
 private :
    uint16_t size;
    uint8_t opCode;
    Buffer *listBuffer;

 public :
    Message();
    Message(uint16_t size, uint8_t code);
    ~Message();

    int NbBuffers();
    void encode(uint8_t *dataToEncode);
    void send(int fd);
};

#endif
