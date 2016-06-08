#include "Ack.h"
#include "Utils.h"
#include "Debug.h"

/*!
 * \brief Constructor
 *
 * Creates an ack
 *
 * \param id device's ID
 * \param ackType ACK_OK, ACK_ERR, ACK_NOK
 */
Ack::Ack(uint8_t id, uint8_t ackType) :
    IncomingMessage(id, SIZE_ACK, SIZE_OPCODE + SIZE_SIZE, ackType)
{
    LOG(1, "Ack(idDevice, ackType)");
}

/*!
 * \brief Destructor
 *
 */
Ack::~Ack()
{
    LOG(1, "~Ack()");
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
void Ack::encodeAck(uint16_t sizeLeftPack, uint8_t opCodePack)
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
// void Ack::handleAck(int fd, OutgoingMessage &msg)
// {
//     //    if (opCode != ACK_OK) {
//     //     Buffer buff;
//     //     buff = msg.getBuffer(listBuffer[0].getOpCode(), listBuffer[0].getSizeLeft());
//     //     buff.send(fd);        
//     // }
// }


/*!
 * \todo is this method usefull ?
 * \brief TODO
 * \param fd
 */
void Ack::setAck(int fd)
{

}

/*!
 * \brief Getter
 *
 * Method which returns the type of ack
 *
 * \return the ack's operation code
 */
uint8_t Ack::getAckType() const
{
    return IncomingMessage::getOpCode();
}
