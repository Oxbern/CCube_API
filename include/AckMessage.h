#ifndef ACK_H
#define ACK_H

#include "Message.h"

/**
 * @class ACK
 */

class AckMessage : public Message {
public :
    AckMessage();
    AckMessage(uint8_t ackType);
    ~AckMessage();

    void encode(uint16_t sizeLeftPack, uint8_t opCodePack);

    void handleAck(int fd, Message &msg);
    bool checkAck(uint16_t crc);
    void setAck(int fd);

    uint8_t getAckType();
    uint8_t getOpCode();
    uint16_t getSizeLeft();
    uint16_t getCrc();
};

#endif
