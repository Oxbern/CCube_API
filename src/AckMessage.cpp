#include "Utils.h"
#include "AckMessage.h"

/**
 * @brief Creates an ack with all parameters set to 0
 */
AckMessage::AckMessage() : Message()
{
}

/**
 * @brief Creates an ack
 * @param ackType : ACK_OK, ACK_ERR, ACK_NOK
 * @param opCode : command of message
 * @param sizeLeft : size left of message to send
 * @param crc : crc of ACK 
 */
AckMessage::AckMessage(uint8_t ackType) : Message(SIZE_ACK, SIZE_OPCODE + SIZE_SIZE, ackType)
{

}

/**
 * @brief Destructor
 */
AckMessage::~AckMessage()
{
}

/**
 *@brief Fills the buffers with data
 *@param data
 */
void AckMessage::encode(uint8_t *dataToEncode)
{}

/**
 * @brief Fills the buffers with the data : id of pack
 * @param sizeLeft
 * @param opCode
 */
void AckMessage::encodeAck(uint16_t sizeLeftPack, uint8_t opCodePack)
{
    uint8_t *tab = new uint8_t[3];
    packID(sizeLeftPack, opCodePack, tab);
    this->encode(tab);

    delete [] tab;
}
/**
 * @brief Checks the ACK's crc
 * @param crc
 * @return boolean
 */
bool AckMessage::checkAck(uint16_t crc) {
    return (this->crc == crc ? true : false);
}

/**
 * @brief Acts depending on the type of ACK
 * @param fd file descriptor
 * @param msg Message
 */
void AckMessage::handleAck(int fd, Message &msg)
{
    //    if (opCode != ACK_OK) {
    //     Buffer buff;
    //     buff = msg.getBuffer(listBuffer[0].getOpCode(), listBuffer[0].getSizeLeft());
    //     buff.send(fd);        
    // }
}

/** 
 * @brief Sets the ack depending on the received message
 * @param fd file descriptor
 */
void AckMessage::setAck(int fd)
{

}

/**
 * @brief Gets the ackType
 */
uint8_t AckMessage::getAckType() {
    return this->opCode;
}

/**
 * @brief Gets the OpCode of the last received buffer
 */
uint8_t AckMessage::getOpCode() {
    return this->opCode;
}

/**
 * @brief Gets the SizeLeft of the last received buffer
 */
uint16_t AckMessage::getSizeLeft() {
    return this->listBuffer[0]->getSizeLeft();
}

/**
 * @brief Gets the crc
 */
uint16_t AckMessage::getCrc() {
    return this->listBuffer[0]->getCrc();
}
