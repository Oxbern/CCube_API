#include "Ack.h"

/**
 * @brief Creates an ack with all parameters set to 0
 */
Ack::Ack()
{

}

/**
 * @brief Creates an ack
 * @param ackType : ACK_OK, ACK_ERR, ACK_NOK
 * @param opCode : command of message
 * @param sizeLeft : size left of message to send
 * @param crc : crc of ACK 
 */
Ack::Ack(uint8_t ackType, uint8_t opCode, uint16_t sizeLeft, uint16_t crc)
{

}

/**
 * @brief Destructor
 */
Ack::~Ack()
{

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
void Ack::handleAck(int fd, Message &msg)
{

}

void Ack::setAck(int fd)
{

}
