#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

#include "Ack.h"

/**
 * @brief Creates an ack with all parameters set to 0
 */
Ack::Ack() {
    ackType = 0x00;
    opCode = 0x00;
    sizeLeft = 0;
    crc = 0;
}

/**
 * @brief Creates an ack
 * @param ackType : ACK_OK, ACK_ERR, ACK_NOK
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

/**
 * @brief Checks the ACK's crc
 * @param crc
 * @return boolean
 */
bool Ack::checkAck(uint16_t crc) {
    return (this->crc == crc ? true : false);
}

/**
 * @brief Acts depending on the type of ACK
 * @param fd file descriptor
 * @param msg Message
 */
void Ack::handleAck(int fd, Message msg) {
    if (ackType != ACK_OK) {
	Buffer buf = msg.getBuffer(opCode, sizeLeft);
	buf.send(fd);
    }
}

void Ack::setAck(int fd) {
    int index = 0,
	c = 0;

    uint8_t buf[6];
    
    while (read(fd, &c, 1) > 0) {
	buf[index] = c;
	index ++;
    }

    this->ackType = buf[0];
    this->opCode = buf[1];
    this->sizeLeft = (buf[2] << 8) + buf[3];
    this->crc = (buf[4] << 8) + buf[5];
}

void Ack::describe(void) {
    std::cout << "ACK: ";
    std::cout << (int)ackType << " | " << (int)opCode << " | "
	      << (int)sizeLeft << " | " << (int)crc << "\n";
}
