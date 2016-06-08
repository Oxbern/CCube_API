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
