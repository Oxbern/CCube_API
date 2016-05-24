#ifndef ACK_H
#define ACK_H

#include "Message.h"

/**
 * @class ACK
 */

class Ack {
private :
    uint8_t ackType;
    uint8_t opCode;
    uint16_t sizeLeft;
    uint16_t crc;
    
public :
    Ack();
    Ack(uint8_t ackType, uint8_t opCode, uint16_t sizeLeft, uint16_t crc);
    ~Ack();

    void handleAck(int fd, Message &msg);
    bool checkAck(uint16_t crc);
    void setAck(int fd);

    uint8_t getAckType();
    uint8_t getOpCode();
    uint16_t getSizeLeft();
    uint16_t getCrc();
};

#endif
