#include "AckMessage.h"

/*!
 * \brief Constructor
 *
 * Creates an ack
 *
 * \param id device's ID
 * \param ackType ACK_OK, ACK_ERR, ACK_NOK
 */
AckMessage::AckMessage(uint8_t id, uint8_t ackType) :
    Message(id, SIZE_ACK, SIZE_OPCODE + SIZE_SIZE, ackType)
{
    LOG(1, "AckMessage(idDevice, ackType)");
}

/*!
 * \brief Destructor
 *
 */
AckMessage::~AckMessage()
{
    LOG(1, "~AckMessage()");
}

/*!
 * \todo is this method usefull ?
 * \brief Fills the buffers with the data
 *
 * Method which encodes an ack
 *
 * \param sizeLeftPack 
 * \param opCodePack
 */
void AckMessage::encodeAck(uint16_t sizeLeftPack, uint8_t opCodePack)
{
    uint8_t *tab = new uint8_t[3];
    packID(sizeLeftPack, opCodePack, tab);
    this->encode(tab);

    delete [] tab;
}

/*!
 * \todo is this method usefull ? 
 * \brief TODO
 * \param fd
 * \param msg
 */
void AckMessage::handleAck(int fd, Message &msg)
{
    //    if (opCode != ACK_OK) {
    //     Buffer buff;
    //     buff = msg.getBuffer(listBuffer[0].getOpCode(), listBuffer[0].getSizeLeft());
    //     buff.send(fd);        
    // }
}


/*!
 * \todo is this method usefull ?
 * \brief TODO
 * \param fd
 */
void AckMessage::setAck(int fd)
{

}

/*!
 * \brief Getter
 *
 * Method which returns the type of ack
 *
 * \return the ack's operation code
 */
uint8_t AckMessage::getAckType() const
{
    return Message::getOpCode();
}
