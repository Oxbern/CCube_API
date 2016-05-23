#ifndef MESSAGE_H
#define MESSAGE_H

#include "Buffer.h"

enum OPCODE {
    ACK_OK = 0x00,
    ACK_ERR = 0x01,
    ACK_NOK = 0x02,
    BUFF_SENDING = 0x10,
    LIGHT_SENDING = 0x11,
    BUFF_RECEPTION =  0XA0,
    LIGHT_RECEPTION = 0XA1,
    SIZE_RECEPTION = 0XB0,
    VERSION_RECEPTION = 0XB1,
    ID_RECEPTION = 0XB2,
    FIRMWARE_SENDING = 0x21,
    TFT_SENDING = 0x20,
    TOUCH_DETECTION = 0xC0
};

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
    void encode(uint8_t *dataToEncode, uint16_t sizeData);
    Buffer getBuffer(uint8_t opCode, uint16_t sizeLeft);
    void send(int fd);
};

#endif
