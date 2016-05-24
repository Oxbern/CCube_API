#include "Utils.h"
#include "Ack.h"

/**
 * @brief Creates an ack with all parameters set to 0
 */
Ack::Ack() : ackType(0), opCode(0), sizeLeft(0), crc(0)
{
}

/**
 * @brief Creates an ack
 * @param ackType : ACK_OK, ACK_ERR, ACK_NOK
 * @param opCode : command of message
 * @param sizeLeft : size left of message to send
 * @param crc : crc of ACK 
 */
Ack::Ack(uint8_t ack, uint8_t code, uint16_t size, uint16_t crcCheck) :    
    ackType(ack), opCode(code), sizeLeft(size), crc(crcCheck)
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

/** 
 * @brief Sets the ack depending on the received message
 * @param fd file descriptor
 */
void Ack::setAck(int fd)
{

}

/**
 * @brief Gets the ackType
 */
uint8_t Ack::getAckType() {
    return this->ackType;
}

/**
 * @brief Gets the OpCode of the last received buffer
 */
uint8_t Ack::getOpCode() {
    return this->opCode;
}

/**
 * @brief Gets the SizeLeft of the last received buffer
 */
uint16_t Ack::getSizeLeft() {
    return this->sizeLeft;
}

/**
 * @brief Gets the crc
 */
uint16_t Ack::getCrc() {
    return this->crc;
}
