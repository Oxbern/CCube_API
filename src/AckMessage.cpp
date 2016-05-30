#include "AckMessage.h"

/**
 * @brief Creates an ack
 * @param idDevice
 * @param ackType : ACK_OK, ACK_ERR, ACK_NOK
 */
AckMessage::AckMessage(uint8_t id, uint8_t ackType) : Message(id, SIZE_ACK, SIZE_OPCODE + SIZE_SIZE, ackType)
{
    LOG(1, "AckMessage(idDevice, ackType)");
}

/**
 * @brief Destructor
 */
AckMessage::~AckMessage()
{
    LOG(1, "~AckMessage()");
}
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
 * @return opCode 
 */
uint8_t AckMessage::getAckType() const {
    return Message::getOpCode();
}
