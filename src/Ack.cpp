#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "Ack.h"

/**
 * @brief Default Constructor
 */
Ack::Ack() {
    ackType = 0x00;
    opCode = 0x00;
    sizeLeft = 0;
    crc = 0;
}

/**
 * @brief Constructor
 * @param ackType : OK, ERR, NOK
 * @param opCode : command of message
 * @param sizeLeft : size left of message to send
 * @param crc : crc of ACK 
 */
Ack::Ack(uint8_t ackType, uint8_t opCode, uint16_t sizeLeft, uint16_t crc) {
    ackType = ackType;
    opCode = opCode;
    sizeLeft = sizeLeft;
    crc = crc;
}

/**
 * @brief Destructor
 */
Ack::~Ack() {

}

bool Ack::checkAck(uint16_t crc) {
    return (this->crc == crc ? true : false);
}

void Ack::handleAck(int fd, Message msg) {
    if (ackType != ACK_OK) {
	Buffer buf = msg.getBuffer(opCode, sizeLeft);
	buf.send(fd);
    }
}
